/*


This file declares the abstract base class or interface that all file visitors that can be used
in this program must implement. The functions declared here are part of the visitor pattern.


*/

#pragma once
// declaration of the file visitor interface here

// forward declarations
class TextFile;
class ImageFile;

class AbstractFileVisitor {
public:
	virtual void visit_TextFile(TextFile*) = 0;
	virtual void visit_ImageFile(ImageFile*) = 0;
};
