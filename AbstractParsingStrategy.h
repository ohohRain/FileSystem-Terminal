/*


This file declares the abstract base class or interface that all parsing strategies used in this program
must implement. See ReadMe.txt "Design Decisions" section for explanation of why displayInfo() is declared
here.


*/

#pragma once

#include <vector>
#include <string>

class AbstractParsingStrategy {
public:
	virtual std::vector<std::string> parse(std::string) = 0;


	
	virtual void displayInfo() = 0;		// must be defined by derived classes to display information for macro commands
};

