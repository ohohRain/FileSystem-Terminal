/*


This file declares the necessary functions for the TextFile class, which is a type of file
that this system knows how to handle.


*/

#pragma once
// TextFile declaration goes here
#include "AbstractFile.h"

class TextFile : public AbstractFile{
public:
	
	
	// constructor
	TextFile(std::string name);
	// copy constructor
	TextFile(std::string, TextFile& toCopy);

	// public methods that implement AbstractFile interface
	virtual unsigned int getSize() override;
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override;
	virtual int append(std::vector<char>) override;
	virtual std::string getName() override;

	virtual void accept(AbstractFileVisitor* vis) override;

	virtual AbstractFile* clone(std::string& s) override;

private:
	// private member variables (can be accessed through member functions)
	std::vector<char> contents;
	std::string name;


};
