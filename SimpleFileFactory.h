/*



This file declares the necessary functions for the SimpleFileFactory, which is a particular
implementation of the AbstractFileFactory interface.


*/

#pragma once

#include "AbstractFileFactory.h"

class SimpleFileFactory : public AbstractFileFactory {
public:
	virtual AbstractFile* createFile(std::string name);


};
