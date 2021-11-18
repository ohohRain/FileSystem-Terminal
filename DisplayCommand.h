/*


This file declares the necessary functions for the display command, which is derived from the
AbstractCommand interface.


*/

#pragma once

#include "AbstractCommand.h"
class AbstractFileSystem;

class DisplayCommand : public AbstractCommand {

public:
	DisplayCommand(AbstractFileSystem* s);

	virtual int execute(std::string s) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* system;

};
