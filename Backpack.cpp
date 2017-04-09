/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file of Backpack class. Contains a 
constructor, packMenu function, placeItem function, and getEquippedItem
function.
*********************************************************************/

#include "Backpack.hpp"
#include <ncurses.h>
#include <unistd.h>

/*********************************************************************
** Description: Default constructor. Sets number of items in pack to zero.
*********************************************************************/
Backpack::Backpack() {
	numItems = 0;
}

/*********************************************************************
** Description: Menu function that displays current items in the pack.
Function allows user to move a cursor by pressing the 'w' and 's' keys.
Then the user presses 'e' to equip a selected item.
*********************************************************************/
void Backpack::packMenu() {
	nodelay(stdscr, FALSE);
	
	backpack[0][0] = '>';

	clear();

	printw("Backpack Menu\n");
	
	for (int i = 0; i < backpackSize; i++) {
		for (unsigned int j = 0; j < backpack[i].length(); j++) {
			char temp = backpack[i][j];
			addch(temp);
		}
		printw("\n");
	}

	printw("Use 'w' to move cursor '>' up and 's' to move");
	printw(" cursor down. Press 'e' to equip item. \n");

	int ch;
	int k = 0;

	while ((ch = getch()) != 'e') {
		if (ch == 's') {
			if (k < numItems - 1) {
				(backpack[k])[0] = ' ';

				++k;

				(backpack[k])[0] = '>';
			}
		} else if (ch == 'w') {
			if (k > 0) {
				(backpack[k])[0] = ' ';

				--k;

				(backpack[k])[0] = '>';
			}
		}

		clear();

		printw("Backpack Menu\n");

		for (int i = 0; i < backpackSize; i++) {
			for (unsigned int j = 0; j < backpack[i].length(); j++) {
				char temp = backpack[i][j];
				addch(temp);
			}
			printw("\n");
		}

		printw("Use 'w' to move cursor '>' up and 's' to move");
		printw(" cursor down. Press 'e' to equip item. \n");
	}

	equippedItem = backpack[k][2];

	backpack[k][0] = ' ';

	printw("Item ");

	for (unsigned int j = 0; j < backpack[k].length(); j++) {
		char temp = backpack[k][j];
		addch(temp);
	}

	printw(" equipped.\n");
	printw("Press any key to continue.\n");

	getch();
	
	nodelay(stdscr, TRUE);
}

/*********************************************************************
** Description: Function used to place an item in the pack. Pack contains
a maximum of three items. Takes a char as input representing the current
item picked up as it appears on teh map.
*********************************************************************/
void Backpack::placeItem(char input) {
	if (input == 'K') {
		backpack[1] = "  Key";
	} else if (input == 'P') {
		backpack[0] = "  Phone";
	} else if (input == 'S') {
		backpack[2] = "  Speaker";
	}
	numItems++;
} 

/*********************************************************************
** Description: Returns a char representing the current item that is
equipped by the user.
*********************************************************************/
char Backpack::getEquippedItem() {
	return equippedItem;
}