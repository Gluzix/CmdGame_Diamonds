# Diamonds

My first game made in C++ — a small maze game that runs in the Windows console.

The game is a run of levels, one map each. Collect every diamond on the map, flip the lever
to open the barriers, then walk out through `OUT` to go on to the next level; walking out of
the last one finishes the game. Touch an enemy and that level starts again from the
beginning.

## Map legend

| Symbol | Meaning |
| --- | --- |
| `@` | where the player starts |
| `*` | a diamond — walk over it to pick it up |
| `#` | a wall |
| `$` | a barrier, closed until you flip the lever |
| `S` | the lever that opens every barrier |
| `OUT` | the exit |
| `&` | slow enemy |
| `^` | fast enemy |
| `%` | fastest enemy |

## Enemies

The game runs at one frame every 100 ms, and every enemy is a variation on the same
behaviour: walk in a straight line, and when something blocks the way, pick a new
direction. The differences are how often an enemy gets to move and whether it reacts to
the player at all.

| Enemy | Moves | Notices the player | Behaviour |
| --- | --- | --- | --- |
| `&` slow | every 4th frame | within 4 cells | walks straight ahead, chases the player once it spots them |
| `^` fast | every 2nd frame | within 6 cells | the same, but it sees further and moves twice as often |
| `%` fastest | every frame | never | ignores the player completely; it starts off upwards and reverses whenever it is blocked, so it patrols back and forth |

"Within N cells" means a box, not a radius: the player is spotted when they are at most N
cells away horizontally *and* at most N cells away vertically. A chasing enemy closes the
larger of the two gaps first. When a chasing enemy runs into a wall it tries up to four
random directions before giving up for that frame; `%` simply turns around.

`%` never comes after you, but running into one still kills you.

## Controls

| Key | Action |
| --- | --- |
| Arrow keys | move one cell (held down, you move one cell per frame) |
| `Esc` | give up the game and go back to the menu; the next **Start Game** begins again at level 1 |

In the menu, the arrow keys move the selection and `Enter` confirms it: **Start Game**,
**About Creators**, **Exit**.

## Things the map does not tell you

**You use `S` and `OUT` by bumping into them.** The lever and the three letters of `OUT`
are solid tiles, exactly like walls — you cannot stand on them. Walk into the tile and the
game registers it before pushing you back to where you came from.

**The lever works at any score, but the exit only opens once you hold every diamond.**
`resources/Map.txt` seals one diamond inside the `OUT` chamber, behind the barriers, so a
lever that demanded a full score would make that level impossible to finish. Only the exit
checks your score.

**The next level starts the moment you walk out.** There is no screen in between, so an
arrow you are still holding keeps you moving on the new map. After a capture, the lose
screen waits for you to let go of the keys, and then any key starts that level again.

Your progress is printed just below the map: `Level n/N` on the left says which level you
are on, and `Diamonds: n/total` how many diamonds you hold.

## Building and running

The project builds with CMake (3.20 or newer) and MSVC — C++20, x64. It is Windows-only:
it talks to the Win32 console API directly, and configuring it on any other platform
stops with an error instead of failing halfway through the compile.

`CMakePresets.json` carries the architecture and leaves the generator to CMake, which
picks the newest Visual Studio it finds. Build through the presets:

```
cmake --preset windows-msvc
cmake --build --preset windows-msvc-debug
```

