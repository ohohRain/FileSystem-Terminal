======================================================================

This is a project I did with my friends Aaron Stein and Irtaza Waseem

Authors: Irtaza Waseem, Aaron Stein, Rain Chen


======================================================================

Overview:

The purpose of this program is to act as a simulated file system with which the user can interact to make files, 
edit files, remove files, rename files, and more. Another goal of this project was to promote code extensibility
and flexibility. This was implemented through the use of various design patterns that ensured that our code
remains understandable and reusable.


**********************************************************************
Enumerations: 

All of the enumerations used throughout this program are declared in AbstractFile.h in order to keep
them all in a centralized location and ensure that there is no overlap in the specific values assigned
to each error/outcome. This was done in this particular file because practically every other header/source
file in this project required this header file anyways.

In AbstractFile.h
-------------------------------------------------------

"success": enumerated as 0, used to check if the method returned successfully
"cannotAppend": enumerated as 1, returned when cat -a command is being used to append to an image file or an empty file
"imageFileSizeMismatch": enumerated as 2, returned when the square of the size is not equal to the size of the vector, basically when the image dimensions are incorrect
"invalidImagePixel": enumerated as 3, returned when the entered character (anyhwere before the very last character which is a number) is something other than X or a space
"fileAlreadyInSystem": enumerated as 4, returned when user attempts to create a file that already exists in the system
"nullFilePtr": enumerated as 5, returned if the AbstractFile* file pointer points to null
"fileNotOpen": enumerated as 6, returned if user attempts to close a file that isnt even open
"fileIsOpen" enumerated as 7, returned if user attempts to delete a file that is currently open
"fileDoesNotExist": enumerated as 8, returned if user attempts to delete a file that is not in the system because it is not in the files map
"invalidExtension": enumerated as 9, returned if user attempts to create or edit a file that is not supported by the file system e.g. pdf
"invalidPassword": enumerated as 10, returned if user enters the wrong password when trying to edit or display a file
"unableToInsert": enumerated as 11, returned when the program fails to insert the command into the map of commands
"quit": enumerated as 12, returned when user quits the program
"unableToCreateFile": enumerated as 13, returned if the createFile method returns a null pointer
"unableToAddFile": enumerated as 14, returned if the addFile method does not return success
"incorrectCommandArgs": enumerated as 15, returned if the command line arguments are incorrect
"invalidFileName": enumerated as 16, returned if openFile method returns a null pointer
"insufficientMemory" enumerated as 17, returned when program runs out of memory




**********************************************************************
Design Decisions: 

Throughout this project, there were various design and functional decisions that had to be mad. The decisions we made and how the program is intended
to function in various situations are explained in this section.

What inputs do the CommandPrompt and commands accept: This program is configured in such a way that it tolerates
extra whitespace (i.e. spaces and tabs), but it does not tolerate extra characters and strings. For example,
this command is acceptable:
$   touch         <filename>    -p
But this command will cause the program to tell the user that their input is incorrect:
$   touch		  <filename>    -p   extra
Even though the command above contains all the right components in the right order, the input is not accepted
as there is extra input. The same concept is also enforced for the "help" and "q" commands.

Whenever the "-a" command is given in addition to the cat command for an
image file, the program tells the user that they cannot do this. Image files can only be written and overwritten.

Similarly, no empty files can be appended to. If the user attempts to append to any type of file, text or
image, the program will print a message saying that this cannot be done. 

When a command fails to execute as the user intended, the program will always print out a message saying that
the particular command failed. This was added in order to make it clear that something went wrong in the 
program's execution (most likely due to improperly formatted user input). Without this feature, it makes it
much more difficult for the user to know whether or not the command they called completed successfully.

When appending to a password-protected file, two password-protected operations are being used: read() which is
used to display, and append() which is used to append new data to a file. Therefore, when the user tries to
append to a file with a password, they will be prompted for the password on two separate occassions. However, 
this program is implemented in such a way that if the user gets the password wrong the first time, the cat command
automatically fails, and they are not prompted to enter the new data that they will write to the file. If the user
wants to try to append to the file again, they must re-enter the command and get the password correct on
both occassions.

It is possible to copy password-protected files without knowing the password. However, it is impossible to look at or to write
to password-protected files without the password.

If no input is provided to the command prompt, it prints a special error message.

When implementing displayInfo() for macro commands, the issue arises that all macro commands utilize the same
MacroCommand class. Therefore, if we wish to implement multiple macro commands, we cannot simply write out
the information about a macro command in the MacroCommand class. If we did this, all macro commands would display
the same message when the user types "help <macro_command>". However, each macro command is equipped with a parsing
strategy class that is specific to that particular command. Therefore, a displayInfo() method was added to the
RenameParsingStrategy class that prints out the necessary information for the rename command. Then, the displayInfo()
method that lives within the MacroCommand class calls displayInfo() on the pointer to the AbstractParsingStrategy
that the macro command is configured with. In this way, we can get a custom display message for each macro command
since the dynamic type of the parsing strategy will determine what version of displayInfo() is called.

A destructor was implemented for the SimpleFileSystem class. This destructor
iterates through its map of files and calls "delete" on each pointer to AbstractFile that it contains. This prevents
a memory leak upon the program's termination.

In main(), which lives in main.cpp, the SimpleFileSystem and SimpleFileFactory are purposely allocated main's stack frame
and not on the heap. This keeps us from having to explicitly call delete on these objects.

