#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include "user.h"
#include "logs.h"
#include "login.h"
using namespace std;
//login.h

user login()
{
	user currentUser;
	string username;
	string group;
	string password;
	int userID;
	int choice = -1;
	bool loginLoop = true;
	bool passLoop = true;
	bool userLoop = true;
	bool regSuccess = false;

	do
	{
		if (userListExist() == false)
		{
			createUserCsv();
		}
		cout << "Welcome, would you like to (1)login, (2)register, or (3)exit the program?" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter username... " << endl;
			cin >> username;
			cout << "Enter password... " << endl;
			cin >> password;
			while (userLoop == true) { //accept and check both
				if (checkDb(username, password) == false)
				{
					cout << "Username or password is incorrect, please try again" << endl; //dont let potential attacker know which is incorrect, user will know
					cout << "Enter username... " << endl;
					cin >> username;
					cout << "Enter password... " << endl;
					cin >> password;
				}
				else
				{
					userLoop = false;
					currentUser = setCurrentUser(username);
					return currentUser;
				}
			}
			break;;

		case 2: //Potentially add password reentry for future version
			cout << "Enter username for registration" << endl;
			cin >> username;
			while (userLoop == true) {
				if (checkUniqueUser(username) == false)
				{
					cout << "Username already taken, please enter another one" << endl;
					cin >> username;
				}
				else
				{
					userLoop = false;
				}
			}
			cout << "Enter password for registration...\nPassword must have 3 of the following\nUppercase Letters, Lowercase Letters, Numbers, and Symbols(@#$%&)" << endl;
			cin >> password;
			while (passLoop == true) {
				if (checkComplexity(password) == false)
				{
					cout << "Please enter another password...\nPassword must have 3 of the following\nUppercase Letters, Lowercase Letters, Numbers, and Symbols(@#$%&)" << endl;
					cin >> password;
				}
				else
				{
					passLoop = false;
				}
			}

			regSuccess = regUser(username, password, "user"); //registers user into xlsx
			if (regSuccess == true)
			{
				return setCurrentUser(username);
			}
			break;;

		case 3: //exits on choice 3
			cout << "Come again homie" << endl;
			exit(0);
		default: //default loops login
			cout << "Please enter a valid choice, 1, 2 or 3" << endl;
			loginLoop = true;
		}
	} while (loginLoop == true);

	return currentUser;
}//does it all in one

bool userListExist()
{
	fstream file("userList.csv");
	return file.good();
}

vector<string> getUsers()
{
	fstream userList("userList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> usernames;
	vector<string> userInfo;
	int columnNum = 0;
	int val, i, userId, k = 0;
	string line, value;
	bool match = false;

	while (getline(userList, line))
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
		usernames.push_back(fileVal[i]);
	}

	userList.close();
	return usernames;
}

bool regUser(string user, string pass, string group) //register user to db
{
	//this is only called once user is unique and password meets complexity USING CSV
	fstream userIdList;
	userIdList.open("userList.csv");
	//find userID
	int userId = 0;
	string line;
	while (getline(userIdList, line))
	{
		userId++;
	}
	userIdList.close();

	ofstream userList;
	userList.open("userList.csv", ios::app);

	if (checkUniqueUser(user) == true && checkComplexity(pass) == true)
	{
		userList << userId << "," << user << "," << pass << "," << "user," << "\n";
		cout << "Registering" << endl;
	}
	else
	{
		cout << "Failed somewhere" << endl;
		return false;
	}

	userList.close();
	return true;
}

bool createUserCsv()
{
	fstream userList;
	userList.open("userList.csv", fstream::out);
	userList << "USERID," << "USERNAME," << "PASSWORD," << "GROUP," << "\n";
	userList.close();
	cout << "CSV Made" << endl;
	return true;
}



bool checkDb(string user, string pass)//checks info against db
{
	//returns the current user info by constructing instance of user class, all from matching info given by username
	fstream userList("userList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> usernames;
	vector<string> userInfo;
	int columnNum = 0;
	int val, i, userId, k = 0;
	string line, value;
	bool match = false;

	usernames = getUsers();

	for (i = 0; i < usernames.size(); i++)
	{
		if (user == usernames[i])
		{
			//Matched user
			userId = i;
			match = true;
			break;
		}
		else
		{
			match = false;
		}
	}

	if (match == false)
	{
		return false;
	}

	userList.close();
	userList.open("userList.csv");

	while (getline(userList, line))
	{
		if (k == userId)
		{
			size_t begin, end = 0;
			string delim = ",";
			while ((end = line.find(delim)) != string::npos)
			{
				userInfo.push_back(line.substr(0, end));
				line.erase(0, end + delim.length());
			}
			if (userInfo[2] == pass)
			{
				match = true;
				return true;
			}
			else
			{
				match = false;
			}
		}
		else
		{
			k++;
		}
	}
	if (match == false)
	{
		return false;
	}
}

bool checkComplexity(string pass)
{
	//checks the password's complexity, regex for password requirements
	regex upper{ "[A-Z]+" };
	regex lower{ "[a-z]+" };
	regex num{ "[0-9]+" };
	regex specialChar{ "[?!&$%#]+" };
	bool upperCheck = false;
	bool lowerCheck = false;
	bool numCheck = false;
	bool specCharCheck = false;
	if (pass.length() <= 8)
	{
		return false;
	}
	else
	{
		upperCheck = regex_search(pass, upper); //searches each and store the boolean val for each true/false
		lowerCheck = regex_search(pass, lower);
		numCheck = regex_search(pass, num);
		specCharCheck = regex_search(pass, specialChar);

		int checkSum = upperCheck + lowerCheck + numCheck + specCharCheck; //adds the bool vals (1 or 0) and verifies that 3 or more are met

		if (checkSum >= 3)// checks the value
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool checkUniqueUser(string user)
{
	//checks to see if username is unique
	fstream userList("userList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> usernames;
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(userList,line))
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
		usernames.push_back(fileVal[i]);
	}

	for (i = 0; i < usernames.size(); i++)
	{
		if (user == usernames[i])
		{
			//Matched user
			return false;
		}
	}

	return true;


}

string encryptInfo()//encrypts info into db
{
	return "true";
}

string decryptInfo()//decrypts info taken from db
{
	return "true";
}

user setCurrentUser(string username)
{
	//returns the current user info by constructing instance of user class, all from matching info given by username
	user currentUser;
	fstream userList("userList.csv");
	vector<string> fileVal; //vector of all values comma delimited
	vector<string> usernames;
	vector<string> userInfo;
	int columnNum = 0;
	int val, i, userId = 0, k = 0;
	string line, value;
	bool match = false;

	usernames = getUsers();

	for (i = 0; i < usernames.size(); i++)
	{
		if (username == usernames[i])
		{
			//Matched user
			userId = i;
			match = true;
			break;
		}
		else
		{
			match = false;
		}
	}
	if (match == false)
	{
		exit(0);
	}

	userList.close();
	userList.open("userList.csv");

	while (getline(userList, line))
	{
		if (k == userId)
		{
			size_t begin, end = 0;
			string delim = ",";
			while ((end = line.find(delim)) != string::npos)
			{
				userInfo.push_back(line.substr(0, end));
				line.erase(0, end + delim.length());
			}
			currentUser.setUserID(userId);
			currentUser.setUser(username);
			currentUser.setGroup(userInfo[3]);
			return currentUser;
		}
		else
		{
			k++;
		}
	}
}
