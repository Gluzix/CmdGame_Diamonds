#include "Application.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <time.h>
#include <utility>
#include <vector>
#include <Windows.h>
#include "Console.h"
#include "FileReader.h"
#include "Map.h"
#include "MenuHandler.h"
#include "GameHandler.h"

namespace
{
    // One column and two rows more than the map: the score line goes on the row directly
    // under the board, and nothing is ever written into the last column or the last row, so
    // the console has no reason to wrap or scroll while a round is on screen.
    constexpr int spareColumns = 1;
    constexpr int spareRows = 2;

    constexpr char levelListPath[] = "resources/Levels.txt";
    constexpr char levelFolder[] = "resources/";
    constexpr char winScreenPath[] = "resources/Win.txt";
    constexpr char loseScreenPath[] = "resources/Lose.txt";
    constexpr std::string_view byteOrderMark = "\xEF\xBB\xBF";
    constexpr char blanks[] = " \t\r";

    // The keys the menu and the rounds act on.
    constexpr int watchedKeys[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE, VK_RETURN };
    constexpr int keyPollMs = 10;
    constexpr int firstArrowPrefix = 0;
    constexpr int secondArrowPrefix = 224;

    struct BoardSize
    {
        int columns{ 0 };
        int rows{ 0 };
    };

    bool isAnyWatchedKeyDown()
    {
        for (const int key : watchedKeys) {
            if (GetAsyncKeyState(key) & 0x8000) {
                return true;
            }
        }

        return false;
    }

    void waitUntilKeysReleased()
    {
        while (isAnyWatchedKeyDown()) {
            Sleep(keyPollMs);
        }
    }

    void waitForAnyKey()
    {
        // An arrow still held from the round keeps auto-repeating into the console input and
        // would answer the screen before it could be read.
        waitUntilKeysReleased();
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

        // An arrow arrives as two codes, and the second must not be left for the next screen.
        const int key = _getch();

        if (key == firstArrowPrefix || key == secondArrowPrefix) {
            _getch();
        }

        // Nor may the key that answered still be down when the next round starts.
        waitUntilKeysReleased();
    }

    void showScreen(const std::vector<std::string>& lines, const std::string& prompt)
    {
        system("cls");

        for (const std::string& line : lines) {
            std::cout << line << std::endl;
        }

        std::cout << std::endl << prompt << std::endl;

        waitForAnyKey();
    }

    std::vector<std::string> readLevelList()
    {
        const FileReader levelList(levelListPath);
        const std::vector<std::string>& lines = levelList.getContent();
        std::vector<std::string> levelPaths;

        for (std::size_t index = 0; index < lines.size(); index++) {
            std::string name = lines[index].substr(0, lines[index].find('#'));

            if (index == 0 && name.starts_with(byteOrderMark)) {
                name.erase(0, byteOrderMark.size());
            }

            const std::size_t first = name.find_first_not_of(blanks);

            if (first == std::string::npos) {
                continue;
            }

            const std::size_t last = name.find_last_not_of(blanks);
            levelPaths.push_back(levelFolder + name.substr(first, last - first + 1));
        }

        return levelPaths;
    }

    BoardSize measureLargestBoard(const std::vector<std::string>& levelPaths)
    {
        BoardSize largest;

        for (const std::string& path : levelPaths) {
            const FileReader board(path);

            if (board.getWidth() > largest.columns) {
                largest.columns = board.getWidth();
            }

            if (board.getHeight() > largest.rows) {
                largest.rows = board.getHeight();
            }
        }

        return largest;
    }

    std::vector<std::string> findLevelProblems(const Map& board, const BoardSize& sizedFor)
    {
        std::vector<std::string> problems;
        const int columns = board.getFileReader().getWidth();
        const int rows = board.getFileReader().getHeight();

        // The console was sized at startup from the boards as they were then, and a bigger
        // board drawn into it would misalign every row.
        if (columns > sizedFor.columns || rows > sizedFor.rows) {
            problems.push_back("it is " + std::to_string(columns) + " columns by " + std::to_string(rows)
                + " rows now, bigger than the " + std::to_string(sizedFor.columns) + " by "
                + std::to_string(sizedFor.rows)
                + " the console was sized for when the game started: restart the game to play it");
        }

        return problems;
    }

    // The exit moves on to the next level, being caught replays the same one from the board as
    // it was read, and Esc gives the game up.
    void playLevels(const std::vector<Map>& levels)
    {
        const int levelCount = static_cast<int>(levels.size());
        std::size_t level = 0;

        while (level < levels.size()) {
            GameHandler gameHandler(levels[level], static_cast<int>(level) + 1, levelCount);
            const RoundResult result = gameHandler.run();

            if (result == RoundResult::Quit) {
                return;
            }

            if (result == RoundResult::Caught) {
                const FileReader loseScreen(loseScreenPath);
                showScreen(loseScreen.getContent(), "Press any key to try this level again...");
                continue;
            }

            level++;
        }

        const FileReader winScreen(winScreenPath);
        showScreen(winScreen.getContent(), "You finished the game! Press any key to return to the menu...");
    }

    // Every level is read and checked before the first is played, so a broken level 3 is
    // reported now and not after levels 1 and 2 are won. The rounds play copies of these boards
    // and never read the files again.
    void playCampaign(const BoardSize& sizedFor)
    {
        const std::vector<std::string> levelPaths = readLevelList();

        if (levelPaths.empty()) {
            const std::vector<std::string> lines{
                std::string(levelListPath) + " is missing, or it names no levels.",
                "It should name one board file per line, for example: Map.txt"
            };
            showScreen(lines, "Press any key to return to the menu...");
            return;
        }

        std::vector<Map> levels;
        std::vector<std::string> report;

        for (std::size_t index = 0; index < levelPaths.size(); index++) {
            Map board(levelPaths[index]);
            const std::vector<std::string> problems = findLevelProblems(board, sizedFor);

            if (!problems.empty()) {
                report.push_back("Level " + std::to_string(index + 1) + ", " + levelPaths[index] + ":");

                for (const std::string& problem : problems) {
                    report.push_back("  - " + problem);
                }

                report.push_back("");
            }

            levels.push_back(std::move(board));
        }

        if (!report.empty()) {
            std::vector<std::string> lines{ "These levels cannot be played:", "" };
            lines.insert(lines.end(), report.begin(), report.end());
            lines.push_back("Fix them, or put a # in front of their line in " + std::string(levelListPath) + ".");
            showScreen(lines, "Press any key to return to the menu...");
            return;
        }

        playLevels(levels);
    }
}

void Application::run()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // The boards are drawn at fixed console coordinates, so the console has to hold the widest
    // and the tallest of them before anything is printed. It is sized once, here, and never
    // between levels: a second prepareConsole() would save the game's own hidden caret and
    // buffer as the ones restoreConsole() gives back.
    const BoardSize largest = measureLargestBoard(readLevelList());
    prepareConsole(largest.columns + spareColumns, largest.rows + spareRows);

    MenuHandler menuHandler;

    while (true)
    {
        GameStatus status = menuHandler.run();

        if (status == GameStatus::Start) {
            playCampaign(largest);
        }
        else if (status == GameStatus::About) {
            system("cls");
            std::cout << "About creators:" << std::endl;
            std::cout << std::endl << "Press any key to return to the menu..." << std::endl;

            FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            _getch();
        }
        else {
            break;
        }
    }

    // The console belongs to whoever started the game, so it goes back the way it was.
    restoreConsole();
}
