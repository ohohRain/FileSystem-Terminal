/*


This file defines the necessary methods for the touch command, which is used
to create files. The program passes to this class a name for the new file, and this
class asks the factory to create the file. Then the new file is added to the system.


*/

#include <iostream>
#include <sstream>
#include "TouchCommand.h"
#include "AbstractFileFactory.h"
#include "AbstractFileSystem.h"
#include "PasswordProxy.h"


using namespace std;

TouchCommand::TouchCommand(AbstractFileSystem* s, AbstractFileFactory* f) : system(s), factory(f) {}


void TouchCommand::displayInfo() {

	cout << "The touch command creates a file, currently, this system only supports *.txt and *.img files" << endl;
	cout << "touch can be invoked with the command: touch <filename>" << endl;
	cout << "touch can also be invoked to create password protected files with the command: touch <filename> -p" << endl;

}


int TouchCommand::execute(string s) {


	istringstream iss(s);
	
	string fileName;
	iss >> fileName;				// extract name of new file
	if (!iss) {						// if extraction failed, return error
		return incorrectCommandArgs;
	}

	
	string extraCommand;			// search for an extra command
	iss >> extraCommand;

	if (iss) {						// if there is a second input

		string tooMuch;
		if (iss >> tooMuch) {		// search for another input, if there is one, return an error
			return incorrectCommandArgs;
		}

		if (extraCommand == "-p") {		// if the second input is "-p", create password-protected file
			AbstractFile* newFile = this->factory->createFile(fileName);
			if (newFile == nullptr) {
				return unableToCreateFile;
			}
			else {
				string password = getPassword();	// get desired password from user
				AbstractFile* proxy = new PasswordProxy(newFile,password);		// create proxy from file we created and the desired password
				
				int addOutcome = system->addFile(fileName, proxy);
				if (addOutcome != success) {
					delete proxy;					// deleting proxy will call destructor for real file that it protects
					return unableToAddFile;
				}
			}

		}
		else {
			return incorrectCommandArgs;
		}
	}
	else {														// if there was no extra input (i.e. input was only touch <filename>)
		AbstractFile* newFile = this->factory->createFile(s);	// create file
		if (newFile == nullptr) {
			return unableToCreateFile;
		}
		else {
			int addOutcome = system->addFile(s, newFile);		// add new file to system and return failure if adding fails
			if (addOutcome != success) {
				delete newFile;
				return unableToAddFile;
			}
		}
	}



	
	return success;

}

// method to prompt user for new password
string TouchCommand::getPassword() {
	cout << "Create your password here: ";
	string password;
	getline(cin, password);
	return password;
}
