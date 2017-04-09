/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for derived class from Building
base class. Class contains a constructor, setMap function, updateMap function,
printMap function, actionCall function, getType and setPtrs function.
*********************************************************************/

#include "ChemicalZone.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

/*********************************************************************
** Description: Constructor for ChemicalZone class. Takes as parameters
to Building pointers and a Student pointer. The Building pointers represent
buildings that are connected to this building and are used to initialize
the pointers for this class. Also sets bool value that can be altered
through player interaction. Calls setMap function to populate the map vectors
of the class.
*********************************************************************/
ChemicalZone::ChemicalZone(Building* Gilbert, Building* Bexell, Student* hero) : 
	Building("Gleeson Hall", Gilbert, NULL, NULL, Bexell, hero) {
	lightsOn = false;
	setMap();
}

/*********************************************************************
** Description: Set map function used to create the 'dark map' and 
'visible map'.  The first blankMap represents the room without the lights
on.  The hero can only see a certain number of squares around them. The
squares that they can see are represented by the StartMap. The startMap
contains '#' special characters representing chemical spills. If a character
walks in these squares the character will lose life.
*********************************************************************/
void ChemicalZone::setMap() {
	blankMap.push_back("   __________ ");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back(" _|          |");
	blankMap.push_back("|            |");
	blankMap.push_back("|            |");
	blankMap.push_back(" -           |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  |          |");
	blankMap.push_back("  -|        |-");
	blankMap.push_back("    |      |  ");
	blankMap.push_back("     ------   ");

	startMap.push_back("   ___d______ ");
	startMap.push_back("  |          |");
	startMap.push_back("  |# # # # # |");
	startMap.push_back("  |# # # # # |");
	startMap.push_back("  |          |");
	startMap.push_back("  | #  #  #  |");
	startMap.push_back(" _| #  #  #  |");
	startMap.push_back("L            |");
	startMap.push_back("|            |");
	startMap.push_back(" -   ########|");
	startMap.push_back("  |          |");
	startMap.push_back("  |          |");
	startMap.push_back("  |########  |");
	startMap.push_back("  |          |");
	startMap.push_back("  d          |");
	startMap.push_back("  -|        |-");
	startMap.push_back("    |      |  ");
	startMap.push_back("     ------   ");
	map = startMap;
}

/*********************************************************************
** Description: Function to update the map as a zombie moves. When a user
does not input anything the map will still update.  When the map updates
the zombie will move forward until it encounters a space that is not blank.
The zombie will then reverse direction and continue. This map contains
no zombies.
*********************************************************************/
void ChemicalZone::updateMap() {
	clear();
	printMap();
	hero->printHealth();
}

/*********************************************************************
** Description: Function to update map if user enters a character.
Print health function displays user health.  The wallItemCheck function checks
to make sure the user has a blank space in front of them before letting
them move. If the character has a blank space in front of them the move
function is called, changing the xCoord and yCoord values of the user.
*********************************************************************/
void ChemicalZone::updateMap(char input) {
	if (!wallItemCheck(input)) {
		hero->move(input);

		map = startMap;

		map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

		clear();
		printMap();
		
		hero->printHealth();
	}
}

/*********************************************************************
** Description: Function to check if the lights are turned on in a room.
If they are not then a map is generated that is a combination of the
start map and blank map. The user will only be able to see a certain
number of squares around them in a dark map. This is done by printing
a portion of the startMap that is surrounded by the blankMap.
*********************************************************************/
void ChemicalZone::printMap() {
	if (!lightsOn) {
		printDarkMap();
	} else {
		std::vector<std::string>::iterator it;
		for (it = map.begin(); it != map.end(); it++) {
			for (unsigned int i = 0; i < (*it).length(); i++) {
				char temp = (*it)[i];
				addch(temp);
			}
			printw("\n");
		}
	}
} 

/*********************************************************************
** Description: Function that takes a parameter representing the character
in front of the user after the user has pressed 'e'. Checks to see if
an item in front of the user can be picked up or changed. Pressing 'e'
while facing a light switch will turn lights on. Also checks if a user
has a certain item equipped. If they do then either a message will
print or a bool will be changed to alter the map.
*********************************************************************/
void ChemicalZone::actionCall(char icon) {
	if (icon == 'L') {
		lightsOn = true;
	} else if (hero->getCurrentItem() == 'P') {
		std::string message = "Almost to Gilbert Hall! Looks like I've got a";
		message += " new text. It says that I should be careful not to step in";
		message += " any chemical spills '#'.";

		writeMessage(message);
	}
}

/*********************************************************************
** Description: Function returns a string used to check the current room
type. Used in the changeBuilding function to access the correct pointers
by checking the current room.
*********************************************************************/
std::string ChemicalZone::getType() {
	return "ChemicalZone";
}

/*********************************************************************
** Description: Sets the zones connected to the current location. These
zones are accessed through 'd' special characters in the map.  When the
character goes through the 'd' door a function is called that sets the
current location equal to one of these pointer values for the building.
*********************************************************************/
void ChemicalZone::setPtrs(Building* northIn, Building* southIn, Building* westIn) {
	north = northIn;
	south = southIn;
	west = westIn;
}