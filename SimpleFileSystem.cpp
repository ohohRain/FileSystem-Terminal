/*



This file defines the necessary methods for the SimpleFileSystem, which is a
particular implementation of the AbstractFileSystem. This file system can manage
all files that implement the AbstractFile interface.


*/

#include <iostream>
#include <utility>
#include "SimpleFileSystem.h"
#include "AbstractFile.h"


using namespace std;

// destructor ensures that all files within the system are deleted before the system itself is deleted
SimpleFileSystem::~SimpleFileSystem() {
	for (auto curr = files.begin(); curr != files.end(); ++curr) {
		delete (*curr).second;
	}
}

// method to add a file to the system
int SimpleFileSystem::addFile(string name, AbstractFile* file) {
	
	if (files.find(name) != files.end()) {			// if we find a file with the same name, then return failure
		return fileAlreadyInSystem;
	}
	if (file == nullptr) {							// if given nullptr, return failure
		return nullFilePtr;
	}
	std::pair<string, AbstractFile*> newFile = make_pair(name, file);			// insert file into system as entry in map
	files.insert(newFile);

	return success;
}



AbstractFile* SimpleFileSystem::openFile(string name) {

	auto file_ptr = files.find(name);	

	if (file_ptr == files.end()) {					// if file cannot be found in map, return nullptr
		return nullptr;
	}
	AbstractFile* file = file_ptr->second;			// get pointer to the file

	if (openFiles.find(file) == openFiles.end()) {	// if file cannot be found in openFiles
		openFiles.insert(file);						// open the file
	}
	else {											// if file is already open, return nullptr
		return nullptr;
	}

	return file;
}

// method to close file -- checks that file is in set of open files and removes it from the set if it is in there
int SimpleFileSystem::closeFile(AbstractFile* file) {
	if (openFiles.find(file) != openFiles.end()){
		openFiles.erase(file);
		return success;
	}
	else {
		return fileNotOpen;
	}
}

// method to delete a file
int SimpleFileSystem::deleteFile(string name) {
	auto file_ptr = files.find(name);
	

	// if file is not in files map
	if (file_ptr == files.end()) {
		return fileDoesNotExist;
	}
	// if file is in map
	else {
		AbstractFile* file = file_ptr->second;
		// if file is in map and is open
		if (openFiles.find(file) != openFiles.end()) {
			return fileIsOpen;
		}
		// if file is in map and not open
		else {
			files.erase(file_ptr);
			delete file;
			return success;
		}
	}
}

// method returns a set of all the names of the files
set<string> SimpleFileSystem::getFileNames() {
	set<string> fileNames;
	for (auto curr = this->files.begin(); curr != files.end(); ++curr) {
		fileNames.insert((*curr).first);
	}
	return fileNames;
}
