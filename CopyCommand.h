/*


This file declares the necessary functions for the copy command, which is derived from the
AbstractCommand interface.


*/

#pragma once

#include "AbstractCommand.h"
class AbstractFileSystem;

class CopyCommand : public AbstractCommand {

public:
	CopyCommand(AbstractFileSystem* s);

	virtual int execute(std::string s) override;
	virtual void displayInfo() override;

private:
	AbstractFileSystem* system;

};
