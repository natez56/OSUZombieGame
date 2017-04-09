/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for KeyZone derived class from Building
base class. Used to represent the second level of the game. Has a constructor
desctructor, set map function, update map function, print map function,
actionCall, and getType function. To use the class use the constructor and
pass the appropriate parameters to initialize the Building pointers.
*********************************************************************/

#include "KeyZone.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

/*********************************************************************
** Description: Default constructor for KeyZone class. Takes a Building
pointer and a student pointer as parameters. The building pointer is
used to initialize the pointer variables required to update map when
a door is encountered.  Also, initializes bool variables triggered by
user interaction. Creates enemy zombies and sets their move speed and
position on the map. Calls the setMap function to fill the map vectors
so that the maps can be printed to the screen.
*********************************************************************/
KeyZone::KeyZone(Building* Kelley, Student* hero) : 
	Building("Ballard Extension Hall", NULL, Kelley, NULL, NULL, hero) {
	enemy = new Zombie('z', 7, 7, 1, 0);
	enemy2 = new Zombie('z', 11, 12, 1, 0);
	enemy3 = new Zombie('z', 15, 17, 1, 0);

	zombieList.push_back(enemy);
	zombieList.push_back(enemy2);
	zombieList.push_back(enemy3);

	lightsOn = false;
	keyFound = false;

	setMap();
}

/*********************************************************************
** Description: Destructor for the zombie class. Frees memory associated
with the created enemies.
*********************************************************************/
KeyZone::~KeyZone() {
	delete enemy;
	delete enemy2;
	delete enemy3;
}

/*********************************************************************
** Description: Set map function used to create the 'dark map' and 
'visible map'.  The first blankMap represents the room without the lights
on.  The hero can only see a certain number of squares around them. The
squares that they can see are represented by the StartMap. Also sets the
location of the locked doors on the map. Key character is set to replace
vector value at appropriate index. If the bool is true it means the
user has picked up the key. The key will then no longer show on the map.
*********************************************************************/
void KeyZone::setMap() {
	blankMap.push_back("__________________     ");
	blankMap.push_back("|                 |    ");
	blankMap.push_back("|                 |    ");
	blankMap.push_back("---               |    ");
	blankMap.push_back("   |              |    ");
	blankMap.push_back("   ---            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("     |            |    ");
	blankMap.push_back("   ---            |    ");
	blankMap.push_back("   |              |    ");
	blankMap.push_back("----              -----");
	blankMap.push_back("|                     |");
	blankMap.push_back("|                     |");
	blankMap.push_back("-----------------------");

	startMap.push_back("__________________     ");
	startMap.push_back("|                 |    ");
	startMap.push_back("|                 L    ");
	startMap.push_back("---               |    ");
	startMap.push_back("   |              |    ");
	startMap.push_back("   ---            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("     |            |    ");
	startMap.push_back("   ---            |    ");
	startMap.push_back("   |              |    ");
	startMap.push_back("----              -----");
	startMap.push_back("|                     d");
	startMap.push_back("|                     |");
	startMap.push_back("-----------------------");

	map = startMap;
	
	if (!keyFound) {
		map[2][5] = 'K';
	}

	std::vector<Zombie*>::iterator it;

	for (it = zombieList.begin(); it != zombieList.end(); it++) {
		map[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getIcon();
	}
}

/*********************************************************************
** Description: Function to update the map as a zombie moves. When a user
does not input anything the map will still update.  When the map updates
the zombie will move forward until it encounters a space that is not blank.
The zombie will then reverse direction and continue. Also checks if any
if a user has picked up a key by facing it and pressing 'e'. The key
will no longer show up on the map once a user has picked it up.
*********************************************************************/
void KeyZone::updateMap() {
	char nextPos;

	std::vector<Zombie*>::iterator it;

	for (it = zombieList.begin(); it != zombieList.end(); it++) {
		nextPos = getMapChar((*it)->getXPos() + (*it)->getXDirection(), 
							 (*it)->getYPos());

		if (nextPos == '<' || nextPos == '^' || nextPos == '>' || nextPos == 'v') {
			hero->minusLife();
		}	

		if (nextPos != ' ') {
			(*it)->setDirection(-1, 0, 0, 0);
			(*it)->move();
		} else {
			(*it)->move();
		}
	}

	
	map = startMap;

	map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

	if (!keyFound) {
		map[2][5] = 'K';
	}

	for (it = zombieList.begin(); it != zombieList.end(); it++) {
		map[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getIcon();
	}

	clear();
	printMap();

	hero->printHealth();
}

/*********************************************************************
** Description: Function to update map if user enters a character.
Checks to see if key is picked up.  The wallItemCheck function checks
to make sure the user has a blank space in front of them before letting
them move. If the character has a blank space in front of them the move
function is called, changing the xCoord and yCoord values of the user.
Zombie positions are also updated.
*********************************************************************/
void KeyZone::updateMap(char input) {
	if (!wallItemCheck(input)) {
		hero->move(input);

		map = startMap;

		map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

		if (!keyFound) {
			map[2][5] = 'K';
		}

		std::vector<Zombie*>::iterator it;

		for (it = zombieList.begin(); it != zombieList.end(); it++) {
			map[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getIcon();
		}

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
void KeyZone::printMap() {
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
void KeyZone::actionCall(char icon) {
	if (icon == 'L') {
		lightsOn = true;
	} else if (icon == 'K') {
		hero->addItem('K');
		
		keyFound = true;
	} else if (hero->getCurrentItem() == 'P') {
		std::string message = "Another text! My friend says that some of the";
		message += " doors around OSU are locked. I should look for a key 'K'";
		message += " to unlock them. My friend also says that they've found ";
		message += "that zombies can only hurt you if you get in their ";
		message += "walking path and they touch you. So as long as they ";
		message += "aren't facing you you can run into them.";

		writeMessage(message);
	}
}

/*********************************************************************
** Description: Function returns a string used to check the current room
type. Used in the changeBuilding function to access the correct pointers
by checking the current room.
*********************************************************************/
std::string KeyZone::getType() {
	return "KeyZone";
}