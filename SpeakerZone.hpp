/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for SpeakerZone class, a derived class from
the Building base class. Is an abstraction of an OSU building in a zombie
survival game.
*********************************************************************/

#ifndef SPEAKERZONE_HPP
#define SPEAKERZONE_HPP

#include "Building.hpp"
#include "Zombie.hpp"
#include <vector>
#include <string>
#include "WriteMessage.hpp"

class SpeakerZone : public Building {
private:
	bool stereoFound;
	bool lightsOn;
	Zombie* enemy;
	Zombie* enemy2;
	Zombie* enemy3;
	Zombie* enemy4;
	Zombie* enemy5;
	Zombie* enemy6;
	std::vector<Zombie*> zombieList;
public:
	SpeakerZone(Building*, Student*);
	~SpeakerZone();
	void setMap();
	void printMap();
	void updateMap();
	void updateMap(char);
	void actionCall(char);
	std::string getType();
};


#endif