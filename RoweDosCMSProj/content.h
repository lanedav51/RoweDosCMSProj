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

	content()
	{
		fileSize = 0;
		fileName = "";
		fileLoc = "";
		ownerID = -1;
	}

	float getFileSize() { return fileSize; }
	string getFileName() { return fileName; }
	string getFileLoc() { return fileLoc; }
	int getOwnerID() { return ownerID; }

	bool setFileSize(float fileSize) { this->fileSize = fileSize; return true; }
	bool setFileName(string fileName) { this->fileName = fileName; return true; }
	bool setFileLoc(string fileLoc) { this->fileLoc = fileLoc; return true; }
	bool setOwnerID(int ownerID) { this->ownerID = ownerID; return true; }

private:
	float fileSize;
	string fileName;
	string fileLoc;
	int ownerID;
};