Swap the last line for `--preset windows-msvc-release` to get the optimised build. Both
land in `build\`, which holds a single Visual Studio project serving every configuration.

If you would rather spell it out, the same thing without presets:

```
cmake -B build -A x64
cmake --build build --config Debug
cmake --build build --config Release
```

Visual Studio opens the repository directly — **File → Open → Folder**. It reads
`CMakePresets.json`, offers `windows-msvc` in the configuration dropdown and runs the game
on <kbd>F5</kbd>.

The game reads everything under `resources/` — the logo, the win and lose screens,
`resources/Levels.txt` and the maps it names — through paths relative to its working
directory. Every build copies `resources/` next to the executable it just produced, and that
copy is what the game reads when you double-click `build\Debug\Diamonds_CmdGame.exe` in
Explorer or press <kbd>F5</kbd> in Visual Studio. Started from the repository root instead,
as `build\Debug\Diamonds_CmdGame.exe`, it reads the repository's own `resources/`, so an
edited map needs no rebuild.

One more thing worth knowing: the game sizes its own console window at startup, screen
buffer and all, to the widest and the tallest map listed in `resources/Levels.txt`, so every
map fits however wide the console was to begin with. That happens once: a map that grows
while the game is running is refused until the game is restarted.

## Repository layout

```
header/          class declarations
source/          their implementations
resources/       the level list, the maps, the logo and the win/lose screens, all plain text
main.cpp         creates an Application and runs it
CMakeLists.txt   the build: the file list, the compiler settings and the resource copy
```

* **`Application`** — the menu loop and the campaign. It sizes the console, checks every
  level when **Start Game** is chosen, plays the levels in order, replays a level after a
  capture, and shows the end screens.
* **`MenuHandler`** / **`Menu`** — `MenuHandler` reads the keys and tracks which row is
  selected; `Menu` draws the logo and the three options.
* **`GameHandler`** — one round on one map: the frame loop, the player's input and moving
  the enemies. It reports whether the player escaped, was caught or pressed `Esc`, and leaves
  what comes next, end screens included, to `Application`.
* **`Map`** — one board, read from its file. It knows what is at each cell, which tiles
  block movement, and it redraws single tiles as things move over them.
* **`MapCheck`** — reports, by line and column, what keeps a board from being played.
* **`Player`** — the player's position and glyph.
* **`Enemy`** and its subclasses **`SlowEnemy`**, **`FastEnemy`**, **`FastestEnemy`** —
  shared movement and chasing logic, with each subclass supplying its own speed, eyesight
  and glyph.
* **`FileReader`** — reads a text file into a vector of lines, and lets the map edit a
  single character of it.
* **`Score`** — the diamond counter shown below the map.
* **`Console`** — the small Win32 helpers: sizing the console at startup, and drawing or
  clearing one character at a set position.

## Levels

The levels, and the order they are played in, come from `resources/Levels.txt`: one map
file per line, played top to bottom.

```
# The levels, in the order they are played: one board file per line. The files sit
# in this folder, so write Map.txt, not resources/Map.txt. Anything after a # is
# ignored, so a # at the start of a line takes that level out of the game.
Map.txt
```

* Write the bare file name, `Map.txt`, not `resources/Map.txt`: the maps sit next to the
  list.
* Keep file names to plain ASCII: letters, digits, `-`, `_` and `.`. The game cannot open a
  name with a letter such as `Ł` in it, so it reports that line of the list by its number.
* Blank lines are skipped and anything after a `#` is ignored, so a `#` at the start of a
  line takes that level out of the game without deleting its file.
* A missing list, or one that names no levels, gets a screen of its own when you choose
  **Start Game**. The game does not quietly fall back to `Map.txt`.

Every **Start Game** reads the list and every map on it afresh and checks them all before
level 1 begins, so a broken last level is reported straight away, not after you have won the
ones before it. The rounds then play copies of the maps that were checked: a level you are
caught on starts again exactly as its file has it.

### Drawing a map

A map is its own plain-text file in `resources/`, next to `Map.txt`. The file is the map and
nothing else — no title, no notes — and line 1 is the top row. Start from a copy of
`Map.txt`, and leave `Map.txt` itself as it is.

**Characters.** Only the legend above, plus the space for floor: no tabs, no lower-case
letters, no other letters, digits or punctuation, and nothing outside ASCII, such as
box-drawing characters or accented letters. Anything else would be an invisible wall, so the
check refuses it and says where it is. Save the file as plain text: ASCII, or UTF-8 without a
byte order mark, which is the same thing for these characters. Windows and Unix line endings
both work. The file may end with a line break but not with an empty line: an empty line
counts as a row and pushes the counter down.

* Each `O`, `U` and `T` is a working exit tile on its own, wherever it stands. Write the
  exit once, as `OUT` on one row, and use those letters for nothing else.
* Each `S` is a working lever, and any of them opens every `$` on the map. Use one.

**Size and shape.** The game does not check these, but a map needs them:

* At most 125 columns by 26 rows, the size the game is known to fit on screen. Exactly
  125 × 26, like `Map.txt`, is best.
* Every row the same length, with a complete `#` border. Past the end of a short row the
  game sees a wall but draws nothing.
