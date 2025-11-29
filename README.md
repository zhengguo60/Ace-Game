# Ace-Game
A retro arcade-style shooting game built entirely from scratch using C++ and POSIX system calls. It runs directly in your Linux terminal without requiring external game libraries (like ncurses or SDL)

# <font style="color:rgb(26, 28, 30);">Linux C++ Terminal Plane War</font>
<font style="color:rgb(26, 28, 30);">A retro arcade-style shooting game built entirely from scratch using C++ and POSIX system calls. It runs directly in your Linux terminal without requiring external game libraries (like ncurses or SDL)</font>

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">Features</font>
+ **<font style="color:rgb(26, 28, 30);">Terminal-Based Graphics:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Uses ANSI escape codes for colorful rendering and UI.</font>
+ **<font style="color:rgb(26, 28, 30);">Real-time Input:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Implements non-blocking keyboard input using</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">termios</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">and</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">select</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">for smooth control.</font>
+ **<font style="color:rgb(26, 28, 30);">Collision System:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Smart collision detection (interleaved updates) to prevent "tunneling" effects.</font>
+ **<font style="color:rgb(26, 28, 30);">Item System:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Randomly spawned power-ups:</font>
    - **<font style="color:rgb(26, 28, 30);">[B] Bomb:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Clears all enemies on screen.</font>
    - **<font style="color:rgb(26, 28, 30);">[S] Super Gun:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Activates 3-way scatter shot for 10 seconds.</font>
+ **<font style="color:rgb(26, 28, 30);">Game State Management:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Support for</font><font style="color:rgb(26, 28, 30);"> </font>**<font style="color:rgb(26, 28, 30);">Saving</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">and</font><font style="color:rgb(26, 28, 30);"> </font>**<font style="color:rgb(26, 28, 30);">Loading</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">game progress.</font>
+ **<font style="color:rgb(26, 28, 30);">Dynamic UI:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Side-panel HUD showing score, difficulty, and active buffs.</font>
+ **<font style="color:rgb(26, 28, 30);">3 Difficulty Levels:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Easy, Medium, and Hard.</font>

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">Prerequisites</font>
+ **<font style="color:rgb(26, 28, 30);">OS:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Linux / macOS (POSIX-compliant terminal required).</font>
+ **<font style="color:rgb(26, 28, 30);">Compiler:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">g++</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">(supports C++11 or later).</font>
+ **<font style="color:rgb(26, 28, 30);">Terminal:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Recommended to use a terminal that supports ANSI colors (e.g., Gnome-terminal, VSCode, XTerm).</font>

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">Build & Run</font>
### <font style="color:rgb(26, 28, 30);">Method 1: Direct Compilation</font>
<font style="color:rgb(26, 28, 30);">You can compile the game using a single command:</font>

```plain
g++ -std=c++11 main.cpp Game.cpp Entity.cpp Utils.cpp -o plane_war
```

### <font style="color:rgb(26, 28, 30);">Method 2: Using Makefile (Recommended)</font>
<font style="color:rgb(26, 28, 30);">If you have a </font><font style="color:rgb(50, 48, 44);">Makefile</font><font style="color:rgb(26, 28, 30);">, simply run:</font>

```plain
make
```

### <font style="color:rgb(26, 28, 30);">Run the Game</font>
```plain
./plane_war
```

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">Controls</font>
| **<font style="color:rgb(26, 28, 30);">Key</font>** | **<font style="color:rgb(26, 28, 30);">Action</font>** |
| --- | --- |
| **<font style="color:rgb(26, 28, 30);">W</font>** | <font style="color:rgb(26, 28, 30);">Move Up</font> |
| **<font style="color:rgb(26, 28, 30);">S</font>** | <font style="color:rgb(26, 28, 30);">Move Down</font> |
| **<font style="color:rgb(26, 28, 30);">A</font>** | <font style="color:rgb(26, 28, 30);">Move Left</font> |
| **<font style="color:rgb(26, 28, 30);">D</font>** | <font style="color:rgb(26, 28, 30);">Move Right</font> |
| **<font style="color:rgb(26, 28, 30);">SPACE</font>** | <font style="color:rgb(26, 28, 30);">Shoot</font> |
| **<font style="color:rgb(26, 28, 30);">P</font>** | <font style="color:rgb(26, 28, 30);">Save Game</font> |
| **<font style="color:rgb(26, 28, 30);">Q</font>** | <font style="color:rgb(26, 28, 30);">Quit to Menu</font> |


