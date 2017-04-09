/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for Building class. Base class
for size derived classes. Contains a default constructor, constructor,
printMap functions, get mapChar function, wallItemCheck function,
getDoorOpen function, resetDoor function, changeBuilding function, getGameWon
and getName function. This class is an abstract base class.
*********************************************************************/

#include "Building.hpp"
#include <ncurses.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>

/*********************************************************************
** Description: Default constructor for building class. Sets pointers
to NULL.
*********************************************************************/
Building::Building() {
	name = "";
	north = NULL;
	east = NULL;
	south = NULL;
	west = NULL;
}

/*********************************************************************
** Description: Constructor for Building class. Takes as parameters
pointers that represent the links that the derived classes will have to
each other. Most rooms will have NULL pointers representing a direction
that does not have a connecting room.
*********************************************************************/
Building::Building(std::string nameIn, Building* northIn, Building* eastIn, 
				   Building* southIn, Building* westIn, Student* heroIn) {
	name = nameIn;
	north = northIn;
	east = eastIn;
	south = southIn;
	west = westIn;
	doorOpen = " ";
	hero = heroIn;
	objectPickedUp = false;	
}

/*********************************************************************
** Description: Function to print the contents of a map. Virtual function
that is defined in classes using this class. Iterates through a vector
containing strings that are the current room map. addch function is a 
print function in ncurses. Printw is also a print function.
*********************************************************************/
void Building::printMap() {
	std::vector<std::string>::iterator it;

	for (it = map.begin(); it != map.end(); it++) {
		for (unsigned int i = 0; i < (*it).length(); i++) {
			char temp = (*it)[i];
			addch(temp);
		}
		printw("\n");
	}
}

/*********************************************************************
** Description: Prints a map that is a combination of a derived Building
classes blankMap and startMap.  Prints startMap squares that are located
close to the user. Prints blankMap squares that are located farther away.
This gives the illusion that the user is in the dark and can only see
a certain amount of squares in front of them.
*********************************************************************/
void Building::printDarkMap() {
	std::vector<std::string> combinedMap = blankMap;
	std::vector<std::string> darkMap = blankMap;
	std::vector<std::string>::iterator it;

	int xPos = 0;
	int yPos = 0;

	for (it = darkMap.begin(); it != darkMap.end(); it++) {
		for (unsigned int i = 0; i < (*it).length(); i++) {
			char temp = (*it)[i];

			(combinedMap[xPos])[yPos] = temp;

			yPos++;
		}	
		yPos = 0;
		xPos++;
	}

	xPos = 0;
	yPos = 0;

	std::vector<std::string>::iterator it2;

	for (it2 = map.begin(); it2 != map.end(); it2++) {
		for (unsigned int i = 0; i < (*it2).length(); i++) {
			if ((xPos > (hero->getYPos() - 3) && xPos < (hero->getYPos() + 3)) && 
				(yPos < (hero->getXPos() + 5) && (yPos > hero->getXPos() - 5))) {
				(combinedMap[xPos])[yPos] = (*it2)[i];
			}	
			yPos++;
		}
		yPos = 0;
		xPos++;
	}

	std::vector<std::string>::iterator it3;

	for (it3 = combinedMap.begin(); it3 != combinedMap.end(); it3++) {
		for (unsigned int i = 0; i < (*it3).length(); i++) {
			char temp = (*it3)[i];
			addch(temp);
		}
		printw("\n");
	}
}

/*********************************************************************
** Description: Get function to return a map char at a specific index.
Used in functions to check spaces in front of characters.
*********************************************************************/
char Building::getMapChar(int xCoord, int yCoord) {
	return map[yCoord][xCoord];
}

