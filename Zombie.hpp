/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Zombie class, a derived class from Character
base class.
*********************************************************************/

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "Character.hpp"

class Zombie : public Character {
private:
	int walkDelay;
	int zombieSpeed;
	int xDirection;
	int yDirection;
public:
	Zombie(char, int, int, int, int);
	~Zombie() {}
	void move();
	void setDirection(int, int, int, int);
	int getXDirection();
	int getYDirection();
	void setSpeed(int);
};

#endif