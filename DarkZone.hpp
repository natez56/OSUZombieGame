/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for DarkZone class, a derived class from
Building base class. Represents the abstraction of a OSU building in a
zombie survival game.
*********************************************************************/

#ifndef DARKZONE_HPP
#define DARKZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include <vector>
#include <string>
#include "WriteMessage.hpp"

class DarkZone : public Building {
private:
	bool lightsOn;
	Zombie* enemy;
	Zombie* enemy2;
	Zombie* enemy3;
	Zombie* enemy4;
	Zombie* enemy5;
	Zombie* enemy6;
	Zombie* enemy7;
	Zombie* enemy8;
	std::vector<Zombie*> zombieList;
	std::vector<Debris*> debrisVector;
public:
	DarkZone(Building*, Student*);
	~DarkZone();
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void actionCall(char);
	void setPtrs(Building*, Building*, Building*);
	std::string getType();
};

#endif