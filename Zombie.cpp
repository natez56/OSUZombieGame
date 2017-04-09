/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for Zombie class that is a derived
class from the Character base class.
*********************************************************************/

#include "Zombie.hpp"

/*********************************************************************
** Description: Constructor that takes a parameters four ints and a char.
Char value represents the symbol the zombie will appear as on the map.
The xCoord and yCoord parameters represent the position the zombie
will start at.  the xDirection and yDirection parameters represent if
the zombie will move or not on the map. Inputing a one in these parameters
will cause the zombie to move.
*********************************************************************/
Zombie::Zombie(char icon, int xCoord, int yCoord, int xDirectionIn, 
			   int yDirectionIn) : Character(icon, xCoord, yCoord) {
	xDirection = xDirectionIn;
	yDirection = yDirectionIn;
	
	walkDelay = 0;
	zombieSpeed = 90;
}

/*********************************************************************
** Description: Function causeing the zombie to move. Each time the
function is called it increments the walkDelay parameter. Only when that
parameter exceeds zombieSpeed is the zombies' position altered. This serves
to slow zombies down. Without this function they will move too fast.
*********************************************************************/
void Zombie::move() {
	if (walkDelay < zombieSpeed) {
		walkDelay++;
	} else {
		xCoord += xDirection;
		yCoord += yDirection;

		walkDelay = 0;
	}
}

/*********************************************************************
** Description: Function used to set the zombies speed and direction
of movement.  The first two int parameters represent values used to
cause the zombie to change direction.  The other two int parameters
will cause a zombie to start to move.
*********************************************************************/
void Zombie::setDirection(int xChange, int yChange, int xStart, int yStart) {
	xDirection += xStart;
	yDirection += yStart;
	xDirection *= xChange;
	yDirection *= yChange;
}

/*********************************************************************
** Description: Get function returning an integer parameter tha represents
the current direction the zombie is moving.
*********************************************************************/
int Zombie::getXDirection() {
	return xDirection;
}

/*********************************************************************
** Description: Get function returning an integer parameter tha represents
the current direction the zombie is moving.
*********************************************************************/
int Zombie::getYDirection() {
	return yDirection;
}

/*********************************************************************
** Description: Function to set the speed of the zombie. Entering in
a high value will cause the zombie to go slow.
*********************************************************************/
void Zombie::setSpeed(int speedIn) {
	zombieSpeed = speedIn;
}