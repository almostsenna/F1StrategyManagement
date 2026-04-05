# Formula 1 Race Strategy Simulator

## Versions

### v0.1 — Core Simulation
- lap-by-lap race simulation
- lap time calculation
- tyre wear system
- fuel consumption
- pit stop logic
- position calculation
- basic console output

### v0.2 — Readable Simulation
- gap to leader
- race mode display
- tyre temperature output
- pit stop events
- improved console formatting

### v0.3 — Improved Race Logic
- added track-specific parameters
- improved lap time calculation
- added custom tyre compound selection after pit stop
- improved pit stop event output
- made race dynamics more realistic

### v0.4 — Multiple Tracks
- added track selection menu
- added 10 predefined tracks
- each track has unique race parameters
- tracks now affect power, technicality, tyre wear, and temperature behavior

### v0.5 — Interactive Strategy
- added driver selection
- added player-controlled strategy management
- added live race mode switching
- added manual pit stop requests
- fixed player tracking after position changes
- added stable [YOU] marker for selected driver

### v0.6 — Console System & Driver Expansion

This version introduces a major upgrade to the project, transforming it from a technical race simulation into a structured console-based application with expanded content and improved usability.

#### Key Improvements:

- Added a full console menu system
  - Start race
  - View driver list
  - View detailed driver profiles
  - Select race type
  - Exit program

- Implemented race type selection:
  - Sprint (short race distance)
  - Grand Prix (default full distance)
  - Custom race (user-defined number of laps)

- Introduced Driver Profiles:
  - Includes name, team, nationality, age, experience
  - Displays car and engine information
  - Shows performance stats (skill, consistency, tyre management)
  - Added formatted driver "card" view

- Improved console UI:
  - Structured tables
  - Better alignment and readability
  - Cleaner interaction flow

- Expanded driver database:
  - Added full 2026 Formula 1 grid (22 drivers, 11 teams)
  - Included new Cadillac team
  - Updated modern team structure (Audi, VCARB, etc.)

- Integrated driver selection system:
  - Player can now choose any driver from the full grid
  - Selection is stable during race (fixed previous indexing issue)

#### Result:

The project now functions as a complete console-based race simulator with structured navigation, realistic driver data, and user interaction, forming a strong foundation for further development (GUI or advanced simulation features).
