/*


This file defines the necessary methods for the copy command, which duplicates a file 
and gives the new file a new name.


*/

#include <iostream>
#include <sstream>
#include "CopyCommand.h"
#include "AbstractFileSystem.h"

using namespace std;

CopyCommand::CopyCommand(AbstractFileSystem* s) : system(s) {}

void CopyCommand::displayInfo() {
	cout << "The copy command copies an existing file into a new file of a different name" << endl;
	cout << "Invoke the copy command with: cp <file_to_copy> <new_name_with_no_extension>" << endl;
}

int CopyCommand::execute(string s) {

	istringstream iss(s);
	string fileToCopy;
	iss >> fileToCopy;						// extract name of file
	if (!iss) {								// if extraction unsuccessful, can return failure
		return incorrectCommandArgs;
	}

	AbstractFile* fileToCopy_ptr = system->openFile(fileToCopy);		// obtain pointer to file we are going to copy
	if (fileToCopy_ptr == nullptr) {			
		return fileDoesNotExist;
	}

	string newFileName;							// extract desired name of new file
	iss >> newFileName;
	if (!iss) {									// if extraction failed, close file and return failure
		system->closeFile(fileToCopy_ptr);
		return incorrectCommandArgs;
	}

	string extra;
	iss >> extra;								// check for extra arguments, if there are some, improper formatted input
	if (iss) {
		system->closeFile(fileToCopy_ptr);
		return incorrectCommandArgs;
	}
	
	AbstractFile* newFile = fileToCopy_ptr->clone(newFileName);		// call clone method within specific file
	int addOutcome = system->addFile(newFileName, newFile);			// add new file to system
	if (addOutcome != success) {									// if unable to add new file, delete the new file, close original file, and return failure
		delete newFile;
		system->closeFile(fileToCopy_ptr);
		return unableToAddFile;
	}


	system->closeFile(fileToCopy_ptr);
	return success;
}
