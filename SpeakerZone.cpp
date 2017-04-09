/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for SpeakerZone class. File contains
a constructor, destructor, setMap, updateMap, printMap, actionCall, and
getType functions.
*********************************************************************/

#include "SpeakerZone.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

/*********************************************************************
** Description: Constructor for FinalZone class. Takes as parameters
a Building pointer and a Student pointer. The Building pointer represents
buildings that are connected to this building and are used to initialize
the pointers for this class. Also sets bool value that can be altered
through player interaction. Calls setMap function to populate the map vectors
of the class. Creates enemy zombies and initializes them to the correct
position on the map. setMap function called to populate the map vectors.
*********************************************************************/
SpeakerZone::SpeakerZone(Building* Kelley, Student* hero) : 
	Building("Milam Hall", Kelley, NULL, NULL, NULL, hero) {
	enemy = new Zombie('z', 39, 5, 0, 0);
	enemy2 = new Zombie('z', 39, 6, 0, 0);
	enemy3 = new Zombie('z', 39, 7, 0, 0);
	enemy4 = new Zombie('z', 39, 8, 0, 0);
	enemy5 = new Zombie('z', 39, 9, 0, 0);
	enemy6 = new Zombie('z', 39, 10, 0, 0);

	zombieList.push_back(enemy);
	zombieList.push_back(enemy2);
	zombieList.push_back(enemy3);
	zombieList.push_back(enemy4);
	zombieList.push_back(enemy5);
	zombieList.push_back(enemy6);

	lightsOn = false;
	stereoFound = false;

	setMap();
}

/*********************************************************************
** Description: Destructor used to free memory associated with the Zombie's
on the map.
*********************************************************************/
SpeakerZone::~SpeakerZone() {
	delete enemy;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;
	delete enemy6;
}

/*********************************************************************
** Description: Set map function used to create the 'dark map' and 
'visible map'.  The first blankMap represents the room without the lights
on.  The hero can only see a certain number of squares around them. The
squares that they can see are represented by the StartMap. Sets the location of
the stereo in the map. If the stereo is found then the map will be updated
to no longer show the stereo symbol.
*********************************************************************/
void SpeakerZone::setMap() {
	blankMap.push_back("       ____________                       __________ ");
	blankMap.push_back("       |           |                     |          |");
	blankMap.push_back("       |           |                     |          |");
	blankMap.push_back("       |           |   _______________   |          |");
	blankMap.push_back("       |           |__|               |__|          |");
	blankMap.push_back("       |                                            |");
	blankMap.push_back("       |                                            |");
	blankMap.push_back("       |                                            |");
	blankMap.push_back("       |                                            |");
	blankMap.push_back("   ____|                                            |");
	blankMap.push_back("  _|                                                |");
	blankMap.push_back("_|                 ---                ---           |");
	blankMap.push_back("|                 |   |              |   |          |");
	blankMap.push_back("|_                |    --------------    |          |");
	blankMap.push_back("  |               |                      |          |");
	blankMap.push_back("  -----------------                      ------------");

	startMap.push_back("       ____________                       __________ ");
	startMap.push_back("       |           |                     |          |");
	startMap.push_back("       |           |                     |          |");
	startMap.push_back("       L           |   _______d_______   |          |");
	startMap.push_back("       |           |__|               |__|          |");
	startMap.push_back("       |                                            |");
	startMap.push_back("       |                                            |");
	startMap.push_back("       |                                            |");
	startMap.push_back("       |                                            |");
	startMap.push_back("   ____|                                            |");
	startMap.push_back("  _|                                                |");
	startMap.push_back("_|                 ---                ---           |");
	startMap.push_back("|                 |   |              |   |          |");
	startMap.push_back("|_                |    --------------    |          |");
	startMap.push_back("  |               |                      |          |");
	startMap.push_back("  -----------------                      ------------");

	map = startMap;

	if (!stereoFound) {
		map[13][4] = 'S';
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
The zombie will then reverse direction and continue.
*********************************************************************/
void SpeakerZone::updateMap() {
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

	if (!stereoFound) {
		map[13][4] = 'S';
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
Print health function displays user health.  The wallItemCheck function checks
to make sure the user has a blank space in front of them before letting
them move. If the character has a blank space in front of them the move
function is called, changing the xCoord and yCoord values of the user.
*********************************************************************/
void SpeakerZone::updateMap(char input) {
	if (!wallItemCheck(input)) {

		hero->move(input);

		map = startMap;

		map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

		if (!stereoFound) {
			map[13][4] = 'S';
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
void SpeakerZone::printMap() {
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
void SpeakerZone::actionCall(char icon) {
	if (icon == 'L') {
		lightsOn = true;
	} else if (icon == 'S') {
		hero->addItem('S');
		stereoFound = true;
	} else if (icon == 'z' && hero->getCurrentItem() == 'S') {
		std::vector<Zombie*>::iterator it;
		int speed = 90;
		for (it = zombieList.begin(); it != zombieList.end(); it++) {
			(*it)->setDirection(1, 1, 1, 0);
			(*it)->setSpeed(speed);
			speed -= 10;
		}
	} else if (hero->getCurrentItem() == 'P') {
		std::string message = "Another text! My friend says that some of the";
		message += " zombies are behaving funny. They seem to like to line up";
		message += " and go to sleep. Not much can wake them up when they do";
		message += " this. If only I could find something to make a bunch of";
		message += " noise...";

		writeMessage(message);
	}
}

/*********************************************************************
** Description: Function returns a string used to check the current room
type. Used in the changeBuilding function to access the correct pointers
by checking the current room.
*********************************************************************/
std::string SpeakerZone::getType() {
	return "SpeakerZone";
}