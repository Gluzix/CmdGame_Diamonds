#include "Console.h"
#include <climits>

namespace
{
    constexpr WORD defaultColour = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // The logo and the win/lose screens are all 123 columns wide, and the menu is the
    // tallest thing the game prints: 12 rows of logo, then the three options with a blank
    // row between them, leaving the caret on the row below. The console never ends up
    // smaller than that even if the caller asks for less - which is what happens when the
    // map file cannot be read and its measured size comes back as zero.
    constexpr int minimumColumns = 124;
    constexpr int minimumRows = 20;

    // How the console was found. The screen buffer belongs to whatever shell started the
    // game, so a round played in an existing cmd window has to hand it back the way it was;
    // otherwise that shell is left with an invisible caret and a 28-row scrollback.
    bool consoleSaved = false;
    CONSOLE_CURSOR_INFO savedCursor{};
    COORD savedBufferSize{};
    SMALL_RECT savedWindow{};

    SHORT asBufferSize(int requested, int minimum)
    {
        if (requested < minimum) {
            requested = minimum;
        }

        if (requested > SHRT_MAX) {
            requested = SHRT_MAX;
        }

        return static_cast<SHORT>(requested);
    }

    SHORT smaller(SHORT first, SHORT second)
    {
        return first < second ? first : second;
    }

    bool saveConsoleState(HANDLE hOutput)
    {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo{};

        if (!GetConsoleScreenBufferInfo(hOutput, &bufferInfo) || !GetConsoleCursorInfo(hOutput, &savedCursor)) {
            return false;
        }

        savedBufferSize = bufferInfo.dwSize;
        savedWindow = bufferInfo.srWindow;
        consoleSaved = true;

        return true;
    }

    // SetConsoleScreenBufferSize() refuses any buffer smaller than the window that is on
    // screen at the time, so the window has to be pulled out of the way before a resize and
    // opened back up over the new buffer afterwards. That holds in both directions.
    bool shrinkWindow(HANDLE hOutput)
    {
        const SMALL_RECT smallestWindow = { .Left = 0, .Top = 0, .Right = 1, .Bottom = 1 };

        return SetConsoleWindowInfo(hOutput, TRUE, &smallestWindow) != FALSE;
    }

    bool openWindow(HANDLE hOutput, const SMALL_RECT& window)
    {
        return SetConsoleWindowInfo(hOutput, TRUE, &window) != FALSE;
    }

    void setCursorVisible(HANDLE hOutput, BOOL visible)
    {
        CONSOLE_CURSOR_INFO cursorInfo{};

        if (!GetConsoleCursorInfo(hOutput, &cursorInfo)) {
            return;
        }

        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(hOutput, &cursorInfo);
    }

    void writeCharAt(const Coordinates& coordinates, char character, WORD colour)
    {
        HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD consoleCoords = { static_cast<SHORT>(coordinates.x), static_cast<SHORT>(coordinates.y) };

        SetConsoleTextAttribute(hOutput, colour);
        SetConsoleCursorPosition(hOutput, consoleCoords);
        WriteConsoleA(hOutput, &character, 1, nullptr, nullptr);
        SetConsoleTextAttribute(hOutput, defaultColour);
    }
}

void prepareConsole(int columns, int rows)
{
    const HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOutput == nullptr || hOutput == INVALID_HANDLE_VALUE) {
        return;
    }

    // Fails when output is redirected to a file or a pipe, and that is the one case where
    // there is no console to size at all.
    if (!saveConsoleState(hOutput)) {
        return;
    }

    // Every tile is placed by hand, so the caret would otherwise sit blinking on whichever
    // one was drawn last.
    setCursorVisible(hOutput, FALSE);

    const COORD wantedBuffer = {
        .X = asBufferSize(columns, minimumColumns),
        .Y = asBufferSize(rows, minimumRows)
    };

    const bool windowShrunk = shrinkWindow(hOutput);

    if (!SetConsoleScreenBufferSize(hOutput, wantedBuffer)) {
        // The board cannot be made to line up on this console, but the window must not be
        // left at the couple of cells the shrink put it at.
        if (windowShrunk) {
            openWindow(hOutput, savedWindow);
        }

        return;
    }

    // The window can be no larger than the buffer behind it, nor than what the display can
    // show with the current font. A screen too small for the whole board is not a failure
    // either: the buffer keeps its full width, which is the part that holds the rows in
    // line, and the rest of the board is a scroll away.
    const COORD largestWindow = GetLargestConsoleWindowSize(hOutput);

    SHORT windowColumns = wantedBuffer.X;
    SHORT windowRows = wantedBuffer.Y;

    if (largestWindow.X > 0 && largestWindow.Y > 0) {
        windowColumns = smaller(windowColumns, largestWindow.X);
        windowRows = smaller(windowRows, largestWindow.Y);
    }

    const SMALL_RECT window = {
        .Left = 0,
        .Top = 0,
        .Right = static_cast<SHORT>(windowColumns - 1),
        .Bottom = static_cast<SHORT>(windowRows - 1)
    };

    if (!openWindow(hOutput, window)) {
        // The buffer is the size the board needs and that is what keeps the drawing
        // correct, so put the window back where it was and let the player size it by hand.
        openWindow(hOutput, savedWindow);
    }
}

void restoreConsole()
{
    if (!consoleSaved) {
        return;
    }

    consoleSaved = false;

    const HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOutput == nullptr || hOutput == INVALID_HANDLE_VALUE) {
        return;
    }

    // Best effort, in the order the resize has to happen: the buffer the console started
    // with is shorter than the window the game has been playing in, and often narrower too,
    // so the window has to come down first. Nothing useful can be done if it refuses.
    shrinkWindow(hOutput);
    SetConsoleScreenBufferSize(hOutput, savedBufferSize);
    openWindow(hOutput, savedWindow);
    SetConsoleCursorInfo(hOutput, &savedCursor);
}

void drawCharAt(const Coordinates& coordinates, char character, WORD colour)
{
    writeCharAt(coordinates, character, colour);
}

void clearCharAt(const Coordinates& coordinates)
{
    writeCharAt(coordinates, ' ', defaultColour);
}
