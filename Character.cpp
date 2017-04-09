/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Base class for two derived classes. Implementation file.
*********************************************************************/

#include "Character.hpp"

/*********************************************************************
** Description: Constructor takes as parameters a char and two ints. The
char represents how the character will be visible on the map. For instance
zombies are visible as 'z'. The int parameters are used to set the
map location of the character.
*********************************************************************/
Character::Character(char iconIn, int xCoordIn, int yCoordIn) {
	icon = iconIn;
	xCoord = xCoordIn;
	yCoord = yCoordIn;
}

/*********************************************************************
** Description: Returns an int representing the map index x coordinate
of a characer.
*********************************************************************/
int Character::getXPos() const {
	return xCoord;
}

/*********************************************************************
** Description: Returns an int representing the map index y coordinate
of a character.
*********************************************************************/
int Character::getYPos() const {
	return yCoord;
}

/*********************************************************************
** Description: Returns a char representing how the character appears
on the map.
*********************************************************************/
char Character::getIcon() const {
	return icon;
}

/*********************************************************************
** Description: Used to set the location of a character in the event
that a building is changed through the use of a door. Checks the direction
that the user came from. Then places the user at the appropriate coordinates
for the new building.
*********************************************************************/
void Character::setLocation(std::string building, std::string directionFrom) {
	if (building == "StartZone") {
		if (directionFrom == "west") {
			xCoord = 29;
			yCoord = 8;
			icon = '<';
		} else if (directionFrom == "north") {
			xCoord = 9;
			yCoord = 9;
			icon = '^';
		} else if (directionFrom == "east") {
			xCoord = 1;
			yCoord = 8;
			icon = '>';
		}
	} else if (building == "KeyZone") {
		if (directionFrom == "west") {
			xCoord = 21;
			yCoord = 23;
			icon = '<';
		}
	} else if (building == "SpeakerZone") {
		if (directionFrom == "south") {
			xCoord = 30;
			yCoord = 4;
			icon = 'v';
		}
	} else if (building == "DarkZone") {
		if (directionFrom == "east") {
			xCoord = 1;
			yCoord = 10;
			icon = '>';
		} else if (directionFrom == "west") {
			xCoord = 48;
			yCoord = 7;
			icon = '<';
		}
	} else if (building == "ChemicalZone") {
		if (directionFrom == "east") {
			xCoord = 3;
			yCoord = 14;
			icon = '>';
		} else if (directionFrom == "south") {
			xCoord = 6;
			yCoord = 1;
			icon = 'v';
		}
	} else if (building == "FinalZone") {
		if (directionFrom == "north") {
			xCoord = 3;
			yCoord = 17;
			icon = '^';
		}
	}
}