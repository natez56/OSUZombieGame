/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Main file for final project.  File contains a loop which
runs the game until the user chooses to end the game by using the menu
option to end game and pressing 'n', completing the game and pressing 'n',
or pressing 'q' and then 'n'. To run the program use the makefile to 
create the executable Final. Then use the approprate terminal command
to run the executable.
*********************************************************************/

#include <ncurses.h>
#include <iostream>
#include "StartZone.hpp"
#include "Game.hpp"

int main() {
	Game* zombieGame;
	zombieGame = new Game();
	int ch = 0;

	while(ch != 'n') {
		zombieGame->playGame();

		nodelay(stdscr, FALSE);

		printw("Play again?\n");
		printw("Press y for yes\n");
		printw("Press n for No\n");

		while (ch != 'y' && ch != 'n') {
			ch = getch();
			
			if (ch == 'y') {
				delete zombieGame;
				zombieGame = new Game;
			} else if (ch != 'n') {
				printw("Please enter in y or n\n");
			}
		}
	}
	delete zombieGame;
	
	endwin();
	return 0;
}