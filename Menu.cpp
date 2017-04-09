/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Menu function to allow user to either continue, exit game,
see game controls, or see the amount of turns left. To run the function
simply call it and it will allow the user to input one of the four
options. Returns a char. 'q' will cause the game to end, '4' will cause
the turns left to be printed to the screen. The char 'a' is a dummy variable
and will exit the menu and allow the user to continue the game.
*********************************************************************/

#include "Menu.hpp"
#include <ncurses.h>
#include <unistd.h>

char menu() {
	// Pauses screen until user input is given.
	nodelay(stdscr, FALSE);
	
	int ch;
	while (1) {
		clear();
		printw("Press the number corresponding to the menu option you want to ");
		printw("select.\n\n");
		printw("Game Menu\n");
		printw("1) Play Game\n");
		printw("2) Game Controls\n");
		printw("3) Exit Game\n");
		printw("4) Turns Left\n");

		// Function requesting user input
		ch = getch();
		if (ch == '1') {
			// Sets screen back to updating without the need for user input
			nodelay(stdscr, TRUE);
			//
			return 'a';
		} else if (ch == '2') {
			gameControlsMessage();
		} else if (ch == '3') {
			return 'q';
		} else if (ch == '4') {
			return '4';
		}
	}
	// Sets screen back to updating without the need for user input
	nodelay(stdscr, TRUE);

	return 'a';
}