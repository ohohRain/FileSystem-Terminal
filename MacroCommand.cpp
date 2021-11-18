/*



This file defines the necessary methods for all macro commands, which are composite
objects composed of other commands. This class aggregates commands under one object
and calls the proper parsing class to make sure that it provides the commands it is
made of with the right inputs.


*/

#include <iostream>
#include <sstream>
#include "MacroCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractParsingStrategy.h"

using namespace std;

MacroCommand::MacroCommand(AbstractFileSystem* s) : system(s), strat(nullptr) {}

void MacroCommand::displayInfo() {

	this->strat->displayInfo();			// call displayInfo() on particular strategy this MacroCommand is configured with
	 
}

int MacroCommand::execute(string s) {
	vector<string> inputs;
	try {										// parse() will throw exception if user input is incorrect
		inputs = strat->parse(s);				// get format of correct inputs to commands
	}
	catch (...) {								// catch any issue from parsing
		return incorrectCommandArgs;
	}

	int i = 0;												// iterating variable to keep track of what input to give to the command
	for (AbstractCommand* command : commands) {				// for each of its commands, execute it with proper input
		int outcome = command->execute(inputs[i]);
		++i;
		if (outcome != success) {
			return outcome;
		}
	}

	return success;
}


void MacroCommand::addCommand(AbstractCommand* command) {
	commands.push_back(command);
}

void MacroCommand::setParseStrategy(AbstractParsingStrategy* strategy) {
	this->strat = strategy;
}
