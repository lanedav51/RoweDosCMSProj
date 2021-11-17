#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include "user.h"
#include "logs.h"
#include "login.h"
#include "cmsSystem.h"
using namespace std;

int displayUserOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = true;
	string fileName, fileLoc;
	bool inputLoop = false;

	if (contentListExist() == false)
	{
		createContentCsv();
	}

	do {
		cout << "1) View Content 2) Add Content 3) Delete Content\n4) Modify Content 5) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			viewContent(userID);
			break;;
		case 2:
			do {
				cout << "What would you like to call your file?\n";
				cin >> fileName;
				cout << "What is the location of your file?\n";
				cin >> fileLoc;
				if (addContent(userID, fileName, fileLoc) == true)
				{
					inputLoop = false;
				}
			} while (inputLoop == true);
			break;;
		case 3:
			cout << "What file would you like to delete?\n";
			cin >> fileName;
			deleteContent(userID, fileName);
			break;;
		case 4:
			//modifyContent(userID);
			break;;
		case 5:
			cout << "Come again" << endl;
			return 0;
			break;;
		default:
			cout << "Please enter a valid choice, 1, 2, 3, or 4." << endl;
			choiceLoop = true;
		}
	} while (choiceLoop == true);
}
int displayAdminOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = true;
	bool inputLoop = false;
	string fileName, fileLoc;

	if (contentListExist() == false)
	{
		createContentCsv();
	}

	do {
		cout << "1) View Content 2) Add Content 3) Delete Content\n4) Modify Content 5) Edit User Privileges 6) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			viewContent(userID);
			break;;
		case 2:
			do {
				cout << "What would you like to call your file?\n";
				cin >> fileName;
				cout << "What is the location of your file?\n";
				cin >> fileLoc;
				if (addContent(userID, fileName, fileLoc) == false)
				{
					inputLoop = false;
				}
			} while (inputLoop == true);
			break;;
		case 3:
			cout << "What file would you like to delete?\n";
			cin >> fileName;
			deleteContent(userID, fileName);
			break;;
		case 4:
			//modifyContent(userID);
			break;;
		case 5:
			//edit user permissions
			break;;
		case 6:
			cout << "Come again" << endl;
			return 0;
			break;;
		default:
			cout << "Please enter a valid choice, 1, 2, 3, or 4." << endl;
			choiceLoop = true;
		}
	} while (choiceLoop == true);

}

bool contentListExist()
{
	fstream file("contentList.csv");
	return file.good();
}

bool createContentCsv()
{
	fstream contentList;
	contentList.open("contentList.csv", fstream::out);
	contentList << "FILE_NAME," << "FILE_SIZE," << "FILE_LOC," << "OWNER_ID," << "\n";
	contentList.close();
	cout << "CSV Made" << endl;
	return true;
}

bool viewContent(int userID)
{
	cout << "Here are the files you have access to...\n_________________________________________\nNAME          FILESIZE         FILE LOCATION\n___________________________________________________\n";
	//For each line, if userID is equal to ownerID, print out the other 3
	vector<string> fileNames, fileLocs, fileSizes, fileOwners;
	fileNames = getFileNames();
	fileLocs = getFileLocations();
	fileSizes = getFileSizes();
	fileOwners = getFileOwners();

	int i = 0;
	//cout << fileOwners.size();
	for (i = 0; i < fileOwners.size(); i++)
	{
		if (to_string(userID) == fileOwners[i])
		{
			cout << fileNames[i] << "         " << fileSizes[i] << "             " << fileLocs[i] << endl;
		}
	}

	return true;
}

