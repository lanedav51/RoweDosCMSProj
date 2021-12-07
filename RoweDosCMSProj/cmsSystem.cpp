#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <filesystem>
#include "user.h"
#include "logs.h"
#include "login.h"
#include "cmsSystem.h"
#include "content.h"
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
				if (!fileExist(fileLoc))
				{
					cout << "File doesn't exist" << endl;
					break;;
				}
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
			modifyContent(userID);
			break;;
		case 5:
			cout << "Come again" << endl;
			logEvent(getUsername(userID), "Exited Program");
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
		cout << "1) View Content 2) Add Content 3) Delete Content\n4) Modify Content 5) Edit User Privileges 6) Print Logs 7) Exit Program" << endl;
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
				if (!fileExist(fileLoc))
				{
					cout << "File doesn't exist" << endl;
					break;;
				}
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
			modifyContent(userID);
			break;;
		case 5:
			changePerm(userID);
			break;;
		case 6:
			printReport();
			break;;
		case 7:
			cout << "Come again" << endl;
			logEvent(getUsername(userID), "Exited Program");
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
	fstream fileStream("contentList.csv");
	if (fileStream.fail())
	{
		return false;
	}
	return true;
}

bool fileExist(string filePath)
{
	fstream fileStream(filePath);
	if (fileStream.fail())
	{
		return false;
	}
	return true;
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
	vector<string> fileNames, fileLocs, fileOwners;
	vector<string> fileSizes;
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
	logEvent(getUsername(userID), "Viewed Content");
	return true;
}

string getUsername(int userID)
{
	vector<string> usernameList = getUsers();
	return usernameList[userID];
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
	float value;
	int columnNum = 0;
	int val, i;
	string line;

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
	ifstream fileSize(fileLoc, ios::binary);
	fileSize.seekg(0, ios::end);
	return fileSize.tellg();
}

