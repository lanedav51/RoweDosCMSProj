#pragma once
#include <iostream>
#include <fstream>
#include <string>
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
	bool loginLoop = false;
	bool passLoop = true;
	bool userLoop = true;

	do
	{
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
				}
			}

			currentUser = setCurrentUser(username);

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
			cout << "Enter password for registration, must meet COMPLEXITY REQUIREMENT HERE" << endl;
			cin >> password;
			while (passLoop == true) {
				if (checkComplexity(password) == false)
				{
					cout << "Please enter another password that meets REQUIREMENTS HERE" << endl;
					cin >> password;
				}
				else
				{
					passLoop = false;
				}
			}

			regUser(username, password, "user"); //registers user into xlsx

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

bool regUser(string user, string pass, string group) //register user to db
{
	//this is only called once user is unique and password meets complexity USING CSV
	ofstream userList;
	userList.open("userList.csv");
	//ye
	userList.close();
}

bool createUserCsv()
{
	ofstream userList("userList.csv");
	userList << "USERID," << "USERNAME" << "PASSWORD" << "GROUP";
	userList.close();
}

bool checkDb(string user, string pass)//checks info against db
{

}

bool checkComplexity(string pass)
{
	//checks the password's complexity

}

bool checkUniqueUser(string user)
{
	//checks to see if username is unique
}

string encryptInfo()//encrypts info into db
{

}

string decryptInfo()//decrypts info taken from db
{

}

user setCurrentUser(string username)
{
	//returns the current user info by constructing instance of user class, all from matching info given by username
}
