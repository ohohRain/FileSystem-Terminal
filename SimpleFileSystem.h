/*



This file declares the necessary functions for the SimpleFileFactory class, which is
a particular implementation of the AbstractFileSystem interface.


*/

#pragma once


#include <map>
#include <set>
#include "AbstractFileSystem.h"


class SimpleFileSystem : public AbstractFileSystem {


public:
	virtual int addFile(std::string name, AbstractFile* file) override;
	virtual int deleteFile(std::string name) override;
	virtual AbstractFile* openFile(std::string name) override;
	virtual int closeFile(AbstractFile* file) override;
	virtual std::set<std::string> getFileNames() override;

	~SimpleFileSystem();										// destructor -- makes sure all files are deallocated when system is destroyed

private:
	std::map<std::string, AbstractFile*> files;
	std::set<AbstractFile*> openFiles;


};
