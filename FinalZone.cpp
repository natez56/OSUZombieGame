/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for derived class from building base
class. Class represents the final level of the game. Contains a constructor, destructor, setMap function, updateMap
function, printMap function, actionCall function, a get function, and a
set pointers function.
*********************************************************************/

#include "FinalZone.hpp"
#include "WriteMessage.hpp"
#include <ncurses.h>
#include <string>
#include <vector>

/*********************************************************************
** Description: Constructor for FinalZone class. Takes as parameters
a Building pointer and a Student pointer. The Building pointer represents
buildings that are connected to this building and are used to initialize
the pointers for this class. Also sets bool value that can be altered
through player interaction. Calls setMap function to populate the map vectors
of the class. gameWon will be changed to true when the user interacts
with the final objective item.
*********************************************************************/
FinalZone::FinalZone(Building* Gleeson, Student* hero) : 
	Building("Gilbert Hall", NULL, NULL, Gleeson, NULL, hero) {
	enemy = new Zombie('z', 1, 10, 1, 0);
	enemy2 = new Zombie('z', 13, 1, 0, 0);
	enemy3 = new Zombie('z', 13, 2, 0, 0);
	enemy4 = new Zombie('z', 13, 3, 0, 0);

	zombieList.push_back(enemy);
	zombieList.push_back(enemy2);
	zombieList.push_back(enemy3);
	zombieList.push_back(enemy4);

	lightsOn = false;
	objectPickedUp = false;
	gameWon = false;

	setMap();
}

/*********************************************************************
** Description: Destructor used to free memory associated with enemies
and debris on the map.
*********************************************************************/
FinalZone::~FinalZone() {
	delete enemy;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;

	std::vector<Debris*>::iterator it;

	for (it = debrisVector.begin(); it != debrisVector.end(); it++) {
		delete (*it);
	}
}

/*********************************************************************
** Description: Set map function used to create the 'dark map' and 
'visible map'.  The first blankMap represents the room without the lights
on.  The hero can only see a certain number of squares around them. The
squares that they can see are represented by the StartMap. Also sets the
location of debris represented by 'O'. A vector is used because it is
necessary to access each debris position so that it's coordinates can
be changed. Then the for loop will print the new position of the 
debris by replacing the map vector value at the appropriate index.
*********************************************************************/
void FinalZone::setMap() {
	blankMap.push_back("      ____________________            ");
	blankMap.push_back("     /                    \\__        ");
	blankMap.push_back("    /                         \\__    ");
	blankMap.push_back("   /                              \\  ");
	blankMap.push_back("  /         --                    / _ ");
	blankMap.push_back(" /         /  \\--               // / ");
	blankMap.push_back("|         /       \\--          _ _/  ");
	blankMap.push_back("|        |            \\--     /      ");
	blankMap.push_back("|        |                \\--/       ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|        |                            ");
	blankMap.push_back("|       ---------                     ");
	blankMap.push_back("|                |                    ");
	blankMap.push_back("|       ---------                     ");
	blankMap.push_back("--------|                             ");

	startMap.push_back("      ____________________            ");
	startMap.push_back("     /                    \\__        ");
	startMap.push_back("    /                         \\__    ");
	startMap.push_back("   /                              \\  ");
	startMap.push_back("  /         --                    / _ ");
	startMap.push_back(" /         /  \\--           R   // / ");
	startMap.push_back("|         /       \\--          _ _/  ");
	startMap.push_back("|        |            \\--     /      ");
	startMap.push_back("|  ######|                \\--/       ");
	startMap.push_back("|        |                            ");
	startMap.push_back("|        |                            ");
	startMap.push_back("|        |                            ");
	startMap.push_back("|#####   |                            ");
	startMap.push_back("|        |                            ");
	startMap.push_back("|        |                            ");
	startMap.push_back("|       ---------                     ");
	startMap.push_back("|                L                    ");
	startMap.push_back("|       ---------                     ");
	startMap.push_back("---d----|                             ");

	map = startMap;

	if (objectPickedUp == true) {
		if (hero->getIcon() == 'v') {
			map[hero->getYPos() + 1][hero->getXPos()] = 'O';
		} else if (hero->getIcon() == '<') {
			map[hero->getYPos()][hero->getXPos() - 1] = 'O';
		} else if (hero->getIcon() == '>') {
			map[hero->getYPos()][hero->getXPos() + 1] = 'O';
		} else if (hero->getIcon() == '^') {
			map[hero->getYPos() - 1][hero->getXPos()] = 'O';
		}	
	}

	int count = 0;
	int xPos = 22;
	int yPos = 1;

	for (int i = 0; i < 5; i++) {
		if (count == 1) {
			yPos++;
			count = 0;
			xPos = 22;
		}
		Debris* objectTemp = new Debris(xPos, yPos);
		debrisVector.push_back(objectTemp);
		count++;
	}

	Debris* frontObject = new Debris(8, 2);
	debrisVector.push_back(frontObject);

	std::vector<Zombie*>::iterator it;

	for (it = zombieList.begin(); it != zombieList.end(); it++) {
		map[(*it)->getYPos()][(*it)->getXPos()] = (*it)->getIcon();
	}
}

