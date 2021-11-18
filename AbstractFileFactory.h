/*


This file declares the abstract base class or interface that all file factories that can be used in
this program must implement.


*/

#pragma once
// studio 18 - file factory interface declared here

#include <string>
#include "../SharedCode/AbstractFile.h"

class AbstractFileFactory {

public:
	virtual AbstractFile* createFile(std::string name) = 0;


};

