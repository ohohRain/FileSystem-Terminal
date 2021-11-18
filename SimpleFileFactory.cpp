/*



This file defines the necessary methods for a SimpleFileFactory, which is a particular
implementation of the AbstractFileFactory. This factory is capable of creating both
.txt files and .img files.


*/

#include "SimpleFileFactory.h"
#include "AbstractFile.h"
#include "TextFile.h"
#include "ImageFile.h"


using namespace std;

// method for creating files based on the extension of the file name it is given
AbstractFile* SimpleFileFactory::createFile(string name) {
	
	int dotIndex = 0;
	for (int i = 0; i < name.size(); ++i) {
		if (name[i] == '.') {
			dotIndex = i;							// finding the '.' character in the name
		}
	}
	string fileExtension;
	for (int i = dotIndex + 1; i < name.size(); ++i) {
		fileExtension += name[i];					// finding the file extension
	}

	AbstractFile* newFilePtr;						// create new file based on extension found above
	if (fileExtension == "txt") {
		newFilePtr = new TextFile(name);
		return newFilePtr;
	}
	else if (fileExtension == "img") {
		newFilePtr = new ImageFile(name);
		return newFilePtr;
	}
	else {
		return nullptr;
	}

}
