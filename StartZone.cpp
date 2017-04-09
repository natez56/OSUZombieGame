/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for StartZone class, class derived
from Building class. Program simulates the first level in a zombie adventure.
Has a constructor, setMap function, updateMap function, actionCall function,
setPtrs, printMap, and getType function. To run the class simply call the
constructor with the required parameters.
*********************************************************************/

#include "StartZone.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

/*********************************************************************
** Description: Constructor for StartZone class. Takes a Student pointer
as a parameter. uses the Building constructor to initialize the name,
and Building* nodes. Creates a zombie that is represented on the map
by 'z'. Calls the setMap function to create the map that the hero will
be pictured in.
*********************************************************************/
StartZone::StartZone(Student* hero) : 
	Building("Kelley Engineering Center", NULL, NULL, NULL, NULL, hero) {
	enemy = new Zombie('z', 2, 8, 1, 0);
	lightsOn = false;
	southDoorLocked = true;
	eastDoorLocked = true;
	setMap();
}

/*********************************************************************
** Description: Destructor for enemy. deletes memory associated with
the zombie.
*********************************************************************/
StartZone::~StartZone() {
	delete enemy;
}

/*********************************************************************
** Description: Set map function used to create the 'dark map' and 
'visible map'.  The first blankMap represents the room without the lights
on.  The hero can only see a certain number of squares around them. The
squares that they can see are represented by the StartMap. Also sets the
location of the locked doors on the map.
*********************************************************************/
void StartZone::setMap() {
	blankMap.push_back("           ___________________ ");
	blankMap.push_back("           |                  |");
	blankMap.push_back("         __|                  |");
	blankMap.push_back("        |                    _|");
	blankMap.push_back("        |                   |  ");
	blankMap.push_back("________|                   |  ");
	blankMap.push_back("|                           |_ ");
	blankMap.push_back("|                             |");
	blankMap.push_back("|                             |");
	blankMap.push_back("|                             |");
	blankMap.push_back("-------------------------------");

	startMap.push_back("           ___________________ ");
	startMap.push_back("           |                  |");
	startMap.push_back("         __|                  |");
	startMap.push_back("        |                    _|");
	startMap.push_back("        L                   |  ");
	startMap.push_back("________|                   |  ");
	startMap.push_back("|                           |_ ");
	startMap.push_back("|                             |");
	startMap.push_back("d                             d");
	startMap.push_back("|                             |");
	startMap.push_back("---------d---------------------");

	map = startMap;

	if (southDoorLocked) {
		map[10][9] = 'X';
	}
	if (eastDoorLocked) {
		map[8][30] = 'X';
	}

	map[hero->getYPos()][hero->getXPos()] = hero->getIcon();
	map[enemy->getYPos()][enemy->getXPos()] = enemy->getIcon();
}

/*********************************************************************
** Description: Function to update the map as a zombie moves. When a user
does not input anything the map will still update.  When the map updates
the zombie will move forward until it encounters a space that is not blank.
The zombie will then reverse direction and continue. Also checks if any
of the doors have been opened. If they have the doors will change from
'X' to 'd'.
*********************************************************************/
void StartZone::updateMap() {
	char nextPos = getMapChar(enemy->getXPos() + enemy->getXDirection(), 
							  enemy->getYPos());

	if (nextPos == '<' || nextPos == '^' || nextPos == '>' || nextPos == 'v') {
		hero->minusLife();
	}

	if (nextPos != ' ') {
		enemy->setDirection(-1, 0, 0, 0);
		enemy->move();
	} else {
		enemy->move();
	}

	map = startMap;

	if (southDoorLocked) {
		map[10][9] = 'X';
	}

	if (eastDoorLocked) {
		map[8][30] = 'X';
	}

	map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

	map[enemy->getYPos()][enemy->getXPos()] = enemy->getIcon();

	clear();

	printMap();

	hero->printHealth();
}

/*********************************************************************
** Description: Function to update map if user enters a character.
Checks to see if any of the doors have been unlocked.  Will update
the characters position as long as his next position is a blank space.
*********************************************************************/
void StartZone::updateMap(char input) {
	if (!wallItemCheck(input)) {

		hero->move(input);

		map = startMap;

		if (southDoorLocked) {
			map[10][9] = 'X';
		}

		if (eastDoorLocked) {
			map[8][30] = 'X';
		}

		map[hero->getYPos()][hero->getXPos()] = hero->getIcon();
		map[enemy->getYPos()][enemy->getXPos()] = enemy->getIcon();

		clear();

		printMap();

		hero->printHealth();
	}
}

/*********************************************************************
** Description: Used to allow the hero to interact with the map. If the
hero is facing a special character such as L or X then the character can
press 'e' to interact with the space. Once they press 'e' this function
is called to update bool variables which are checked in the other functions.
The map is updated once these bool variables are changed. Takes a char
representing the position in front of the hero.
*********************************************************************/
void StartZone::actionCall(char icon) {
	if (icon == 'L') {
		lightsOn = true;
	} else if (icon == 'X' &&  hero->getCurrentItem() == 'K') {
		if (hero->getXPos() == 9) {
			southDoorLocked = false;
		} else if (hero->getXPos() == 29) {
			eastDoorLocked = false;
		}
	} else if (hero->getCurrentItem() == 'P') {
		std::string message = "You look at your phone. There's an emergency";
		message += " warning stating that there has been an outbreak of a ";
		message += "mysterious disease. Your friend at oregon state has also";
		message += " texted. Oh no!!! Your friend's text says the mysterious";
		message += " disease is causing people to turn into zombies! Your";
		message += " friend says to make your way to Gilbert Hall the chemistry";
		message += " building where they are working on an antidote... It's ";
		message += " probably a good idea to check my phone each time I enter";
		message += " a new room. Now I should look for a light switch 'L' to";
		message += " turn on the lights. Right now I can only see a few ";
		message += "squares around me. There should be a light switch in";
		message += " each room.";

		writeMessage(message);
	}
}

/*********************************************************************
** Description: Sets the zones connected to the current location. These
zones are accessed through 'd' special characters in the map.  When the
character goes through the 'd' door a function is called that sets the
current location equal to one of these pointer values for the building.
*********************************************************************/
void StartZone::setPtrs(Building* eastIn, Building* southIn, Building* westIn) {
	east = eastIn;
	south = southIn;
	west = westIn;
}

/*********************************************************************
** Description: Function to check if the map with the lights out needs
to be printed or if just the regular map needs to be printed. The darkmap
function will print the startMap map for a certain number of squares around
the character, the rest of the squares will be comprised of the blank map
map.
*********************************************************************/
void StartZone::printMap() {
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
** Description: Get function to return the type of the map
*********************************************************************/
std::string StartZone::getType() {
	return "StartZone";
}