* The row just below the map holds `Level n/N` from the first column and `Diamonds: n/total`
  from the 49th, so on a map narrower than 63 columns the counter sticks out past its right
  edge.
* The console is sized once, at startup, for the widest and the tallest listed map. A
  smaller map sits in its top-left corner.

**Difficulty.** `Map.txt`, the original map, has 12 diamonds, 13 `&`, 5 `^` and 3 `%` in
wide open halls. Keep the list in order of difficulty: a map played before it should be
easier, one played after it harder. Ways to make a map harder: more `^`, `%` patrolling
columns the player has to cross, narrower corridors with fewer ways out, diamonds in dead
ends near a chaser, and the lever far from the barriers it opens.

### What Start Game checks

A map is refused, with a message, when:

* the file cannot be opened or is empty, or starts with a UTF-8 byte order mark;
* it holds a character outside the legend;
* it does not have exactly one `@`;
* it has no `*`;
* it has no exit letter;
* it has a `$` but no `S`;
* the lever, a diamond or the exit cannot be reached.

Reachability follows the round's own rules. The player starts on the `@` and moves up,
down, left or right, never diagonally. Space, `*` and the cells where `@`, `&`, `^` and `%`
start are floor: the enemies begin there, and their markers are cleared when the level
starts. `#`, `S`, `O`, `U`, `T` and a closed `$` are solid. The lever and the exit letters
are used by walking into them from a floor cell beside them, so one reachable neighbour is
enough.

The check walks the map twice. First with every `$` closed: the lever has to be usable.
The lever opens every `$` at once and for good, so the second walk treats them as floor, and
then every `*` has to be reachable and the exit usable. The lever works at any score and only
the exit asks for every diamond, so a diamond may sit behind the barriers, even inside the
exit's own chamber — like the one at line 3, column 7 of `Map.txt`. A single walk with the
barriers closed would refuse the game's own map. A map without `$` is simply walked once.

A `%` only moves up and down. With something solid directly above it and directly below it
— `#`, `S`, an exit letter, or a `$` while the barriers are closed — it never moves, kills
whoever steps onto it, and counts as a wall. Give every `%` room above or below.

What the check cannot tell you is whether a person can survive the route. It does not look
at where the enemies are, and a map can pass every check and still be unfair:

* Enemies cannot pass `#`, a closed `$`, `S` or an exit letter. They walk over diamonds
  without taking them and pass through each other, and a wall does not hide you from them.
* Give the start room: keep every `^` at least 7 cells and every `&` at least 5 cells from
  the `@`, horizontally or vertically, so nothing is chasing you on the first frame.
* A `%` patrols the run of free cells in its column, its own cell included. In a run of two
  it swaps between them every frame and neither can be crossed; in a run of three the middle
  cell cannot be crossed. From four on, every cell can be crossed with the right timing.

### Trying a map out

Start the game from the repository root — in a terminal, `cd` into the repository and run
`build\Debug\Diamonds_CmdGame.exe` — and it reads the repository's own `resources/`. Every
**Start Game** reads the list and the maps again, so a saved edit shows up after `Esc` and
**Start Game**, with no rebuild and no restart. Only a map that has grown past the size the
console was given at startup asks for a restart. A double-click or <kbd>F5</kbd> reads the
copy in `build\Debug\resources\` instead, which every build refreshes.

To try one map without playing the ones before it, move its line to the top of
`Levels.txt`, or put a `#` in front of the others, and put the list back afterwards.

A refused map is reported when you choose **Start Game**, and any broken map on the list
keeps the whole game from starting until it is fixed or taken out of the list. Walling off
the lever in `Map.txt`, for example, gives:

```
These levels cannot be played:

Level 1, resources/Map.txt:
  - the lever ('S') cannot be reached from the start, so the barriers never open: line 2, column 49
  - 2 diamonds cannot be reached while the barriers are closed: line 3, column 7; line 3, column 49
  - the exit cannot be reached while the barriers are closed: line 2, column 2

Fix them, or put a # in front of their line in resources/Levels.txt.

Press any key to return to the menu...
```

Positions are counted the way an editor shows them: line 1 is the top row and column 1 the
leftmost character. A list of positions shows the first three and counts the rest.