string getFileLoc(string fileName)
{
	//compare lists to lists to lists
	vector<string> fileNames = getFileNames();
	vector<string> fileLocations = getFileLocations();

	for (int i = 0; i < fileNames.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			return fileLocations[i];
		}
		else
		{
			return "Failed";
		}
	}
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
	bool fileNameMatch = false, fileLocationMatch = false;
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
	}

	for (i = 0; i < fileLocs.size(); i++)
	{
		if (fileLoc == fileLocs[i])
		{
			fileLocationMatch = true;
			break;
		}
	}
	
	if (fileLocationMatch == true || fileNameMatch == true)
	{
		cout << "File locations or name exists, please try again" << endl;
		string log = "Attempted to add file  " + fileName;
		logEvent(getUsername(userID), log);
		return false;
	}
	else
	{
		//add the content to csv
		ofstream contentList;
		contentList.open("contentList.csv", ios::app);
		contentList << fileName << "," << getFileSize(fileLoc) << "," << fileLoc << "," << userID << ",\n";
		contentList.close();
		string log = "Successfully added file  " + fileName;
		logEvent(getUsername(userID), log);
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
						if (((k+1) % 4 == 0) && k != 0)
						{
							contentList << "\n";
						}
					}
					contentList.close();
					cout << "File deleted" << endl;
					string log = "Successfully deleted file " + fileName;
					logEvent(getUsername(userID), log);
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
				string log = "Attmpted to delete file " + fileName;
				logEvent(getUsername(userID), log);
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
	int choice;
	bool modifyLoop = true;
	string fileName;

	do
	{
		cout << "Would you like to (1)Change Content Path, (2)Change File Name, or (3)Exit?" << endl;
		cin >> choice;
		cout << "What file would you like to modify?" << endl;
		cin >> fileName;

		if (choice == 1)
		{
			if (checkPerm(userID, fileName))
			{
				overrideContent(userID, fileName);
				modifyLoop = false;
			}
			else
			{
				string log = "Attempted to modify file " + fileName;
				logEvent(getUsername(userID), log);
				cout << "You do not have permission to modify this file" << endl;
			}
		}
		else if (choice == 2)
		{
			if (checkPerm(userID, fileName))
			{
				changeFileName(userID, fileName);
				modifyLoop = false;
			}
			else
			{
				cout << "You do not have permission to modify this file" << endl;
			}
		}
		else if (choice == 3)
		{
			cout << "Returning to home screen" << endl;
			return false;
		}
		else
		{
			cout << "Please enter a valid option" << endl;
		}
	} while (modifyLoop == true);
	return true;
}
bool overrideContent(int userID, string fileName)
{
	vector<string> fileNames = getFileNames();
	vector<string> filePaths = getFileLocations();
	vector<string> fileSizes = getFileSizes();
	vector<string> ownerIDs = getFileOwners();
	content current(getFileSize(getFileLoc(fileName)), fileName, getFileLoc(fileName), userID); //init the content being manipulated
	//this will keep name same, but change file loc and filesize
	fstream contentList;
	string path;
	cout << "What will the new file's path be?" << endl;
	cin >> path;
	current.setFileLoc(path);
	current.setFileSize(getFileSize(path));

	for (int i = 0; i < filePaths.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			filePaths[i] = current.getFileLoc();
			fileSizes[i] = current.getFileSize();
		}
	}

	contentList.open("contentList.csv", ios::out);
	for (int i = 0; i < filePaths.size(); i++)
	{
		contentList << fileNames[i] << "," << fileSizes[i] << "," << filePaths[i] << "," << ownerIDs[i] << ",\n";
	}
	contentList.close();

	string log = "Modified file path for " + fileName;
	logEvent(getUsername(userID), log);

	return true;
}
bool changeFileName(int userID, string fileName)
{
	//this will keep fileloc and filesize the same, but change the name
	vector<string> fileNames = getFileNames();
	vector<string> filePaths = getFileLocations();
	vector<string> fileSizes = getFileSizes();
	vector<string> ownerIDs = getFileOwners();
	content current(getFileSize(getFileLoc(fileName)), fileName, getFileLoc(fileName), userID); //init the content being manipulated
	//this will keep name same, but change file loc and filesize
	fstream contentList;
	string newName;
	cout << "What will the new file's path be?" << endl;
	cin >> newName;
	current.setFileName(newName);

	for (int i = 0; i < fileNames.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			fileNames[i] = current.getFileName();
		}
	}

	contentList.open("contentList.csv", ios::out);
	for (int i = 0; i < filePaths.size(); i++)
	{
		contentList << fileNames[i] << "," << fileSizes[i] << "," << filePaths[i] << "," << ownerIDs[i] << ",\n";
	}
	contentList.close();

	string log = "Changed file name from " + fileName + " to " + newName;
	logEvent(getUsername(userID), log);

	return true;
}

bool checkPerm(int userID, string fileName)
{
	//this will check if user can own or not, if group is admin always return true
	vector<string> fileNames = getFileNames();
	vector<string> ownerIds = getFileOwners();

	for (int i = 0; i < fileNames.size(); i++)
	{
		if (fileName == fileNames[i])
		{
			//match
			if (to_string(userID) == ownerIds[i])
			{
				return true;
			}
		}
	}
	return false;
}

