/*


This file defines how the BasicDisplayVisitor should visit each type of file supported
by this file system.


*/

#include <iostream>
#include "BasicDisplayVisitor.h"
#include "ImageFile.h"
#include "TextFile.h"


using namespace std;

void BasicDisplayVisitor::visit_TextFile(TextFile* file) {
	vector<char> contents = file->read();
	for (unsigned int i = 0; i < file->getSize(); ++i) {
		cout << contents[i];
	}
	cout << endl;
}

void BasicDisplayVisitor::visit_ImageFile(ImageFile* file) {
	vector<char> contents = file->read();
	
	char sizeChar = file->size;
	sizeChar -= 48;
	int size = static_cast<int>(sizeChar);
	int index;

	for (int row = size - 1; row >= 0; --row) {		// prints out contents of image file, lower left corner corresponds to (0,0)
		if (row < size - 1) { cout << '\n'; }
		for (int col = 0; col < size; ++col) {
			index = (row * size) + col;
			cout << contents[index];
			
		}
	}
	cout << '\n';
}






