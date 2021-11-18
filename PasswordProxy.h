/*



This file declares the PasswordProxy class, which is a particular derived class of
the Abstract file class. The proxy acts as a gateway between the user and a file (that
this class maintains a pointer to).


*/

#pragma once

#include "AbstractFile.h"

class PasswordProxy : public AbstractFile {

public:
	PasswordProxy(AbstractFile* realFile, std::string password);

	~PasswordProxy();


	// public methods that implement AbstractFile interface
	virtual unsigned int getSize() override;
	virtual std::vector<char> read() override;
	virtual int write(std::vector<char>) override;
	virtual int append(std::vector<char>) override;
	virtual std::string getName() override;



	virtual void accept(AbstractFileVisitor* vis) override;			// part of the visitor design pattern
	virtual AbstractFile* clone(std::string& s) override;			// part of the prototype design patern


protected:
	std::string passwordPrompt();					
	bool isCorrectPassword(std::string input);			

private:
	AbstractFile* realFile;											// the file that this proxy protects
	std::string password;


};
