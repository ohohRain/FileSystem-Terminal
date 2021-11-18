/*



This file defines the necessary methods for the text file type, which is one
of 2 types of files supported by this system.


*/

#include <iostream>
#include "TextFile.h"


using namespace std;




// TextFile constructor
TextFile::TextFile(string name) : name(name) {}

// TextFile (kind of) copy constructor -- copy has different name than original
TextFile::TextFile(string name, TextFile& toCopy) : name(name), contents(toCopy.contents) {}


unsigned int TextFile::getSize() {
	return static_cast<unsigned int>(contents.size());
}

string TextFile::getName(){
	return this->name;
}

// overwrites contents of text file
int TextFile::write(vector<char> newVec) {
	this->contents = newVec;
	return success;
}

int TextFile::append(vector<char> newVec) {

	for (unsigned int i = 0; i < newVec.size(); ++i) {
		this->contents.push_back(newVec[i]);
	}
	return success;

}


vector<char> TextFile::read() {
	
	return contents;
}

// method to allow visitors to visit this type of file
void TextFile::accept(AbstractFileVisitor* vis) {
	vis->visit_TextFile(this);
}

// makes a copy of the original with a new name -- part of prototype pattern
AbstractFile* TextFile::clone(string& s) {
	s += ".txt";
	AbstractFile* newFile = new TextFile(s,*this);
	return newFile;
}

