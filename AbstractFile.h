/*


This file declares the abstract base class or interface that all files that this file system supports must define
in their implementations. This file also contains all of the error/outcome enumerations used throughout the entire
program.


*/

#pragma once
#include <vector>
#include <string>
#include "AbstractFileVisitor.h"

// enumerations for possible outcomes
enum outcomeVals { success = 0 , cannotAppend = 1 , imageFileSizeMismatch = 2 , invalidImagePixel = 3, fileAlreadyInSystem = 4 , nullFilePtr = 5, 
	fileNotOpen = 6, fileIsOpen = 7, fileDoesNotExist = 8, invalidExtension = 9 , invalidPassword = 10, unableToInsert = 11, quit = 12, unableToCreateFile = 13,
	unableToAddFile = 14 , incorrectCommandArgs = 15 , invalidFileName = 16, insufficientMemory = 17 };


class AbstractFile {
public:

	virtual ~AbstractFile() = default;

	virtual std::vector<char> read() = 0;
	virtual int write(std::vector<char>) = 0;
	virtual int append(std::vector<char>) = 0;
	virtual unsigned int getSize() = 0;
	virtual std::string getName() = 0;


	virtual void accept(AbstractFileVisitor* vis) = 0;		// accept function is used to implement visitor pattern

	virtual AbstractFile* clone(std::string&) = 0;			// clone function is used to implement prototype pattern


};

