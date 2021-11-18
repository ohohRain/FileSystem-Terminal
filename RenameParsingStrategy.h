/*



This file declares the necessary functions for the RenameParsingStrategy, which is used to
feed input to the commands that make up the rename macro command.


*/

#pragma once

#include <vector>
#include <string>
#include "AbstractParsingStrategy.h"

class RenameParsingStrategy : public AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string) override;
	
	virtual void displayInfo() override;			// used to display information for macro commands
};
