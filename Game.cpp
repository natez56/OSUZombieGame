/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for game class. Class contains a
constructor, destructor, and playGame funcion. To use the function simply
create an instance of the class and call the playGame funcion.
*********************************************************************/

#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include "Game.hpp"
#include "Menu.hpp"

/*********************************************************************
** Description: Default constructor for the Game class. Creates a new
Student and also creates all the Building class objects needed for the
game. Sets game turns to 2000, these turns are decreased when the user
moves. Also sets the required pointers that allow the doors to generate
the appropriate map.
*********************************************************************/
Game::Game() {
	hero = new Student('v', 24, 1);
	hero->addItem('P');
	Kelley = new StartZone(hero);
	Milam = new SpeakerZone(Kelley, hero);
	Ballard = new KeyZone(Kelley, hero);
	Bexell = new DarkZone(Kelley, hero);
	Gleeson = new ChemicalZone(NULL, NULL, hero);
	Gilbert = new FinalZone(Gleeson, hero);

	Kelley->setPtrs(Bexell, Milam, Ballard);
	Bexell->setPtrs(Gleeson, NULL, Kelley);
	Gleeson->setPtrs(Gilbert, NULL, Bexell);
	gameTurns = 2000;
}

/*********************************************************************
** Description: Destructor for Game class. Deletes memory associated
with the Building pointers and Student pointer.
*********************************************************************/
Game::~Game() {
	delete hero;
	delete Kelley;
	delete Milam;
	delete Ballard;
	delete Bexell;
	delete Gleeson;
	delete Gilbert;
}

/*********************************************************************
** Description: Function to run the game. Sets screen so that it does
not require user to press enter to record input.  Also when no input is
happening the game still updates the map. When a user enters a recognized
character the function uses the switch statement to call the appropriate
function to either update the map with a character move or display a message.
Checks if health is zero or if number of steps left has reached zero. Also
checks to see if the user has found the final item and won the game.
*********************************************************************/
void Game::playGame() {
	// Initializes the ncurses screen to allow input to be read without
	// needing the user to press enter.
	initscr();

	// User input will not be printed to the screen.
	noecho();
	cbreak();

	// Prints the start location for the game.
	Kelley->printMap();
	Building* currentSite = Kelley;
	int ch = ' ';

	// Function to make it so that user input is not needed to update the game.
	// Zombies will move despite the user not entering in input.
	nodelay(stdscr, TRUE);

	// Prints message going over the rules of the game.
	introMessage();

	// First screen message to actual game.
	std::string firstScreen = "Welcome to the Oregon State Zombie Invasion Game.";
	firstScreen += " To set the scene...You've been working late in the Kelley ";
	firstScreen += "Engineering Center when suddenly your phone buzzes with an";
	firstScreen += " emergency message. Before you read the message the lights";
	firstScreen += " go out...use your inventory 'i' to equip and check your";
	firstScreen += " phone. Press 'e' to equip and 'e' again to use.";

	// Function to print message within a special message box.
	writeMessage(firstScreen);

	// User can press q to quit the game at any time.
	while (ch != 'q') {
		// Function that checks if input is happening.
		if ((ch = getch()) == ERR) {
			// if input is not happening the map is updated to reflect zombie
			// moves. Also checks if user health is zero and exits game if it is.
			if (hero->getHealth() == 0) {
				ch = 'q';
			}
			currentSite->updateMap();

			// Limits how often the screen is updated when no user input is
			// given.
			usleep(10000);
		} else {
			switch (ch) {
				// Move forward input. Updates map with character move.
				case 'w': {
					currentSite->updateMap('w');
					gameTurns--;
					break;
				}
				// Move left input, Updates map with character move.
				case 'a': {
					currentSite->updateMap('a');
					gameTurns--;
					break;
				}
				// Move down input, updates map with character move.
				case 's': {
					currentSite->updateMap('s');
					gameTurns--;
					break;
				}
				// Move right input, updates map with character move.
				case 'd': {
					currentSite->updateMap('d');
					gameTurns--;
					break;
				}
				// Investigate input, prints informaion about a map square.
				case 'f': {
					currentSite->updateMap('f');
					break;
				}
				// Action input, use to equip items and interact with map.
				case 'e': {
					currentSite->updateMap('e');
					break;
				}
				// Input to open backpack.
				case 'i': {
					currentSite->updateMap('i');
					break;
				}
				// Input to open menu.
				case 'm': {
					ch = menu();

					// If user input's 4 as a menu option prints the remaining
					// game steps.
					if (ch == '4') {
						nodelay(stdscr, FALSE);
						printw("Game turns left: ");
						std::string turnsLeft = std::to_string(gameTurns);
						for (unsigned int i = 0; i < turnsLeft.length(); i++) {
							char temp = turnsLeft[i];
							addch(temp);
						}
						printw("\n");
						printw("Press any key to start the game.\n");
						getch();
						nodelay(stdscr, TRUE);
					}
					break;
				}
			}

			// Checks user's health to make sure they have health remaining.
			// Ends game when health reaches zero.
			if (hero->getHealth() == 0) {
				ch = 'q';
			}

			// Checks to see if hero has collected the winning item. Ends game
			// if they have.
			if (currentSite->getGameWon()) {
				std::string message = "Congratulations you've collected the"; 
				message += " zombie antidote and won the game!";
				writeMessage(message);
				ch = 'q';
			}

			// Checks to see if game turns has reached zero. Ends game if it
			// has.
			if (gameTurns == 0) {
				writeMessage("It looks like you have run out of steps. Game over.");
				ch = 'q';
			}

			// Checks to see if the user has entered in a door. If the user
			// has then the conditionals check which door so that the current
			// site can be changed to the correct pointer.
			if (currentSite->getDoorOpen() != " ") {
				// Check exit door location.
				if (currentSite->getDoorOpen() == "north") {
					// Resets string, when a new door is encountered it records
					// the position (north, south, east, west) of the door
					// character is exiting from.
					currentSite->resetDoor();

					currentSite = currentSite->changeBuilding("north");

					// Sets hero x and y position so that it is appropriate
					// for new room.
					hero->setLocation(currentSite->getType(), "north");

					clear();
					currentSite->printMap();
				} else if (currentSite->getDoorOpen() == "east") {
					currentSite->resetDoor();

					currentSite = currentSite->changeBuilding("east");

					hero->setLocation(currentSite->getType(), "east");

					clear();
					currentSite->printMap();
				} else if (currentSite->getDoorOpen() == "south") {
					currentSite->resetDoor();

					currentSite = currentSite->changeBuilding("south");

					hero->setLocation(currentSite->getType(), "south");

					clear();
					currentSite->printMap();
				} else if (currentSite->getDoorOpen() == "west") {
					currentSite->resetDoor();

					currentSite = currentSite->changeBuilding("west");

					hero->setLocation(currentSite->getType(), "west");

					clear();
					currentSite->printMap();
				}
			}

		}
	}	
}