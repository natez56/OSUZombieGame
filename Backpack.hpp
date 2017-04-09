/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Backpack classed. Used to represent
an abstraction for a container of items.
*********************************************************************/

#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <string>

class Backpack {
private:
	static const int backpackSize = 3;
	std::string backpack[backpackSize];
	int numItems;
	char equippedItem;
public:
	Backpack();
	~Backpack() {}
	void placeItem(char);
	void packMenu();
	char getEquippedItem();	
};

#endif