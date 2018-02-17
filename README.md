Anjaney Sharma,
I have written C++ script which can work in windows and perform the tasks given in assignment.

HOW TO USE:
No user input is required for a typical run.
In 2nd function, program will automatically detect username of PC but if it fails it will ask for username input and still it fails to locate Desktop folder it will ask for the path of directory in which Desktop and Documents folders are located.

DETAILS:
The program has two parts:
1. 1st is of finding 10 largest size files - 
	Assumption made is that the drive letters are between A-Z.
	Algo - For every alphabet I checked if it is valid drive letter, if it is then getlargefiles() is called.
		   I made a global vector of size 11 storing the file size and file's full path.
		   For each entry after 10, vector is sorted thus maintaining top 10 large files and the new file is pushed in vector[11] position each time. Vector size is always <= 11 thus not much space is used and time taken is also less since one file entry is traversed once.

2. 2nd is of cleaning Desktop.
	Assumption made is that there is no file of size 0 bytes.
	Algo - I constructed a map of string and vector of strings. In the key, the extension of files is saved   and in the vector, all files name of that extension are saved. Then I used rename() function which changes the file's path accordingly.
	
	
Author - Anjaney Sharma.
			
