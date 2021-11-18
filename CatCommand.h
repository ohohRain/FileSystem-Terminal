/*


This file declares the necessary functions for the cat command, which is derived from the
AbstractCommand interface.


*/

#pragma once

#include "AbstractCommand.h"
class AbstractFileSystem;

class CatCommand : public AbstractCommand {

public:
	CatCommand(AbstractFileSystem* s);

	virtual int execute(std::string s) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* system;

};