## <font style="color:rgb(26, 28, 30);">Project Structure</font>
+ **<font style="color:rgb(50, 48, 44);">main.cpp</font>**<font style="color:rgb(26, 28, 30);">: Entry point. Handles the main menu logic.</font>
+ **<font style="color:rgb(50, 48, 44);">Game.cpp/h</font>**<font style="color:rgb(26, 28, 30);">: Core game loop, rendering logic, update mechanism, and collision detection.</font>
+ **<font style="color:rgb(50, 48, 44);">Entity.cpp/h</font>**<font style="color:rgb(26, 28, 30);">: Base class for all objects. Derived classes:</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">Player</font><font style="color:rgb(26, 28, 30);">,</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">Enemy</font><font style="color:rgb(26, 28, 30);">,</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">Bullet</font><font style="color:rgb(26, 28, 30);">,</font><font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(50, 48, 44);">Item</font><font style="color:rgb(26, 28, 30);">.</font>
+ **<font style="color:rgb(50, 48, 44);">Utils.cpp/h</font>**<font style="color:rgb(26, 28, 30);">: Helper functions for terminal control (hide cursor, non-blocking I/O, colors).</font>
+ **<font style="color:rgb(50, 48, 44);">save.txt</font>**<font style="color:rgb(26, 28, 30);">: Stores game progress (Score & Difficulty).</font>

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">Game Mechanics</font>
### <font style="color:rgb(26, 28, 30);">Enemies</font>
<font style="color:rgb(26, 28, 30);">Enemies spawn at the top and move down.</font>

+ **<font style="color:rgb(26, 28, 30);">Penalty:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">If an enemy reaches the bottom of the screen, you may lose points (optional rule).</font>
+ **<font style="color:rgb(26, 28, 30);">Game Over:</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">If an enemy crashes into your player.</font>

### <font style="color:rgb(26, 28, 30);">Power-Ups (Green Symbols)</font>
+ **<font style="color:rgb(50, 48, 44);">B</font>****<font style="color:rgb(26, 28, 30);"> </font>****<font style="color:rgb(26, 28, 30);">(Bomb):</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Instantly destroys all visible enemies and adds points.</font>
+ **<font style="color:rgb(50, 48, 44);">S</font>****<font style="color:rgb(26, 28, 30);"> </font>****<font style="color:rgb(26, 28, 30);">(Super):</font>**<font style="color:rgb(26, 28, 30);"> </font><font style="color:rgb(26, 28, 30);">Equips a shotgun. Pressing Space will fire 3 bullets at once (Left, Center, Right) for a limited time.</font>

## <font style="color:rgb(26, 28, 30);">Screenshots</font>
```plain
╔══════════════════════════════════════════╗
║ SCORE: 150   LEVEL: 2                    ║
╠══════════════════════════════════════════╣
║                  M                       ║  === CONTROLS ===
║      |                                   ║
║      |                                   ║  [W] Move Up
║      |           S                       ║  [S] Move Down
║     AAA                                  ║  [A] Move Left
║                                          ║  [D] Move Right
║                                          ║
║                                          ║  [SPC] Shoot
║                                          ║
║                                          ║  [P] Save Game
║                                          ║  [Q] Quit Game
╚══════════════════════════════════════════╝
```

## <font style="color:rgb(26, 28, 30);"></font><font style="color:rgb(26, 28, 30);">License</font>
<font style="color:rgb(26, 28, 30);">This project is open-source and available for educational purposes. Feel free to modify and improve it!</font>

