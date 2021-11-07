#pragma once
#include <string>
using namespace std;

class content
{
public:
	content(float fileSize, string fileName, string fileLoc, int ownerID)
	{
		this->fileSize = fileSize;
		this->fileName = fileName;
		this->fileLoc = fileLoc;
		this->ownerID = ownerID;
	}

	float getFileSize() { return fileSize; }
	string getFileName() { return fileName; }
	string getFileLoc() { return fileLoc; }
	int getOwnerID() { return ownerID; }

private:
	float fileSize = 0;
	string fileName = "";
	string fileLoc = "";
	int ownerID = -1;
};