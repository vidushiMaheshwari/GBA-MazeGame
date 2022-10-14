# Game Boy Advance - The Maze Game
This application is a fairly trivial implementation of a maze puzzle in game boy adanced.

The goal of the user is to reach the other end of the maze in less than 400 moves, and without hitting any maze lines.

Pressing 'A' from the START screen starts the game, which displays a moves counter  string and an image character which can move in 2D.

If the character hits a maze line, the user would lose (however, sliding along a maze line is allowed).

Similarly, if the counter reaches till 400, the user loses.

Wrapping of character across the screen is not possible - i.e. say if the character is in the leftmost part of the screen, then pressing left would do nothing.

If the user crosses the maze (2 more pixels ahead of the visible exit) the game would terminate with a WIN screen.

Pressing SELECT at any time during the game will lead the user to the START screen. Pressing 'A' from the start screen would lead user to a new game. A new game is represented by the move counter = '000' and position of character to be at the start of the maze.