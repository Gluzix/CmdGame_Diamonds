#include "MapCheck.h"
#include <cstddef>
#include <string_view>
#include "Coordinates.h"

namespace
{
    constexpr std::size_t maxListedCells = 3;
    constexpr std::string_view byteOrderMark = "\xEF\xBB\xBF";
    constexpr std::string_view legend = "#*$SOUT@&^% ";

    // Up, down, left and right: the four ways the player moves.
    constexpr int stepX[] = { 0, 0, -1, 1 };
    constexpr int stepY[] = { -1, 1, 0, 0 };

    bool isInLegend(char ch)
    {
        return legend.find(ch) != std::string_view::npos;
    }

    // Off the board counts as a wall, as it does in Map::charAt().
    char glyphAt(const std::vector<std::string>& rows, const Coordinates& cell)
    {
        if (cell.y < 0 || cell.y >= static_cast<int>(rows.size())) {
            return '#';
        }

        const std::string& row = rows[cell.y];

        if (cell.x < 0 || cell.x >= static_cast<int>(row.size())) {
            return '#';
        }

        return row[cell.x];
    }

    // Counted from 1, the way a text editor shows them.
    std::string describeCell(const Coordinates& cell)
    {
        return "line " + std::to_string(cell.y + 1) + ", column " + std::to_string(cell.x + 1);
    }

    std::string describeCharacter(char ch)
    {
        if (ch == '\t') {
            return "a tab";
        }

        if (ch == '\r') {
            return "a carriage return";
        }

        const unsigned char code = static_cast<unsigned char>(ch);

        if (code >= ' ' && code <= '~') {
            return std::string("'") + ch + "'";
        }

        return "byte " + std::to_string(code);
    }

    // A long list is cut short, so one badly broken board cannot push the rest of the
    // report off the screen.
    std::string joinListed(const std::vector<std::string>& items)
    {
        std::string joined;

        for (std::size_t index = 0; index < items.size() && index < maxListedCells; index++) {
            if (index > 0) {
                joined += "; ";
            }

            joined += items[index];
        }

        if (items.size() > maxListedCells) {
            joined += " and " + std::to_string(items.size() - maxListedCells) + " more";
        }

        return joined;
    }

    std::string describeCells(const std::vector<Coordinates>& cells)
    {
        std::vector<std::string> items;

        for (const Coordinates& cell : cells) {
            items.push_back(describeCell(cell));
        }

        return joinListed(items);
    }

    // Models Map::removeBarriers(), which turns every '$' on the board into floor at once and
    // for good. If the game ever opens barriers differently, this has to change with it.
    bool isOpenBarrier(const std::vector<std::string>& rows, const Coordinates& cell, bool barriersOpen)
    {
        return barriersOpen && glyphAt(rows, cell) == '$';
    }

    bool isBlockedForEnemy(const Map& cleared, const std::vector<std::string>& rows, const Coordinates& cell,
        bool barriersOpen)
    {
        return !isOpenBarrier(rows, cell, barriersOpen) && cleared.isObstacleForEnemy(cell);
    }

    // Models FastestEnemy, which only ever moves up and down: it starts upwards and reverses
    // whenever it is blocked. With something solid directly above it and directly below it, a
    // '%' never leaves its cell and kills whoever steps onto it, so that cell is a wall. If the
    // game ever moves it differently, this has to change with it.
    bool isStuckPatroller(const Map& cleared, const std::vector<std::string>& rows, const Coordinates& cell,
        bool barriersOpen)
    {
        return glyphAt(rows, cell) == '%'
            && isBlockedForEnemy(cleared, rows, Coordinates(cell.x, cell.y - 1), barriersOpen)
            && isBlockedForEnemy(cleared, rows, Coordinates(cell.x, cell.y + 1), barriersOpen);
    }

    bool isWalkable(const Map& cleared, const std::vector<std::string>& rows, const Coordinates& cell,
        bool barriersOpen)
    {
        if (isOpenBarrier(rows, cell, barriersOpen)) {
            return true;
        }

        return !cleared.isObstacleForPlayer(cell) && !isStuckPatroller(cleared, rows, cell, barriersOpen);
    }

    // Every cell the player can walk to from start, marked with a 1 in a grid of rows by width.
    std::vector<std::vector<char>> reachableFrom(const Map& cleared, const std::vector<std::string>& rows,
        int width, const Coordinates& start, bool barriersOpen)
    {
        const int height = static_cast<int>(rows.size());
        std::vector<std::vector<char>> reached(rows.size(), std::vector<char>(static_cast<std::size_t>(width), 0));
        std::vector<Coordinates> toVisit{ start };

        reached[start.y][start.x] = 1;

        while (!toVisit.empty()) {
            const Coordinates cell = toVisit.back();
            toVisit.pop_back();

            for (std::size_t step = 0; step < std::size(stepX); step++) {
                const Coordinates next(cell.x + stepX[step], cell.y + stepY[step]);

                if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height) {
                    continue;
                }

                if (reached[next.y][next.x] != 0 || !isWalkable(cleared, rows, next, barriersOpen)) {
                    continue;
                }

                reached[next.y][next.x] = 1;
                toVisit.push_back(next);
            }
        }

