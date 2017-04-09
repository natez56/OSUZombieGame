/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Header file for Game class. Class is an abstraction
of a zombie survival game.
*********************************************************************/

#ifndef GAME_HPP
#define GAME_HPP

#include "Student.hpp"
#include "StartZone.hpp"
#include "KeyZone.hpp"
#include "SpeakerZone.hpp"
#include "DarkZone.hpp"
#include "ChemicalZone.hpp"
#include "FinalZone.hpp"
#include "WriteMessage.hpp"

class Game {
private:
	int gameTurns;
	Building* Kelley;
	Building* Milam;
	Building* Ballard;
	Building* Bexell;
	Building* Gleeson;
	Building* Gilbert;
	Backpack* pack;
	Student* hero;
public:
	Game();
	~Game();
	void playGame();
};
#endif