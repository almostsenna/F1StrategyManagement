# F1 Strategy Management Game

**F1 Strategy Management Game** is a C++ console-based racing strategy simulator inspired by Formula 1.  
The player manages race decisions lap by lap, including pace mode, tyre usage, and pit stop timing.

The project was created as an educational team project to practice **C++**, **object-oriented programming**, and multi-file project structure while building a game-like simulation.

---

## Features

- Driver selection before the race
- Multiple race formats:
  - Sprint
  - Grand Prix
  - Custom race length
- Multiple tracks with different characteristics
- Lap-by-lap race simulation
- Strategy system with pace modes:
  - Push
  - Normal
  - Conserve
- Tyre management:
  - Soft
  - Medium
  - Hard
- Pit stop system with tyre change
- Full race grid simulation
- Console race status output with positions, gaps, tyre state, and lap updates

---

## How It Works

The game runs as a **turn-based lap simulation**.

For each lap, the program:
1. reads the player's decision;
2. updates driver and tyre states;
3. calculates lap times for all drivers;
4. updates total race times;
5. sorts positions;
6. prints the current race status.

Lap time is influenced by several factors:
- track base pace;
- driver performance;
- tyre compound;
- tyre wear;
- selected pace mode;
- small random variation.

This makes the result depend not only on the driver stats, but also on race strategy.

---

## Project Structure

```text
F1-Strategy-Management-Game/
│
├── main.cpp
├── Driver.h / Driver.cpp
├── Tyre.h / Tyre.cpp
├── Track.h / Track.cpp
├── Race.h / Race.cpp
├── Strategy.h / Strategy.cpp
├── Team.h / Team.cpp
└── README.md
```
Technologies Used
C++
Object-Oriented Programming (OOP)
STL
Visual Studio
How to Run
Open the project in Visual Studio
Build the solution
Run the program
Educational Goals

This project was created to practice:

class design and object interaction;
multi-file C++ project structure;
simulation logic;
console interface design;
teamwork in a programming project.