/*********************************************************************
** Description: Function to update the map as a zombie moves. When a user
does not input anything the map will still update.  When the map updates
the zombie will move forward until it encounters a space that is not blank.
The zombie will then reverse direction and continue. Also prints hero
position. Conditionals check if the user is currently holding debris.
If the user is then the debris will show one square in front of the user
and will continue to stay in front of the user when the user moves.
*********************************************************************/
void FinalZone::updateMap() {
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

	if (objectPickedUp == true) {
		if (hero->getIcon() == 'v') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() + 1;

			} else if (hero->getIcon() == '<') {
				debrisVector[objectNum]->debrisX = hero->getXPos() - 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '>') {
				debrisVector[objectNum]->debrisX = hero->getXPos() + 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '^') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() - 1;
			}		
	}

	std::vector<Debris*>::iterator it2;

	for (it2 = debrisVector.begin(); it2 != debrisVector.end(); it2++) {
		map[(*it2)->debrisY][(*it2)->debrisX] = 'O';
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
Zombie positions are also updated. Also checks if a character is holding
debris. If they are, the debris will show up in one square in front of
them and will update when the character moves.  Continues until the
user drops the item.
*********************************************************************/
void FinalZone::updateMap(char input) {
	if (!wallItemCheck(input)) {
		hero->move(input);

		map = startMap;

		map[hero->getYPos()][hero->getXPos()] = hero->getIcon();

		if (objectPickedUp == true) {
			if (hero->getIcon() == 'v') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() + 1;

			} else if (hero->getIcon() == '<') {
				debrisVector[objectNum]->debrisX = hero->getXPos() - 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '>') {
				debrisVector[objectNum]->debrisX = hero->getXPos() + 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '^') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() - 1;
			}	
		}

		std::vector<Debris*>::iterator it2;

		for (it2 = debrisVector.begin(); it2 != debrisVector.end(); it2++) {
			map[(*it2)->debrisY][(*it2)->debrisX] = 'O';
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
void FinalZone::printMap() {
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
print or a bool will be changed to alter the map. Also checks if an item
has been picked up. Once an item is picked up the conditionals check
two spaces in front of the character, this way the object they are holding
will not pass through walls. Also prevent user from passing through other
debris when they are holding debris.
*********************************************************************/
void FinalZone::actionCall(char icon) {
	if (icon == 'L') {
		lightsOn = true;
	} else if (icon == 'O') {
		if (objectPickedUp) {
			if (hero->getIcon() == 'v') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() + 1;

			} else if (hero->getIcon() == '<') {
				debrisVector[objectNum]->debrisX = hero->getXPos() - 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '>') {
				debrisVector[objectNum]->debrisX = hero->getXPos() + 1;
				debrisVector[objectNum]->debrisY = hero->getYPos();

			} else if (hero->getIcon() == '^') {
				debrisVector[objectNum]->debrisX = hero->getXPos();
				debrisVector[objectNum]->debrisY = hero->getYPos() - 1;
			}

			objectPickedUp = false;
		} else {
			objectPickedUp = true;

			std::vector<Debris*>::iterator it2;

			int debrisNum = 0;

			for (it2 = debrisVector.begin(); it2 != debrisVector.end(); it2++) {
				if (hero->getIcon() == 'v') {
					if ((*it2)->debrisY == hero->getYPos() + 1 && 
				  	    (*it2)->debrisX == hero->getXPos()) {
						objectNum = debrisNum;
					}
				} else if (hero->getIcon() == '<') {
					if ((*it2)->debrisY == hero->getYPos() && 
				  	    (*it2)->debrisX == hero->getXPos() - 1) {
						objectNum = debrisNum;
					}
				} else if (hero->getIcon() == '>') {
					if ((*it2)->debrisY == hero->getYPos() && 
				  	    (*it2)->debrisX == hero->getXPos() + 1) {
						objectNum = debrisNum;
					}
				} else if (hero->getIcon() == '^') {
					if ((*it2)->debrisY == hero->getYPos() - 1 && 
				  	    (*it2)->debrisX == hero->getXPos()) {
						objectNum = debrisNum;
					}
				}

				debrisNum++;
			}
		}
	} else if (icon == 'z' && hero->getCurrentItem() == 'S') {
		std::vector<Zombie*>::iterator it;

		int speed = 90;

		for (it = zombieList.begin(); it != zombieList.end(); it++) {
			(*it)->setDirection(1, 1, 1, 0);
			(*it)->setSpeed(speed);
			speed -= 10;
		}

	} else if (icon == 'R') {
		gameWon = true;
	} else if (hero->getCurrentItem() == 'P') {
		std::string message = "Finally I've made it. My friend tells me they";
		message += " had to evacuate the building in a hurry. They've left";
		message += " the antidote they've created for me to find near the";
		message += " other end of the building. With the antidote I should";
		message += " become immune to the outbreak.";

		writeMessage(message);
	}
}

/*********************************************************************
** Description: Function returns a string used to check the current room
type. Used in the changeBuilding function to access the correct pointers
by checking the current room.
*********************************************************************/
std::string FinalZone::getType() {
	return "FinalZone";
}

/*********************************************************************
** Description: Returns a bool variable that represents the state of the
game. Is called to check if the player has reached the objective and
completed the game.
*********************************************************************/
bool FinalZone::getGameWon() {
	if (gameWon == true) {
		return true;
	} else {
		return false;
	}
}