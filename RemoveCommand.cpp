/*



This file defines the necessary methods for the remove command, which simply
removed a file from the system.


*/

#include <iostream>
#include <iomanip>
#include "RemoveCommand.h"
#include "AbstractFileSystem.h"



using namespace std;

RemoveCommand::RemoveCommand(AbstractFileSystem* sys) : system(sys) {}

void RemoveCommand::displayInfo() {
	cout << "The remove command removes a file from the file system, remove is invoked using command: rm <filename>" << endl;
}

int RemoveCommand::execute(string s) {
	if (s.length() == 0) {					// if input string is empty, input was improperly formatted
		return incorrectCommandArgs;
	}
	
	return system->deleteFile(s);			// return same value that deleteFile() does
}