bool changePerm(int userID)
{
	bool choiceLoop = true;
	do {
		string username, line, userConfirmation;
		int choice;
		bool usernameExists = false;
		user currentUser;
		fstream userList;
		vector<string> usernameList = getUsers();
		vector<string> userInfo;
		int i = 0, j = 0;
		do
		{
			cout << "Which user would you like to modify?" << endl;
			cin >> username;
			//modify username's permissions, make them an admin if they are user, delete them if they are user
			for (i = 0; i < usernameList.size(); i++)
			{
				if (username == usernameList[i])
				{
					usernameExists = true;
					if (username == currentUser.getUser())
					{
						cout << "You can't select yourself" << endl;
						return false;
					}
					break;
				}
			}
		} while (usernameExists == false);
		
		//assign user info here
		currentUser = setCurrentUser(username);

		cout << "Would you like to (1)Delete User, (2)Promote User, (3) Demote User, or (4)Exit?" << endl;
		cin >> choice;

		if (choice == 1)
		{
			//delete the user
			cout << "Are you sure you want to delete " << currentUser.getUser() << "? (Y,N)" << endl;
			cin >> userConfirmation;
			if (userConfirmation == "y" || userConfirmation == "Y")
			{
				//delete user
				userList.open("userList.csv");
				while (getline(userList, line))
				{
					if ((j != i))
					{
						size_t begin, end = 0;
						string delim = ",";
						while (((end = line.find(delim)) != string::npos))
						{
							userInfo.push_back(line.substr(0, end));
							line.erase(0, end + delim.length());
						}
					}
					j++;
				}
				userList.close();
				
				int x = 1;
				for (int k = 0; k < userInfo.size(); k++)
				{
					if (k % 4 == 0 && k != 0)
					{
						userInfo[k] = to_string(x);
						x++;
					}
				}

				userList.open("userList.csv", ios::out);
				for (int k = 0; k < userInfo.size(); k++)
				{
					userList << userInfo[k] << ",";
					if (((k + 1 )% 4 == 0) && k != 0)
					{
						userList << "\n";
					}
				}
				userList.close();
				cout << "User deleted" << endl;
				return true;
			}
			else if (userConfirmation == "N" || userConfirmation == "n")
			{
				cout << "Returning to home screen" << endl;
				return false;
			}
		}
		else if (choice == 2)
		{
			//Promote user if user
			if (currentUser.getGroup() == "admin")
			{
				cout << "User is already admin" << endl;
				string log = "Attempted to promote user " + currentUser.getUser();
				logEvent(getUsername(userID), log);
				return false;
			}
			else
			{
				//promote the user
				currentUser.setGroup("admin");
				userList.open("userList.csv");
				while (getline(userList, line))
				{
						size_t begin, end = 0;
						string delim = ",";
						while (((end = line.find(delim)) != string::npos))
						{
							userInfo.push_back(line.substr(0, end));
							line.erase(0, end + delim.length());
						}
					j++;
				}

				for (int k = 0; k < userInfo.size(); k++)
				{
					if (currentUser.getUser() == userInfo[k])
					{
						userInfo[k + 2] = currentUser.getGroup();
					}
				}

				userList.close();
				userList.open("userList.csv", ios::out);
				for (int k = 0; k < userInfo.size(); k++)
				{
					userList << userInfo[k] << ",";
					if (((k + 1) % 4 == 0) && k != 0)
					{
						userList << "\n";
					}
				}
				userList.close();
				cout << "User promoted" << endl;
				string log = "Promoted user " + currentUser.getUser();
				logEvent(getUsername(userID), log);
				return true;
			}
		}
		else if (choice == 3)
		{
			//Demote user if admin
			if (currentUser.getGroup() == "user")
			{
				cout << "User is already standard user" << endl;
				string log = "Attempted to demote user " + currentUser.getUser();
				logEvent(getUsername(userID), log);
				return false;
			}
			else
			{
				//demote the user
				currentUser.setGroup("user");
				userList.open("userList.csv");
				while (getline(userList, line))
				{
					size_t begin, end = 0;
					string delim = ",";
					while (((end = line.find(delim)) != string::npos))
					{
						userInfo.push_back(line.substr(0, end));
						line.erase(0, end + delim.length());
					}
					j++;
				}

				for (int k = 0; k < userInfo.size(); k++)
				{
					if (currentUser.getUser() == userInfo[k])
					{
						userInfo[k + 2] = currentUser.getGroup();
					}
				}

				userList.close();
				userList.open("userList.csv", ios::out);
				for (int k = 0; k < userInfo.size(); k++)
				{
					userList << userInfo[k] << ",";
					if (((k + 1) % 4 == 0) && k != 0)
					{
						userList << "\n";
					}
				}
				userList.close();
				cout << "User demoted" << endl;
				string log = "Demoted user " + currentUser.getUser();
				logEvent(getUsername(userID), log);
				return true;
			}
		}
		else if (choice == 4)
		{
			cout << "Returning to home screen" << endl;
			return false;
		}
		else
		{
			cout << "Please enter a correct option" << endl;
		}
	} while (choiceLoop == true);

}