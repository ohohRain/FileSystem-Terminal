/*


This file declares the abstract base class AbstractCommmand which is inherited by all commands in this program.


*/

#pragma once
#include <string>

class AbstractCommand {

public:
	virtual ~AbstractCommand() = default;
	virtual int execute(std::string s) = 0;
	virtual void displayInfo() = 0;


};

