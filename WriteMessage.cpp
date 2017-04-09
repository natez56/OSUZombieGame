/*********************************************************************
** Program name: Final
** Author: Nathan Zimmerman
** Date: 03/21/2017
** Description: Implementation file for writeMessage functioon,
introMessage function, and gameControlMessage function. Functions used
to print messages to the screen.
*********************************************************************/

#include "WriteMessage.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <string>

/*********************************************************************
** Description: Function used to print a message to the screen with a
picture of a bat. Takes a string as a parameter and will print that message
within the confines of a box printed to the screen. Takes a string as
a parameter representing the message to be printed.
*********************************************************************/
void writeMessage(std::string message) {
	nodelay(stdscr, FALSE);
	clear();
	printw("           /\\   .'    '.   /\\             \n");
	printw("          /  \\  ' '''' '  /  \\            \n");
	printw("         /    \\ | O  O | /    \\           \n");
	printw("        /        \\ vv /        \\          \n");
	printw("        \\/\\/\\/\\/\\/    \\/\\/\\/\\/\\/          \n");
	printw("            '     V  V                    \n");
	printw("------------------------------------------\n");
	int count = 0;
	addch('|');
	for (unsigned int i = 0; i < message.length(); i++) {
		if (count > 30) {
			if (message[i] == ' ') {
				while(count < 40) {
					addch(' ');
					count++;
				}
				addch('|');
				printw("\n");
				addch('|');
				i++;
				count = 0;
			}
		}
		
		addch(message[i]);
		count++;
	}
	while(count < 40) {
		addch(' ');
		count++;
	}
	addch('|');
	printw("\n");
	printw("------------------------------------------\n");
	printw("\n\n");
	printw("Press any key to continue.\n");
	getch();
	nodelay(stdscr, TRUE);
}

/*********************************************************************
** Description: Function to print the intro message for the game. Message
goes over the game funcdamentals including controls. Waits for user input
to continue past the message.
What it does: 
Describe arguments/restrictions: 
what it returns:
*********************************************************************/
void introMessage() {
	// Function allowing the screen to pause to wait for user input.
	nodelay(stdscr, FALSE);
	clear();
	printw("Welcome to my final project. The game you are about to play is ");
	printw("called Oregon State Zombie Apocalypse. \nSome important things");
	printw(" to note:\n The game is played in real time. Every key you press ");
	printw("is recorded right away. \nYou will not use the enter key. When you ");
	printw("aren't pressing keys and a screen menu isn't open, things are ");
	printw("still happening.\n The game maps are modeled after real Oregon");
	printw(" State building map layouts.\nControls for the game are as ");
	printw("follows:\n 'w' - face up/move up\n 'a' -face left/move left\n");
	printw(" 's' - face down/move down\n 'd' - face right/move right\n");
	printw(" 'f' - investigate space. Can be used anytime and will generate ");
	printw("a message giving information about the space in front of you.\n");
	printw(" 'e' - action button. Press this button to interact with special");
	printw(" spaces on the map or to equip items from your backpack\n");
	printw(" 'i' - use to access the backpack menu.\n 'm' - use to access ");
	printw("the game menu allowing you to see game controls.\n\n");
	printw("In the game you are a character represented by 'v'. \n");
	printw("To win the game you must reach Gilbert hall and pick up the ");
	printw("'Zombie' repellant.\nMany of the rooms have the lights turned off");
	printw(" this means that your character can only see a certain number of ");
	printw("squares around him/her. \nWhen the lights are turned on your ");
	printw("character can see the whole map.\nKey map object symbols are:\n");
	printw(" '-', '|' - wall symbol, you cannot cross these barriers.\n");
	printw(" 'L' - lightswitch, use 'e' to turn the switch on.\n");
	printw(" 'd' - open door, no need to press 'e', just walk through. \n");
	printw(" 'X' - locked door, equip a key and press 'e' to unlock.\n");
	printw(" 'K' - key, pickup by pressing 'e', equip by pressing 'i' and ");
	printw("equipping the key by moving the menu cursor and pressing 'e' in ");
	printw("your backpack menu.\n 'S' - portable speaker item. pick up by ");
	printw("pressing 'e', equip by pressing 'i' and equipping the speaker");
	printw(" by moving the menu cursor and pressing 'e' in ");
	printw("your backpack menu. \nOnce equipped press 'e' near a wall of ");
	printw("zombies to make them disperse.\n 'z' - zombie, if a zombie moves ");
	printw("to a square you are occupying you will lose a life. Game over if ");
	printw("your lives reach zero.\n 'O' - barrel, pick up with e and move ");
	printw("move your character around with it using your normal controls. ");
	printw("press 'e' again to drop.\n '#' - toxic chemical spill, if you ");
	printw("step on these squares you lose a life.\n 'P' - your phone, you ");
	printw("start with this item in your backpack.\n\n\n");
	printw("Press any key to start the game.\n");
	
	// Function requesting user input;
	getch();

	// Function to allow screen to update without user input.
	nodelay(stdscr, TRUE);
}

/*********************************************************************
** Description: Message to print the game controls.  Waits for user input
to close the message.
*********************************************************************/
void gameControlsMessage() {
	nodelay(stdscr, FALSE);
	clear();
	printw("Game Controls\n");
	printw("Controls for the game are as ");
	printw("follows:\n 'w' - face up/move up\n 'a' -face left/move left\n");
	printw(" 's' - face down/move down\n 'd' - face right/move right\n");
	printw(" 'f' - investigate space. Can be used anytime and will generate ");
	printw("a message giving information about the space in front of you.\n");
	printw(" 'e' - action button. Press this button to interact with special");
	printw(" spaces on the map or to equip items from your backpack\n");
	printw(" 'i' - use to access the backpack menu.\n 'm' - use to access ");
	printw("the game menu allowing you to see game controls.\n\n");
	printw("Key map object symbols are:\n");
	printw(" '-', '|' - wall symbol, you cannot cross these barriers.\n");
	printw(" 'L' - lightswitch, use 'e' to turn the switch on.\n");
	printw(" 'd' - open door, no need to press 'e', just walk through. \n");
	printw(" 'X' - locked door, equip a key and press 'e' to unlock.\n");
	printw(" 'K' - key, pickup by pressing 'e', equip by pressing 'i' and ");
	printw("equipping the key by moving the menu cursor and pressing 'e' in ");
	printw("your backpack menu.\n 'S' - portable speaker item. pick up by ");
	printw("pressing 'e', equip by pressing 'i' and equipping the speaker");
	printw(" by moving the menu cursor and pressing 'e' in ");
	printw("your backpack menu. \nOnce equipped press 'e' near a wall of ");
	printw("zombies to make them disperse.\n 'z' - zombie, if a zombie moves ");
	printw("to a square you are occupying you will lose a life. Game over if ");
	printw("your lives reach zero.\n 'O' - barrel, pick up with e and move ");
	printw("move your character around with it using your normal controls. ");
	printw("press 'e' again to drop.\n '#' - toxic chemical spill, if you ");
	printw("step on these squares you lose a life.\n 'P' - your phone, you ");
	printw("start with this item in your backpack.\n\n\n");


	printw("Press any key to continue the game.\n");
	getch();
	nodelay(stdscr, TRUE);
}