        return reached;
    }

    // Levers and exits are solid: the player uses one by walking into it from a cell beside it
    // and is pushed back, so one reached neighbour is enough.
    bool canBump(const std::vector<std::vector<char>>& reached, const Coordinates& cell)
    {
        for (std::size_t step = 0; step < std::size(stepX); step++) {
            const int x = cell.x + stepX[step];
            const int y = cell.y + stepY[step];

            if (y >= 0 && y < static_cast<int>(reached.size())
                && x >= 0 && x < static_cast<int>(reached[y].size())
                && reached[y][x] != 0) {
                return true;
            }
        }

        return false;
    }

    bool canBumpAny(const std::vector<std::vector<char>>& reached, const std::vector<Coordinates>& cells)
    {
        for (const Coordinates& cell : cells) {
            if (canBump(reached, cell)) {
                return true;
            }
        }

        return false;
    }
}

std::vector<std::string> findMapProblems(const Map& board)
{
    const std::vector<std::string>& rows = board.getFileReader().getContent();

    // FileReader cannot tell a missing file from an empty one.
    if (rows.empty()) {
        return { "the file cannot be opened, or it is empty" };
    }

    // Every column on line 1 would be off by three, so nothing else is worth reporting yet.
    if (rows.front().starts_with(byteOrderMark)) {
        return { "the file starts with a UTF-8 byte order mark: save it again as plain text without one "
                 "(in Notepad: Save As, Encoding UTF-8, not UTF-8 with BOM)" };
    }

    std::vector<Coordinates> starts;
    std::vector<Coordinates> diamonds;
    std::vector<Coordinates> levers;
    std::vector<Coordinates> exits;
    std::vector<std::string> strangers;
    bool hasBarriers = false;

    for (int y = 0; y < static_cast<int>(rows.size()); y++) {
        const std::string& row = rows[y];

        for (int x = 0; x < static_cast<int>(row.size()); x++) {
            const Coordinates cell(x, y);
            const char ch = row[x];

            if (ch == '@') {
                starts.push_back(cell);
            }
            else if (ch == '*') {
                diamonds.push_back(cell);
            }
            else if (ch == '$') {
                hasBarriers = true;
            }

            if (board.hasPlayerSwitchedGate(cell)) {
                levers.push_back(cell);
            }

            if (board.hasPlayerFinished(cell)) {
                exits.push_back(cell);
            }

            if (!isInLegend(ch)) {
                strangers.push_back(describeCharacter(ch) + " at " + describeCell(cell));
            }
        }
    }

    std::vector<std::string> problems;

    if (!strangers.empty()) {
        const std::string count = strangers.size() == 1
            ? "1 character is"
            : std::to_string(strangers.size()) + " characters are";

        problems.push_back(count + " not in the map legend (# * $ S O U T @ & ^ % and space): "
            + joinListed(strangers));
    }

    if (starts.empty()) {
        problems.push_back("there is no player start: a board needs exactly one '@'");
    }
    else if (starts.size() > 1) {
        problems.push_back("there are " + std::to_string(starts.size())
            + " player starts ('@'), and a board needs exactly one: " + describeCells(starts));
    }

    if (diamonds.empty()) {
        problems.push_back("there are no diamonds: a board needs at least one '*'");
    }

    if (exits.empty()) {
        problems.push_back("there is no exit: a board needs an 'OUT'");
    }

    if (hasBarriers && levers.empty()) {
        problems.push_back("there are barriers ('$') but no lever ('S') to open them");
    }

    // Where the player can get to is only a question once there is exactly one place to start.
    if (starts.size() != 1) {
        return problems;
    }

    // The round clears the spawn markers before its first frame, so the game's own questions
    // are asked of a copy cleared the same way. clearSpawnMarkers() only edits the data; nothing
    // here may call drawMap(), removeBarriers() or redrawTile(), which paint on the console.
    Map cleared = board;
    cleared.clearSpawnMarkers();

    const int width = board.getFileReader().getWidth();
    const Coordinates start = starts.front();

    // Two walks. With the barriers closed, some lever has to be usable; the diamonds and the
    // exit then only have to be usable with them open, because the lever works at any score.
    // Map.txt needs exactly that: it seals a diamond inside the exit's own chamber.
    std::vector<std::vector<char>> reached = reachableFrom(cleared, rows, width, start, false);
    bool barriersOpen = false;

    if (hasBarriers && !levers.empty()) {
        barriersOpen = canBumpAny(reached, levers);

        if (!barriersOpen) {
            problems.push_back("the lever ('S') cannot be reached from the start, so the barriers never open: "
                + describeCells(levers));
        }
    }

    if (barriersOpen) {
        reached = reachableFrom(cleared, rows, width, start, true);
    }

    std::string suffix;

    if (hasBarriers) {
        suffix = barriersOpen ? ", even with the barriers open" : " while the barriers are closed";
    }

    std::vector<Coordinates> unreachable;

    for (const Coordinates& diamond : diamonds) {
        if (reached[diamond.y][diamond.x] == 0) {
            unreachable.push_back(diamond);
        }
    }

    if (!unreachable.empty()) {
        const std::string count = unreachable.size() == 1
            ? "1 diamond"
            : std::to_string(unreachable.size()) + " diamonds";

        problems.push_back(count + " cannot be reached" + suffix + ": " + describeCells(unreachable));
    }

    if (!exits.empty() && !canBumpAny(reached, exits)) {
        problems.push_back("the exit cannot be reached" + suffix + ": " + describeCell(exits.front()));
    }

    return problems;
}
