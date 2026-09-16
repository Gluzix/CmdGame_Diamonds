# Diamonds

My first game made in C++ — a small maze game that runs in the Windows console.

Collect every diamond on the map, flip the lever to open the barriers, then walk out
through `OUT`. Touch an enemy and the round is over.

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
| `Esc` | abandon the round and go back to the menu |

In the menu, the arrow keys move the selection and `Enter` confirms it: **Start Game**,
**About Creators**, **Exit**.

## Things the map does not tell you

**You use `S` and `OUT` by bumping into them.** The lever and the three letters of `OUT`
are solid tiles, exactly like walls — you cannot stand on them. Walk into the tile and the
game registers it before pushing you back to where you came from.

**The lever works at any score, but the exit only opens once you hold every diamond.** The
bundled map seals one diamond inside the `OUT` chamber, behind the barriers, so a lever
that demanded a full score would make the round impossible to finish. Only the exit checks
your score.

Your progress is printed just below the map as `Diamonds: n/total`.

## Building and running

The project is a Visual Studio 2022 solution (`Diamonds_CmdGame.sln`), MSVC toolset v143,
C++17, x64. It is Windows-only — it talks to the Win32 console API directly.

Open the solution in Visual Studio and press <kbd>F5</kbd>, or build it from a command
line:

```
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" Diamonds_CmdGame.sln -p:Configuration=Debug -p:Platform=x64
```

**Start the game from the repository root.** It loads `resources/Logo.txt`,
`resources/Map.txt`, `resources/Win.txt` and `resources/Loose.txt` through relative paths,
so the working directory has to be the folder those `resources` live in. Double-clicking
`x64\Debug\Diamonds_CmdGame.exe` from inside `x64\Debug` will not find them. Visual
Studio's debugger defaults to the project directory, which is the repository root, so
<kbd>F5</kbd> works out of the box.

One more thing worth knowing: the map is printed character by character with no line
breaks of its own, and nothing in the code resizes the console. The rows only line up if
the console buffer is as wide as the map — 125 columns for the bundled one.

## Repository layout

```
header/      class declarations
source/      their implementations
resources/   the map, the logo and the win/lose screens, all plain text
main.cpp     creates an Application and runs it
```

* **`Application`** — the outer loop: show the menu, and start a game, the About screen or
  quit, depending on what was chosen.
* **`MenuHandler`** / **`Menu`** — `MenuHandler` reads the keys and tracks which row is
  selected; `Menu` draws the logo and the three options.
* **`GameHandler`** — one round: the frame loop, the player's input, moving the enemies and
  the win/lose screen at the end.
* **`Map`** — the board. It knows what is at each cell, which tiles block movement, and it
  redraws single tiles as things move over them.
* **`Player`** — the player's position and glyph.
* **`Enemy`** and its subclasses **`SlowEnemy`**, **`FastEnemy`**, **`FastestEnemy`** —
  shared movement and chasing logic, with each subclass supplying its own speed, eyesight
  and glyph.
* **`FileReader`** — reads a text file into a vector of lines, and lets the map edit a
  single character of it.
* **`Punctation`** — the diamond counter shown below the map.
* **`Console`** — the small Win32 helpers for drawing or clearing one character at a set
  position.

## Editing the map

`resources/Map.txt` is plain text, so you can rebuild the level in any editor. The game
reads it at startup: it counts the diamonds for the score, places the player at `@`, and
creates one enemy for every `&`, `^` and `%` it finds. A new map needs no code change as
long as it uses the same characters.