Like the other commands, the goal was to enforce, as previously discussed, that the user cannot enter extra input
when calling a command. In order to implement this behavior for the rename command, the RenameParsingStrategy
object had to be the method to check that the user input was fully correct. However, the parse method within the 
RenameParsingStrategy method returns a vector of strings, not an integer that could be interpreted as an error
value. Therefore, in order for the RenameParsingStrategy to communicate to the execute() method within the MacroCommand
class, an exception is thrown from the parse() method if there is too much input. The exception is immediately caught
from within the execute() method, which causes the execute() method to return the proper enumerated value so that 
the user is notified that their input was incorrectly formatted.



**********************************************************************
Warnings/Errors:

No errors or warnings were encountered when building the program.


**********************************************************************
Tests: 

We ran 15 tests which involved testing all the commands and how well the program tolerates whitespace and extra characters, all 15 tests pass.

Test 1: Testing for quit
C:\Users\irtaza.waseem\source\repos\file-system-and-terminal-project\file-system-and-terminal\x64\Debug>project.exe

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  q

C:\Users\irtaza.waseem\source\repos\file-system-and-terminal-project\file-system-and-terminal\x64\Debug>

Test 1 passes

Test 2: Test the help command and test help followed by a command
C:\Users\irtaza.waseem\source\repos\file-system-and-terminal-project\file-system-and-terminal\x64\Debug>project.exe

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  help
cat                 cp
ds                  ls
rm                  rn
touch

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  help rm
The remove command removes a file from the file system, remove is invoked using command: rm <filename>

Test 2a: In this test, we test what happens if you ask for help for 2 commands in the same sentence, the program rightly ignores the second command added

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  help rm cat
The remove command removes a file from the file system, remove is invoked using command: rm <filename>

Test 2b: Here we test what happens if we ask for help for a command that doesnt exist

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  help lol
Error: lol not found as a command

Test 2 passes.




Test 3: Testing touch command and ls command
C:\Users\irtaza.waseem\source\repos\file-system-and-terminal-project\file-system-and-terminal\x64\Debug>project.exe

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls




Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch file1.txt

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
file1.txt

Test 3 passes


Test 4: Testing cat command, ds command, and testing cat command followed by -a, and testing wq
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat file1.txt
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
hello world
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds file1.txt
hello world

Test 4a: concatenating to a file that does not exist

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat file2.txt
cat failed
For help with invoking cat enter: help cat
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat file1.txt -a
hello world
Enter data you would like to append to the existing file. Enter :wq to save the file and exit, enter :q to exit without saving
hello world
3
3
2            hahahahha
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds file1.txt
hello worldhello world
3
3
2            hahahahha

Test 4 passes


Test 5: Testing the cp command
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cp file1.txt file2

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
file1.txt           file2.txt


Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds file2.txt
hello worldhello world
3
3
2            hahahahha

Test 5 passes

Test 6: Testing the rn command
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
file1.txt           file2.txt


Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  rn file2.txt renamedfile2

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
file1.txt           renamedfile2.txt

Test 6 passes

Test 7: Testing that creating a file with invalid extension doesn't work
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch image1.pdf
touch failed
For help with invoking touch enter: help touch

Test 7 passes


Test 8: Testing what happens if you try to create two files at once
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch image1.img image2.img
touch failed
For help with invoking touch enter: help touch
Test 8 passes


Test 9: Testing cat command on image file
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat image1.img
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
XXXXXXXXX3
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds image1.img
XXX
XXX
XXX

Test 9 passes


Test 10: Testing what happens if you try to remove two files at once

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  rm file1.txt renamedfile2.txt
rm failed
For help with invoking rm enter: help rm

Test 10 passes

Test 11: Creating and adding data to a password protecting file. Also testing what happens if you put invalid password.
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch image2.img -p
Create your password here: 332

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat image2.img
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
XXXX2
:wq
Please enter password for image2.img: 331
Incorrect password
cat failed
For help with invoking cat enter: help cat

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat image2.img
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
XXXX2
:wq
Please enter password for image2.img: 332

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds image2.img
Please enter password for image2.img: 332
XX
XX

Test 11 passes


Test 12: Testing the cp command on image file with password
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cp image2.img image3

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
image2.img          image3.img


Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds image3.img
Please enter password for image3.img: 332
XX
XX

Test 12 passes

Test 13: Testing that cat - a (append) does not work on image file
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch image4.img

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat image4.img
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
XXXX2
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat image4.img -a
Error: Cannot append to a *.img file
cat failed
For help with invoking cat enter: help cat

Test 13 passes


Test 14: Testing that the commands tolerates whitespace
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  touch       newfile.txt

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls
image2.img          image3.img
image4.img          newfile.txt

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat        newfile.txt
Enter data you would like to write to the file. Enter :wq to save the file and exit, enter :q to exit without saving
washu
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds            newfile.txt
washu

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  cat        newfile.txt       -a
washu
Enter data you would like to append to the existing file. Enter :wq to save the file and exit, enter :q to exit without saving
   in st louis
:wq

Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ds      newfile.txt
washu   in st louis

Test 14 passes

Test 15: Testing ls-m
Please input command, q to quit, help for list of commands, or help followed by a command name for more information about that command
$  ls -m
Please enter password for image2.img: 332
image2.img              image   4
Please enter password for image3.img: 332
image3.img              image   4
image4.img              image   4
newfile.txt             text    21

Test 15 passes.

All tests performed showcased the correct and expected behavior.


**********************************************************************
