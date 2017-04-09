/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for FinalZone class, a derived class from
the Building base class. Is an abstraction of an OSU building in a zombie
survival game.
*********************************************************************/

#ifndef FINALZONE_HPP
#define FINALZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include <vector>
#include <string>

class FinalZone : public Building {
private:
	bool gameWon;
	bool lightsOn;
	Zombie* enemy;
	Zombie* enemy2;
	Zombie* enemy3;
	Zombie* enemy4;
	Zombie* enemy5;
	std::vector<Zombie*> zombieList;
	std::vector<Debris*> debrisVector;
public:
	FinalZone(Building*, Student*);
	~FinalZone();
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void actionCall(char);
	std::string getType();
	bool getGameWon();
};
#endif