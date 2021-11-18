/*



This file defines the methods that parse the user input into an input that can be fed
to the copy command and then to the remove command -- the commands that make up
the rename command.


*/

#include <sstream>
#include <iostream>
#include "RenameParsingStrategy.h"
#include "AbstractFile.h"


using namespace std;

vector<string> RenameParsingStrategy::parse(string s) {
	istringstream iss(s);

	string existingFile;
	iss >> existingFile;				// get name of existing file
		
	string newName;
	iss >> newName;						// get desired new name

	string extra;			
	if (iss >> extra) {					// test for extra input
		throw incorrectCommandArgs;		// if there is too much input, throw exception -- see ReadMe "Design Decisions" for justification
	}

	string forCopyCommand = existingFile + " " + newName;		// make input for copy command

	return vector<string> {forCopyCommand, existingFile};		// return vector that includes input for copy command then input for remove command
		
}

// acts as the displayInfo() method for the rename command since rename is a macro command and thus does not have its own .cpp file
void RenameParsingStrategy::displayInfo() {
	cout << "The rename command gives an existing file a new name" << endl;
	cout << "Invoke the rename command using: rn <existing_file> <new_name_with_no_extension>" << endl;
}
