/*



This file declares the necessary functions for the command prompt, which is the class that 
controls the flow of the program while the file system is being interacted with.


*/

#pragma once


#include <map>
#include <string>
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
class AbstractCommand;



class CommandPrompt {
public:
	CommandPrompt();								// constructor
	void setFileSystem(AbstractFileSystem*);		// configures command prompt with the file system
	void setFileFactory(AbstractFileFactory*);		// configures the command prompt with the file factory
	int addCommand(std::string s, AbstractCommand*);	// adds a command to the possible commands that can be executed

	int run();										// controls the program flow

protected:
	void listCommands();							// prints all of the commands this command prompt is configured with
	std::string prompt();							// prompts user for input


private:
	std::map<std::string, AbstractCommand*> commands;	// map to store commands and the specific string with which they are invoked
	AbstractFileSystem* system;							// pointer to system this command prompt is configured with
	AbstractFileFactory* factory;						// pointer to the factory this command prompt is configured with



};

