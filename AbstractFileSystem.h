/*


This file declares the abstract base class or interface that all file management systems that can
be used in this program must implement. The functions declared here cover the basic functionality
that a file system should have.


*/

#pragma once
// declaration of the interface all file systems provide goes here

#include <string>
#include <set>
#include "AbstractFile.h"

class AbstractFileSystem {
	
public:
	
	virtual int addFile(std::string name, AbstractFile* file) = 0;
	virtual int deleteFile(std::string name) = 0;
	virtual AbstractFile* openFile(std::string name) = 0;
	virtual int closeFile(AbstractFile* file) = 0;
	virtual std::set<std::string> getFileNames() = 0;
	
	
	
};
