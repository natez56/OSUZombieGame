/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for Student a derived class from 
Character base class. Class contains a default constructor, constructor,
destructor, move function, minus life function, addItem function,
backPackMenu function, getCurrentItem function, getHealth function, and
printHealth function.
*********************************************************************/

#include "Student.hpp"
#include <ncurses.h>
#include <unistd.h>
#include "WriteMessage.hpp"
#include <string>

/*********************************************************************
** Description: Default constructor for student class. Initializes
values by calling the Character constructor. Sets values to prevent values
from having random values from memory.
*********************************************************************/
Student::Student() : Character(' ', 0, 0) {
	pack = new Backpack();
	health = -1;
}

/*********************************************************************
** Description: Constructor for Student class. Takes a char, int, and
int parameter to initialize the class. The char represents the character
taht will represent the Student on a map. The int parameters are used
to correctly represent in the coordinates of the Student on the map.
Also creates a backPack object that is a container for items that the
user can pick up. Sets total life to 10.
*********************************************************************/
Student::Student(char icon, int xCoord, int yCoord) : Character(icon, xCoord, 
																yCoord) {
	pack = new Backpack();
	health = 10;
}

/*********************************************************************
** Description: Destructor for Student class. Used to free memory
associated with the Backpack class object created in the constructor.
*********************************************************************/
Student::~Student() {
	delete pack;
}

/*********************************************************************
** Description: Move function used to either rotate the character if
he is not facing the direction of the move command or to move the
character one index position if they are facing the correct direction.
Takes a parameter representing the user input.
*********************************************************************/
void Student::move(char input) {
	if (input == 'w') {
		if (icon == '^' ) {
			yCoord -= 1;
		} else {
			icon = '^';
		}
	} else if (input == 'a') {
		if (icon == '<' ) {
			xCoord -= 1;
		} else {
			icon = '<';
		}
	} else if (input == 's') {
		if (icon == 'v') {
			yCoord += 1;
		} else {
			icon = 'v';
		}
	} else if (input == 'd') {	
		if (icon == '>') {
			xCoord += 1;
		} else {
			icon = '>';
		}
	}
}

/*********************************************************************
** Description: Function to reduce character life. Called when character
gets in the path of a zombie or if they walk in a chemical spill. Prints
a message to the screen notifyuing the user that they have taken damage.
*********************************************************************/
void Student::minusLife() {
	std::string message;
	if (health > 1) {
		health--;
		message = "Oh no. You've been damaged. Be sure to stay away from 'z'";
		message += " zombies and '#' chemical spills in the future.";
		writeMessage(message);
	} else if (health == 1) {
		health--;
		message = "Game over. You have recieved to much damage and run ";
		message += "out of health.";
		writeMessage(message);
	}

}

/*********************************************************************
** Description: Used to print a message explaining some object on the
map. Takes as input a parameter representing the character in front
of the user on the map.
*********************************************************************/
void Student::investigate(char icon) {
	nodelay(stdscr, FALSE);

	if (icon == ' ') {
		printw("Nothing to investigate. \n");
	} else if (icon == 'd') {
		printw("An unlocked door, you may walk through it.\n");
	} else if (icon == 'X') {
		printw("A locked door, use a key to unlock it. \n");
	} else if (icon == 'L') {
		printw("A light switch, press E to flip the switch. \n");
	}

	printw("Press any key to continue.\n");

	getch();

	nodelay(stdscr, TRUE);
}

/*********************************************************************
** Description: Function to add an item to the Students backpack. Takes
a char parameter representing the item to be added.
*********************************************************************/
void Student::addItem(char item) {
	pack->placeItem(item);
}

/*********************************************************************
** Description: Calls the backpack classes menu function to display
a menu showing the current contents of the users item container.
*********************************************************************/
void Student::backpackMenu() {
	pack->packMenu();
}

/*********************************************************************
** Description: Returns a char representing the item that is currently
equipped by the user.
*********************************************************************/
char Student::getCurrentItem() {
	return pack->getEquippedItem();
}

/*********************************************************************
** Description: Returns an int representing the current remaining health
of the user.
*********************************************************************/
int Student::getHealth() {
	return health;
}

/*********************************************************************
** Description: Function to print the users health to the screen.
*********************************************************************/
void Student::printHealth() {
	printw("Current Health Remaining: ");

	int currentHealth = getHealth();

	std::string health = std::to_string(currentHealth);
	
	for (unsigned int i = 0; i < health.length(); i++) {
		char temp = health[i];
		addch(temp);
	}
}

