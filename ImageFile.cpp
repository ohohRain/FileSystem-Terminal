/*


This file defines the necessary methods for the image file type, which is one
of 2 types of files supported by this system.


*/

#include "ImageFile.h"
#include <iostream>

using namespace std;

ImageFile::ImageFile(string name) : name(name), size(0) {}

// this is kind of like a copy constructor, except the copy is given a new name
ImageFile::ImageFile(string name, ImageFile& toCopy) : name(name), size(toCopy.size), contents(toCopy.contents) {}


unsigned int ImageFile::getSize() {
	return static_cast<unsigned int>(contents.size());
}


string ImageFile::getName() {
	return name;
}

int ImageFile::write(vector<char> vec) {			// writing to an img file requires that the input be properly formatted
	while (vec.back() == '\n') {					// if there are any new line chars at back, pop them off
		vec.pop_back();
	}
	char size = vec.back();							// extract dimensions of image
	this->size = size;								// set member variable
	
	int intSize = charToInt(size);					// call method that returns int representation of the char
	
	int sizeSquared = intSize * intSize;			// gives size of whole vector (minus last char that gives dimensions)
	
	// check for size mismatch
	if (sizeSquared != vec.size() - 1) {
		this->size = 0;
		contents.clear();
		return imageFileSizeMismatch;
	}
	contents.clear();
	for (int i = 0; i < vec.size() - 1; ++i) {
		if (vec[i] != ' ' && vec[i] != 'X') {		// check that all "pixels" are 'X' or ' ' 
			this->size = 0;
			contents.clear();
			return invalidImagePixel;
		}
		else {
			contents.push_back(vec[i]);
		}
	}
	

	return success;
}


int ImageFile::charToInt(char c) {
	c -= 48;
	int i = static_cast<int>(c);
	return i;
}


int ImageFile::append(vector<char> newVec) {
	return cannotAppend;
}


vector<char> ImageFile::read() {
	
	return contents;
}



void ImageFile::accept(AbstractFileVisitor* vis) {
	vis->visit_ImageFile(this);
}

AbstractFile* ImageFile::clone(string& s) {
	s += ".img";
	AbstractFile* newFile = new ImageFile(s, *this);
	return newFile;
}

