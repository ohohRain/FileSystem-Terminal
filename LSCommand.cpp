/*


This file defines the necessary methods for the list command, which displays the files
with either just their names, or name, file type, and size of file contents.


*/

#include <iostream>
#include <iomanip>
#include "LSCommand.h"
#include "MetadataDisplayVisitor.h"
#include "AbstractFileSystem.h"



using namespace std;

LSCommand::LSCommand(AbstractFileSystem* s) : system(s) {}

void LSCommand::displayInfo() {
	cout << "The ls command displays all files currently within the system" << endl;
	cout << "Invoke the default ls command: ls" << endl;
	cout << "Invoke the ls metadata command to display one file per line and show metadata: ls -m" << endl;
}

int LSCommand::execute(string s) {
	set<string> fileNames = system->getFileNames();					// get set of file names
	if (s.size() == 0) {											// if no extra input provided
		int count = 0;
		for (auto name = fileNames.begin(); name != fileNames.end(); ++name) {
			cout << left << setw(20) << *name;						// list files in format described in assignment
			++count;
			if (count % 2 == 0) {
				cout << endl;
			}
		}
		cout << endl;
	}
	else {
		if (s == "-m") {

			AbstractFileVisitor* vis = new MetadataDisplayVisitor;				// allocate metadata display visitor
			for (auto name = fileNames.begin(); name != fileNames.end(); ++name) {
				
				AbstractFile* file = system->openFile(*name);
				
				file->accept(vis);											// send visitor to each file
				
				system->closeFile(file);									// make sure to close file
				
			}
			delete vis;														// de-allocate visitor
		}
		else {								// if input is anything other than "-m", then incorrectly formatted input
			return incorrectCommandArgs;
		}
	}
	return success;
}
