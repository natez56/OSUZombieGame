/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for ChemicalZone class, a derived class from
the Building base class. Is an abstraction of an OSU building in a zombie
survival game.
*********************************************************************/

#ifndef CHEMICALZONE_HPP
#define CHEMICALZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include <vector>
#include <string>
#include "WriteMessage.hpp"

class ChemicalZone : public Building {
private:
	bool lightsOn;
public:
	ChemicalZone(Building*, Building*, Student*);
	~ChemicalZone() {}
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void actionCall(char);
	std::string getType();
	void setPtrs(Building*, Building*, Building*);	
};

#endif