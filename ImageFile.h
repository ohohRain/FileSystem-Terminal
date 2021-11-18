/*


This file declares the necessary functions for the ImageFile class, which is a type of file
that this system knows how to handle. 


*/

#pragma once
// Image file class declaration here
#include "AbstractFile.h"


class ImageFile : public AbstractFile {


public:
	ImageFile(std::string name);					// constructor
	ImageFile(std::string name, ImageFile& toCopy);	// (sort-of) copy constructor -- the copy has its own name


	virtual unsigned int getSize() override;
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override;
	virtual int append(std::vector<char>) override;
	virtual std::string getName() override;

	virtual void accept(AbstractFileVisitor* vis) override;	// necessary accept() as part of visitor pattern


	int charToInt(char c);				// useful for converting character into an integer
	char size;							// char to hold dimension of formatted image (not the same as contents.size())

	virtual AbstractFile* clone(std::string& s) override;		// clone() method as part of prototype pattern


private:
	std::string name;
	std::vector<char> contents;
	

	


};

