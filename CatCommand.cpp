/*


This file contains the definitions that implement the cat command, which is used to
either overwrite the contents of a file or append to the existing contents.


*/

#include <iostream>
#include <sstream>
#include "CatCommand.h"
#include "AbstractFileSystem.h"


using namespace std;

CatCommand::CatCommand(AbstractFileSystem* s) : system(s) {}

void CatCommand::displayInfo() {

	cout << "The cat command is used to write to a file" << endl;
	cout << "To overwrite the contents of a file, use command: cat <filename>" << endl;
	cout << "To append to the end of an existing file, use command: cat <filename> -a" << endl;

}

int CatCommand::execute(string s) {

	istringstream iss(s);				// wrap input in string stream
	string fileName;
	iss >> fileName;					// first argument in string should be file name
	if (!iss) {
		return incorrectCommandArgs;
	}
	
	
	AbstractFile* file = system->openFile(fileName);		
	if (file == nullptr) {								// if file not found, return
		return invalidFileName;
	}


	string extraCommand;					// search for -a command
	iss >> extraCommand;
	
	

	if (iss) {

		string tooMuch;
		if (iss >> tooMuch) {					// if there is something else to extract, incorrect command
			return incorrectCommandArgs;
		}
		// with -a
		if (extraCommand == "-a") {
			// remember: cannot append to image file
			// here, we find what type of file this is
			int dotIndex = 0;
			for (int i = 0; i < fileName.size(); ++i) {
				if (fileName[i] == '.') {
					dotIndex = i;
				}
			}
			string fileExtension;
			for (int i = dotIndex + 1; i < fileName.size(); ++i) {
				fileExtension += fileName[i];
			}
			if (fileExtension == "img") {
				cout << "Error: Cannot append to a *.img file" << endl;
				//make sure to close the file
				system->closeFile(file);
				return cannotAppend;
			}
			if (file->getSize() == 0) {											// enforce that you cannot append to an empty file
				cout << "Error: Cannot append to an empty file" << endl;
				cout << "Use cat command without -a option to write to " << file->getName() << endl;
				system->closeFile(file);
				return cannotAppend;
			}
			vector<char> contents = file->read();					// read contents of file
			if (contents.size() != file->getSize()) {				// if file size does not match expected size
				system->closeFile(file);
				return invalidPassword;								// then there was an error
			}
			for (char c : contents) {
				cout << c;
			}
			cout << endl << "Enter data you would like to append to the existing file. Enter :wq to save the file and exit, enter :q to exit without saving" << endl;
			
			string input;
			vector<char> toWrite;
			
			

			while (true) {
				
				getline(cin, input);
				
				if (input == ":wq") {
					//make sure to close the file
					system->closeFile(file);
					toWrite.pop_back();
					return file->append(toWrite);
				}
				else if (input == ":q") {
					break;
				}
				else {
					// remember: insert \n after each line
					for (char c : input) {
						toWrite.push_back(c);
					}
					toWrite.push_back('\n');
				}
			}
			

		}
		else {//make sure to close the file
			system->closeFile(file);
			return incorrectCommandArgs;
		}
		
	}
	else {
		// without -a
		cout << "Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving" << endl;
		string input;
		vector<char> toWrite;

		while (true) {

			getline(cin, input);

			if (input == ":wq") {
				//make sure to close the file
				toWrite.pop_back();			// take off last newline char
				system->closeFile(file);
				return file->write(toWrite);
			}
			else if (input == ":q") {
				break;
			}
			else {
				// remember: insert \n after each line
				for (char c : input) {
					toWrite.push_back(c);
				}
				toWrite.push_back('\n');
			}
		}



	}


	//make sure to close the file
	system->closeFile(file);

	return success;
}
