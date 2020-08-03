# Project 3 - Quadris

Members:

- Dhvani Patel
- Peggy Li
- Minglei Li

## Bonus Features/Enhancements:
**1. No Leaks**  
All memory management handled via STL vectors and smart pointers.

**2. Renaming commands**  
Support added for the renaming of existing commands.

**3. GUI**  
        Programatically created with gtkmm and DrawingArea.

**4. AI Command**  
        `ai` command auto-plays the current level, playing blocks with a calculated optimal placement.

## Command Line Arguments
`./quadris [-text] [-startlevel n] [-scriptfile xxx] [-seed xxx]`
- `-text` runs in text-only mode. Shows both GUI and text by default.
- `-seed` sets the RNG's seed to xxx.
- `-scriptfile` uses xxx instead of sequence.txt as source of blocks for level 0.
- `-startlevel` starts the game at level n.

## Commands
`left`  
`right`  
`down`  
`clockwise`  
`counterclockwise`  
`drop`  
`levelup`  
`leveldown`  
`norandom file`  
`random`  
`sequence file`  
`restart`  
`hint`  
`I, J, L, S, Z, O, T`  
`exit`  
`rename`  
`ai`