vector<string> getFileNames()
{
	fstream contentList("contentList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> fileNames;
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(contentList, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 0; i < fileVal.size(); i += 4)
	{
		fileNames.push_back(fileVal[i]);
	}

	contentList.close();

	return fileNames;
}

vector<string> getFileSizes()
{
	fstream contentList("contentList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> fileSizes;
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(contentList, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 1; i < fileVal.size(); i += 4)
	{
		fileSizes.push_back(fileVal[i]);
	}

	contentList.close();

	return fileSizes;
}


vector<string> getFileLocations()
{
	fstream contentList("contentList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> fileLocations;
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(contentList, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 2; i < fileVal.size(); i += 4)
	{
		fileLocations.push_back(fileVal[i]);
	}

	contentList.close();

	return fileLocations;
}

vector<string> getFileOwners()
{
	fstream contentList("contentList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> fileOwners;
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(contentList, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 3; i < fileVal.size(); i += 4)
	{
		fileOwners.push_back(fileVal[i]);
	}

	contentList.close();

	return fileOwners;
}

float getFileSize(string fileLoc)
{
	//not sure how we do this but we gotta
	return 50;
}

bool addContent(int userID, string fileName, string fileLoc)
{
	//take in userId and prompt user what file they want to add
	//append csv and add the file information based on given location

	//first check if the file name or location exists
	//checks to see if username is unique
	fstream contentList("contentList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> fileNames, fileLocs;
	bool fileNameMatch, fileLocationMatch;
	int columnNum = 0;
	int val, i;
	string line, value;

	fileNames = getFileNames();
	fileLocs = getFileLocations();

	for (i = 0; i < fileNames.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			fileNameMatch = true;
			break;
		}
		else
		{
			fileNameMatch = false;
		}
	}

	for (i = 0; i < fileLocs.size(); i++)
	{
		if (fileLoc == fileLocs[i])
		{
			fileLocationMatch = true;
			break;
		}
		else
		{
			fileLocationMatch = false;
		}
	}
	
	if (fileLocationMatch == true || fileNameMatch == true)
	{
		cout << "File locations or name exists, please try again" << endl;
		return false;
	}
	else
	{
		//add the content to csv
		ofstream contentList;
		contentList.open("contentList.csv", ios::app);
		contentList << fileName << "," << /*getFileSize(fileLoc)*/ 50 << "," << fileLoc << "," << userID << ",\n";
		return true;
	}
	return false;
}
bool deleteContent(int userID, string fileName)
{
	//delete content based on name, check ownerId and match, if so delete line

	//first find filename, if it doesnt exist tell user and retry

	//second confirm whether owns it, if doesnt then tell user and retry
	vector<string> contentInfo;
	string line;
	vector<string> fileNames = getFileNames();
	vector<string> ownerIds = getFileOwners();
	string userConfirmation = "";
	fstream contentList;
	for (int i = 0; i < fileNames.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			//match
			if (to_string(userID) == ownerIds[i])
			{
				//match
				cout << "Are you sure you wish to delete this file? (Y/N)" << endl;
				cin >> userConfirmation;
				if (userConfirmation == "y" || userConfirmation == "Y")
				{
					cout << "File being deleted" << endl;
					int j = 0;
					contentList.open("contentList.csv");
					while (getline(contentList, line))
					{
						if ((j != i))
						{
							size_t begin, end = 0;
							string delim = ",";
							while (((end = line.find(delim)) != string::npos))
							{
								contentInfo.push_back(line.substr(0, end));
								line.erase(0, end + delim.length());
							}
						}
						j++;
					}
					contentList.close();

					contentList.open("contentList.csv", ios::out);
					for (int k = 0; k < contentInfo.size(); k++)
					{
						contentList << contentInfo[k] << ",";
						if (k % 4 == 0 && k != 0)
						{
							contentList << "\n";
						}
					}
					contentList.close();
					/*
					if (!contentList.eof())
					{
						for (int k = 0; k < fileNames.size(); k++)
						{
							contentList << contentInfo[k - 1];
						}
						contentList << contentInfo[contentInfo.size() - 1] << "\n";
					}*/

					cout << "File deleted" << endl;
					return true;
				}
				else if(userConfirmation == "N" || userConfirmation == "n")
				{
					cout << "Returning to home screen" << endl;
					return false;
				}

			}
			else
			{
				cout << "You are not the owner of this file" << endl;
				return false;
			}
			
		}
	}

	//lastly confirm deletion
	cout << "Filename not found\n";
	return false;
}
bool modifyContent(int userID)
{
	//this one is weird, ask user if they want content name changed, or file changed
	return true;
}
bool overrideContent(int userID)
{
	//this will keep name same, but change file loc and filesize
	return true;
}
bool changeFileName()
{
	//this will keep fileloc and filesize the same, but change the name
	return true;
}

bool checkPerm()
{
	//this will check if user can own or not, if group is admin always return true
	return true;
}
