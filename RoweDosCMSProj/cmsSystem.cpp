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
#include "book.h"
using namespace std;

int displayBookUserOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = true;
	string fileName, fileLoc;
	bool inputLoop = false;

	if (bookListExist() == false)
	{
		createBookCsv();
	}

	do {
		cout << "1) Check Out Books 2) Check In Books 3) View Checked Out Books\n4) View All Available Books 5) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			checkOut(userID);
			break;;
		case 2:
			checkIn(userID);
			break;;
		case 3:
			listCheckOut(userID);
			break;;
		case 4:
			listAll(userID);
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

int displayBookAdminOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = true;
	bool inputLoop = false;
	string fileName, fileLoc;

	if (bookListExist() == false)
	{
		createBookCsv();
	}

	do {
		cout << "1) Check Out Books 2) Check In Books 3) View Checked Out Books\n4) View All Available Books 5) Add Books 6) Delete Books 7) Edit User Privileges 8) Print Logs 9) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			checkOut(userID);
			break;;
		case 2:
			checkIn(userID);
			break;;
		case 3:
			listCheckOut(userID);
			break;;
		case 4:
			listAll(userID);
			break;;
		case 5:
			addBook(userID);
			break;;
		case 6:
			deleteBook(userID);
			break;;
		case 7:
			changePerm(userID);
			break;;
		case 8:
			printReport();
			break;;
		case 9:
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

bool bookListExist()
{
	fstream fileStream("bookList.csv");
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


bool createBookCsv()
{
	fstream bookList;
	bookList.open("bookList.csv", fstream::out);
	bookList << "BOOK_ID," << "TITLE," << "AUTHOR," << "CHECKOUT," << "TIME," << "\n";
	bookList.close();
	cout << "CSV Made" << endl;
	return true;
}

string getDate()
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	//logs an event that happens, giving user information, time, and action
	int year = 1900 + newtime.tm_year;
	int month = 1 + newtime.tm_mon;
	int day = newtime.tm_mday;

	string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
	return date;
}

bool checkOut(int userID)
{
	vector<string> names, authors, users, times;
	getBookInfo(names, authors, users, times);
	string bookName;
	bool match = false;
	int i;
	//Prompts user for which book
	//If other user has it, let current user know
	//If it doesn't exist, let current user know
	//If it does exist, assign user to book and set time checked out
	//All it does is set the time checked out and assign CHECKOUT to current user?
	cout << "Which book would you like to check out?" << endl;
	cin >> bookName;

	for (i = 0; i < names.size(); i++)
	{
		if (bookName == names[i])
		{
			match = true;
			if (users[i] == "false")
			{
				book current(to_string(i), names[i], authors[i], users[i], times[i]); //init the content being manipulated
	//this will keep name same, but change file loc and filesize
				fstream bookList;
				current.setUser(to_string(userID));
				current.setDate(getDate());

				for (int i = 0; i < names.size(); i++)
				{
					if (bookName == names[i])
					{
						users[i] = current.getUser();
						times[i] = current.getDate();
					}
				}

				bookList.open("bookList.csv", ios::out);
				for (int i = 0; i < names.size(); i++)
				{
					bookList << i << "," << names[i] << "," << authors[i] << "," << users[i] << "," << times[i] << ",\n";
				}
				bookList.close();

				string log = "Checked out book " + bookName;
				logEvent(getUsername(userID), log);
				return true;

			}
			else
			{
				cout << "Book is already checked out by another user" << endl;
				return false;
			}
		}
		else
		{
			match = false;
		}
	}
	if (match == false)
	{
		cout << "Book doesn't exist, returning to menu" << endl;
		return false;
	}
}

bool checkIn(int userID)
{
	vector<string> names, authors, users, times;
	getBookInfo(names, authors, users, times);
	string bookName;
	bool match = false;
	int i;
	//Prompts user for which book
	//Tells user if book exists, and if so, if user hasn't checked it out, alert and loop
	//If reqs met, make checkout false and reset time to null
	cout << "Which book would you like to check in?" << endl;
	cin >> bookName;

	for (i = 0; i < names.size(); i++)
	{
		if (bookName == names[i])
		{
			match = true;
			if (users[i] == to_string(userID))
			{
				book current(to_string(i), names[i], authors[i], users[i], times[i]); //init the content being manipulated
	//this will keep name same, but change file loc and filesize
				fstream bookList;
				current.setUser("false");
				current.setDate("null");

				for (int i = 0; i < names.size(); i++)
				{
					if (bookName == names[i])
					{
						users[i] = current.getUser();
						times[i] = current.getDate();
					}
				}

				bookList.open("bookList.csv", ios::out);
				for (int i = 0; i < names.size(); i++)
				{
					bookList << i << "," << names[i] << "," << authors[i] << "," << users[i] << "," << times[i] << ",\n";
				}
				bookList.close();

				string log = "Checked out book " + bookName;
				logEvent(getUsername(userID), log);
				return true;

			}
			else
			{
				cout << "You have not checked this book out" << endl;
				return false;
			}
		}
		else
		{
			match = false;
		}
	}
	if (match == false)
	{
		cout << "Book doesn't exist, returning to menu" << endl;
		return false;
	}
}

bool listCheckOut(int userID)
{
	vector<string> names, authors, users, times;
	getBookInfo(names, authors, users, times);
	//Lists all books that match userID and CHECKOUT
	cout << "Here are all of the books you have checked out: " << endl;
	int i = 0;
	//cout << fileOwners.size();
	for (i = 0; i < users.size(); i++)
	{
		if (to_string(userID) == users[i])
		{
			cout << names[i] << " : " << authors[i] << endl;
		}
	}
	logEvent(getUsername(userID), "Listed Checked Out Books");
	return true;
}

bool listAll(int userID)
{
	vector<string> names, authors, users, times;
	getBookInfo(names, authors, users, times);
	//Lists all books that have false as CHECKOUT
	cout << "Here are all of the books available for check out: " << endl;
	//For each line, if userID is equal to ownerID, print out the other 3

	int i = 0;
	//cout << fileOwners.size();
	for (i = 0; i < users.size(); i++)
	{
		if ("false" == users[i])
		{
			cout << names[i] << " : " << authors[i] << endl;
		}
	}
	logEvent(getUsername(userID), "Listed All Books");
	return true;
}

bool addBook(int userID)
{
	//add content but adding book lol
	//take in userId and prompt user what file they want to add
	//append csv and add the file information based on given location

	//first check if the file name or location exists
	//checks to see if username is unique
	fstream contentList("bookList.csv");
	vector<string> names, authors, users, times;
	getBookInfo(names, authors, users, times);
	bool bookNameMatch = false;
	int columnNum = 0;
	int val, i;
	string line, value, bookName, authorName;

	cout << "What is the name of the book you would like to add: ";
	cin.ignore();
	getline(cin, bookName);

	cout << "What is the name of the author: ";
	getline(cin, authorName);

	for (i = 0; i < names.size(); i++)
	{
		if (bookName == names[i])
		{
			bookNameMatch = true;
			break;
		}
	}

	if (bookNameMatch == true)
	{
		cout << "Book name already exists, please try again" << endl;
		string log = "Attempted to add book  " + bookName;
		logEvent(getUsername(userID), log);
		return false;
	}
	else
	{
		//add the content to csv
		ofstream bookList;
		bookList.open("bookList.csv", ios::app);
		bookList << to_string(names.size()) << "," << bookName << "," << authorName << "," << "false" << "," << "null" << ",\n";
		bookList.close();
		string log = "Successfully added book " + bookName;
		logEvent(getUsername(userID), log);
		return true;
	}
	return false;
}

bool deleteBook(int userID)
{
	//delete content but deleting book lol
	vector<string> names, authors, users, times;
	vector<string> bookListInfo;
	getBookInfo(names, authors, users, times);
	string line, bookName;
	string userConfirmation = "";
	fstream bookList;

	cout << "What is the name of the book you would like to delete: ";
	cin.ignore();
	getline(cin, bookName);

	for (int i = 0; i < names.size(); i++)
	{
		if (bookName == names[i])
		{
			//match
				cout << "Are you sure you wish to delete this book? (Y/N)" << endl;
				cin >> userConfirmation;
				if (userConfirmation == "y" || userConfirmation == "Y")
				{
					cout << "Book deleted" << endl;
					int j = 0;
					bookList.open("bookList.csv");
					while (getline(bookList, line))
					{
						if ((j != i))
						{
							size_t begin, end = 0;
							string delim = ",";
							while (((end = line.find(delim)) != string::npos))
							{
								bookListInfo.push_back(line.substr(0, end));
								line.erase(0, end + delim.length());
							}
						}
						j++;
					}
					bookList.close();

					bookList.open("bookList.csv", ios::out);
					for (int k = 0; k < bookListInfo.size(); k++)
					{
						bookList << bookListInfo[k] << ",";
						if (((k + 1) % 5 == 0) && k != 0)
						{
							bookList << "\n";
						}
					}
					bookList.close();
					string log = "Successfully deleted book " + bookName;
					logEvent(getUsername(userID), log);
					return true;
				}
				else if (userConfirmation == "N" || userConfirmation == "n")
				{
					cout << "Returning to home screen" << endl;
					return false;
				}
		}
	}

	//lastly confirm deletion
	cout << "Filename not found\n";
	return false;
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

bool getBookInfo(vector<string>& names, vector<string>& authors, vector<string>& users, vector<string>& times)
{
	fstream bookList("bookList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(bookList, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 0; i < fileVal.size(); i += 5)
	{
		names.push_back(fileVal[i+1]);
		authors.push_back(fileVal[i + 2]);
		users.push_back(fileVal[i + 3]);
		times.push_back(fileVal[i + 4]);
	}

	bookList.close();

	return true;
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