/*********************************************************************
** Description: Function to check if a character in front of a Student
or Zombie is something other than a blank space. Conditional used to
check what the user's current input is. Checks the direction the user
is facing and either rotates the user or if the user if facing the correct
way will return false. The function has a parameter representing the current
symbol for the user. The parameter is used to check the direction the
user is facing. If the function returns false then the move function for
the user will be called in another location of the program. Also checks
for special input to bring up menus, to investigate, and to interact with
the map. Calls the appropriate function in the event that menus are needed
or action needs to take place.
*********************************************************************/
bool Building::wallItemCheck(char input) {
	char nextPos;
	char nextNextPos;

	if (input == 'w') {
		nextPos = getMapChar(hero->getXPos(), hero->getYPos() - 1);

		if (nextPos == '#' && hero->getIcon() == '^') {
			hero->minusLife();
			return false;
		}

		if (objectPickedUp == true) {
			nextNextPos = getMapChar(hero->getXPos(), hero->getYPos() - 2);
		} else {
			nextNextPos = nextPos;
		}
		
		if (objectPickedUp == true && nextNextPos != ' ' && hero->getIcon() == '^') {
			return true;
		} else if (nextPos != ' ' && hero->getIcon() == '^' && nextPos != 'O') {
			if (nextPos == 'd') {
				doorOpen = "north";
			}

			return true;
		} else if (nextPos == 'O') {
			if (objectPickedUp == false) {
				return true;
			} else if (objectPickedUp == true) {
				return false;
			}
		} else {
			return false;
		}
	} else if (input == 'a') {
		nextPos = getMapChar(hero->getXPos() - 1, hero->getYPos());

		if (nextPos == '#' && hero->getIcon() == '<') {
			hero->minusLife();

			return false;
		}

		if (objectPickedUp == true) {
			nextNextPos = getMapChar(hero->getXPos() - 2, hero->getYPos());
		} else {
			nextNextPos = nextPos;
		}

		if (objectPickedUp == true && nextNextPos != ' ' && hero->getIcon() == '<') {
			return true;
		} else if (nextPos != ' ' && hero->getIcon() == '<' && nextPos != 'O') {
			if (nextPos == 'd') {
				doorOpen = "west";
			}

			return true;
		} else if (nextPos == 'O' && hero->getIcon() == '<') {
			if (objectPickedUp == false) {
				return true;
			} else if (objectPickedUp == true) {
				return false;
			}
		} else {
			return false;
		}
	} else if (input == 's') {
		nextPos = getMapChar(hero->getXPos(), hero->getYPos() + 1);

		if (nextPos == '#' && hero->getIcon() == 'v') {
			hero->minusLife();
			return false;
			
		}

		if (objectPickedUp == true) {
			nextNextPos = getMapChar(hero->getXPos(), hero->getYPos() + 2);
		} else {
			nextNextPos = nextPos;
		}

		if (objectPickedUp == true && nextNextPos != ' ' && hero->getIcon() == 'v') {
			return true;
		} else if (nextPos != ' ' && hero->getIcon() == 'v' && nextPos != 'O') {
			if (nextPos == 'd') {
				doorOpen = "south";
			}

			return true;
		} else if (nextPos == 'O') {
			if (objectPickedUp == false) {
				return true;
			} else if (objectPickedUp == true) {
				return false;
			}
		} else {
			return false;
		}
	} else if (input == 'd') {
		nextPos = getMapChar(hero->getXPos() + 1, hero->getYPos());

		if (nextPos == '#' && hero->getIcon() == '>') {
			hero->minusLife();
			return false;
			
		}

		if (objectPickedUp == true) {
			nextNextPos = getMapChar(hero->getXPos() + 2, hero->getYPos());
		} else {
			nextNextPos = nextPos;
		}

		if (objectPickedUp == true && nextNextPos != ' ' && hero->getIcon() == '>') {
			return true;
		} else if (nextPos != ' ' && hero->getIcon() == '>' && nextPos != 'O') {
			if (nextPos == 'd') {
				doorOpen = "east";
			}

			return true;
		} else if (nextPos == 'O' && hero->getIcon() == '>') {
			if (objectPickedUp == false) {
				return true;
			} else if (objectPickedUp == true) {
				return false;
			}
		} else {
			return false;
		}
	} else if (input == 'f') {
		if (hero->getIcon() == '^') {
			nextPos = getMapChar(hero->getXPos(), hero->getYPos() - 1);
		} else if (hero->getIcon() == '<') {
			nextPos = getMapChar(hero->getXPos() - 1, hero->getYPos());
		} else if (hero->getIcon() == 'v') {
			nextPos = getMapChar(hero->getXPos(), hero->getYPos() + 1);
		} else if (hero->getIcon() == '>') {
			nextPos = getMapChar(hero->getXPos() + 1, hero->getYPos());
		}

		hero->investigate(nextPos);

		return true;

	} else if (input == 'e') {
		if (hero->getIcon() == '^') {
			nextPos = getMapChar(hero->getXPos(), hero->getYPos() - 1);
		} else if (hero->getIcon() == '<') {
			nextPos = getMapChar(hero->getXPos() - 1, hero->getYPos());
		} else if (hero->getIcon() == 'v') {
			nextPos = getMapChar(hero->getXPos(), hero->getYPos() + 1);
		} else if (hero->getIcon() == '>') {
			nextPos = getMapChar(hero->getXPos() + 1, hero->getYPos());
		}

		actionCall(nextPos);

		return true;

	} else if (input == 'i') {
		hero->backpackMenu();
		
		return true;
	}
	return false;
}

/*********************************************************************
** Description: Returns a string representing the direction of the door
that is being walked through. Used to ensure that the correct pointer is
being accessed to change the current map.
*********************************************************************/
std::string Building::getDoorOpen() {
	return doorOpen;
}

/*********************************************************************
** Description: Function to reset the door string after it has been
used to change the map.
*********************************************************************/
void Building::resetDoor() {
	doorOpen = " ";
}

/*********************************************************************
** Description: Returns a pointer representing the building that is the
new map location that the character has moved to. Takes a parameter
representing the direction of the door walked through.
*********************************************************************/
Building* Building::changeBuilding(std::string direction) {
	if (direction == "north") {
		return north;
	} else if (direction == "east") {
		return east;
	} else if (direction == "south") {
		return south;
	} else {
		return west;
	}
}

/*********************************************************************
** Description: Virtual function returns false for all derived classes
except the final level.
*********************************************************************/
bool Building::getGameWon() {
	return false;
}

/*********************************************************************
** Description: Returns a string representing the current building name.
*********************************************************************/
std::string Building::getName() {
	return name;
}