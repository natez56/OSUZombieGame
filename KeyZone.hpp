/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for KeyZone derived class from building base
class. Represents an abstraction of a OSU school building in a zombie
survival game.
*********************************************************************/

#ifndef KEYZONE_HPP
#define KEYZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include <vector>
#include <string>
#include "WriteMessage.hpp"

class KeyZone : public Building {
private:
	bool keyFound;
	bool lightsOn;
	Zombie* enemy;
	Zombie* enemy2;
	Zombie* enemy3;
	std::vector<Zombie*> zombieList;
public:
	KeyZone(Building*, Student*);
	~KeyZone();
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void actionCall(char);
	std::string getType();
};

#endif