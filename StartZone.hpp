/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for StartZone, derived class from Building
base class. Represents and abstraction of an OSU building a zombie survival
game.
*********************************************************************/

#ifndef STARTZONE_HPP
#define STARTZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include "WriteMessage.hpp"

class StartZone : public Building {
private:
	bool southDoorLocked;
	bool eastDoorLocked;
	bool lightsOn;
	Zombie* enemy;
public:
	StartZone(Student*);
	~StartZone();
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void setPtrs(Building*, Building*, Building*);
	void actionCall(char);
	std::string getType();
};

#endif