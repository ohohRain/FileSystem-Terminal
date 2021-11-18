/*



This file declares the necessary functions for the MetadataDisplayVisitor, which is used
to display information about particular files, including the file name, how many characters
are in the file, and file type.


*/

#pragma once
// declaration of MetadataDisplayVisitor here

#include "AbstractFileVisitor.h"

class MetadataDisplayVisitor : public AbstractFileVisitor {

public:
	virtual void visit_TextFile(TextFile*) override;
	virtual void visit_ImageFile(ImageFile*) override;

};
