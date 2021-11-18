/*


This file declares the necessary functions that are used to "visit" different types of files
and display their contents as part of the visitor pattern.


*/

#pragma once
// declaration of BasicDisplayVisitor here
#include "AbstractFileVisitor.h"

class BasicDisplayVisitor : public AbstractFileVisitor {

public:
	virtual void visit_TextFile(TextFile*) override;
	virtual void visit_ImageFile(ImageFile*) override;

};

