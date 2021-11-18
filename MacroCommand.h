/*



This file declares the necessary functions for all MacroCommand objects, which is derived from the
AbstractCommand interface. This file extends the interface, however, including a vector of pointers
to the command objects that it aggregates and also a pointer to an AbstractParsingStrategy that is
used to parse the user input and feed it to the individual commands.


*/

#pragma once

#include <vector>
#include "AbstractCommand.h"
class AbstractFileSystem;
class AbstractParsingStrategy;

class MacroCommand : public AbstractCommand {

public:
	MacroCommand(AbstractFileSystem* s);

	virtual int execute(std::string s) override;
	virtual void displayInfo() override;


	void addCommand(AbstractCommand*);
	void setParseStrategy(AbstractParsingStrategy*);

private:
	AbstractFileSystem* system;
	
	std::vector<AbstractCommand*> commands;
	AbstractParsingStrategy* strat;

};

