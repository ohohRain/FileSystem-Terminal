/*



This file defines the necessary methods for the password proxy, which acts as
a gateway between the user and the file that the proxy protects and maintains
a pointer to.


*/

#include "PasswordProxy.h"
#include "AbstractFile.h"
#include <iostream>

using namespace std;

PasswordProxy::PasswordProxy(AbstractFile* file, string p) : realFile(file), password(p) {}



PasswordProxy::~PasswordProxy() {			// when this proxy gets deleted, we must delete the file it protects as well to prevent memory leak
	delete this->realFile;
}

// prompts user for password
string PasswordProxy::passwordPrompt() {

	cout << "Please enter password for " << this->getName() << ": ";
	string input;
	getline(cin, input);
	return input;
}

// determines if password is correct and prints message if incorrect
bool PasswordProxy::isCorrectPassword(string input) {

	if (input == this->password) {
		return true;
	}
	else {
		cout << "Incorrect password" << endl;
		return false;
	}

}


// if password is correct, calls read() on file that proxy protects
vector<char> PasswordProxy::read() {
	string input = passwordPrompt();
	bool correct = isCorrectPassword(input);
	if (correct) {
		return this->realFile->read();
	}
	else {
		vector<char> empty;
		return empty;
	}
}

// if password is correct, calls write() on file that proxy protects
int PasswordProxy::write(vector<char> toWrite) {
	string input = passwordPrompt();
	bool correct = isCorrectPassword(input);
	if (correct) {
		return this->realFile->write(toWrite);
	}
	else {
		return invalidPassword;
	}
}

// if password is correct, calls append() on file that proxy protects
int PasswordProxy::append(vector<char> toWrite) {
	string input = passwordPrompt();
	bool correct = isCorrectPassword(input);
	if (correct) {
		return this->realFile->append(toWrite);
	}
	else {
		return invalidPassword;
	}
}

unsigned int PasswordProxy::getSize() {
	return this->realFile->getSize();
}

string PasswordProxy::getName() {
	return this->realFile->getName();
}

// if password is correct, calls accept() on file that proxy protects
void PasswordProxy::accept(AbstractFileVisitor* vis) {
	string input = passwordPrompt();
	bool correct = isCorrectPassword(input);
	if (correct) {
		return this->realFile->accept(vis);
	}
}

// creates a new proxy that maintains a pointer to a new file that is a copy of the original file
AbstractFile* PasswordProxy::clone(string& s) {
	AbstractFile* newProxy = new PasswordProxy(this->realFile->clone(s),this->password);
	return newProxy;
}

