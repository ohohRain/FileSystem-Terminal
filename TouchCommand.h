/*



This file declares the necessary functions for the touch command, which is derived from the
AbstractCommand class and is used to create files. 


*/

#pragma once

#include "AbstractCommand.h"
class AbstractFileFactory;
class AbstractFileSystem;

class TouchCommand : public AbstractCommand {

public:
	TouchCommand(AbstractFileSystem* s, AbstractFileFactory* f);

	virtual int execute(std::string s) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* system;
	AbstractFileFactory* factory;

	std::string getPassword();				// extra method added to get user input when they create password-protected file

};
