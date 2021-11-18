/*


This file defines the necessary methods for the display command, which can display
files either as their data, or as formatted data for img files.


*/

#include <iostream>
#include <sstream>
#include "DisplayCommand.h"
#include "AbstractFileSystem.h"
#include "BasicDisplayVisitor.h"

using namespace std;

DisplayCommand::DisplayCommand(AbstractFileSystem* s) : system(s) {}

void DisplayCommand::displayInfo() {
	cout << "The display command is used to print the contents of a file" << endl;
	cout << "To display the formatted file, use command: ds <filename>" << endl;
	cout << "To display the unformatted version of a file, use command: ds <filename> -d" << endl;
}

int DisplayCommand::execute(string s) {

	istringstream iss(s);
	string fileName;
	iss >> fileName;						// extract file name, if unsuccessful, return failure
	if (!iss) {
		return incorrectCommandArgs;
	}

	AbstractFile* file = system->openFile(fileName);
	if (file == nullptr) {							// if opening unsuccessful, return failure
		return invalidFileName;
	}


	string extraCommand;					// check for another command
	iss >> extraCommand;

	

	if (iss) {								//if there was second command
		
		string tooMuch;
		if (iss >> tooMuch) {				// check for more input, if there is any, input not properly formatted
			return incorrectCommandArgs;
		}

		if (extraCommand == "-d") {			// if the extra command was -d option
			// unformatted
			vector<char> contents = file->read();
			for (char c : contents) {		// display contents simply
				cout << c;
			}
			cout << '\n';
		}	
		else {								// if extraCommand was not "-d"
			system->closeFile(file);		// must close file when done with it
			return incorrectCommandArgs;
		}
	}
	else {									// formatted option
		
		BasicDisplayVisitor* displayer = new BasicDisplayVisitor();		// make display visitor
		file->accept(displayer);			// display data formatted
		delete displayer;					// deallocate visitor
	}	


	system->closeFile(file);
	return success;
}


