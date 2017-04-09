/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Building base class. Pure virtual base
class. Has six derived classes. Represents the abstraction of an OSU
building in a zombie survival game.
*********************************************************************/

#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <vector>
#include <string>
#include "Student.hpp"

class Building {
protected:
	bool objectPickedUp;
	int objectNum;
	struct Debris {
		int debrisX;
		int debrisY;
		Debris(int x, int y) : debrisX(x), debrisY(y) {}
	};
	int objectX;
	int objectY;
	std::string doorOpen;
	std::string name;
	Building* north;
	Building* east;
	Building* south;
	Building* west;
	std::vector<std::string> map;
	std::vector<std::string> blankMap;
	std::vector<std::string> startMap;
	Student* hero;
public:
	Building();
	Building(std::string, Building*, Building*, Building*, Building*, Student*);
	virtual ~Building() {}
	virtual void setMap() = 0;
	char getMapChar(int, int);
	virtual void printMap();
	void printDarkMap();
	virtual void updateMap(char) {}
	virtual void updateMap() {}
	virtual bool wallItemCheck(char);
	virtual void setPtrs(Building*, Building*, Building*) {}
	virtual void actionCall(char) {}
	std::string getDoorOpen();
	void resetDoor();
	Building* changeBuilding(std::string);
	virtual std::string getType() = 0;
	virtual bool getGameWon();
	std::string getName();
};

#endif