/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Character base class. Represents an
abstraction of a character in a zombie survival game.
*********************************************************************/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>

class Character {
protected:
	char icon;
	int xCoord;
	int yCoord;
public:
	Character(char, int, int);
	virtual ~Character() {}
	int getXPos() const;
	int getYPos() const;
	char getIcon() const;
	void setLocation(std::string, std::string);
};

#endif