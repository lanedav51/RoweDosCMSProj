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

user login(); //does it all in one

bool userListExist();
bool createUserCsv();
bool regUser(string user, string pass, string group); //register user to db, this is only called once user is unique and password meets complexity
bool checkDb(string user, string pass);//checks info against db

vector<string> getUsers(); //returns vector of list of usernames

bool checkComplexity(string pass);
	//checks the password's complexity

bool checkUniqueUser(string user);//checks to see if username is unique


string encryptInfo();//encrypts info into db

string decryptInfo();//decrypts info taken from db

user setCurrentUser(string username);//returns the current user info by constructing instance of user class, all from matching info given by username





