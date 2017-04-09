/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Student derived class derived from
Character base class. Represents an abstraction of the hero of a zombie
survival game.
*********************************************************************/

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Character.hpp"
#include "Backpack.hpp"
#include <vector>
#include <string>

class Student : public Character {
private:	
	int health;
	Backpack* pack;
public:
	Student();
	Student(char icon, int xCoord, int yCoord);
 	~Student();
	void move(char);
	void minusLife();
	void investigate(char);
	void addItem(char);
	void backpackMenu();
	char getCurrentItem();
	int getHealth();
	void printHealth();
};

#endif