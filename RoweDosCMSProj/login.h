#pragma once
#include <string>
#include "user.h"
#include "logs.h"
using namespace std;
//login.h

user login(); //does it all in one

bool regUser(string user, string pass, string group); //register user to db, this is only called once user is unique and password meets complexity
bool checkDb(string user, string pass);//checks info against db

bool checkComplexity(string pass);
	//checks the password's complexity

bool checkUniqueUser(string user);//checks to see if username is unique


string encryptInfo();//encrypts info into db

string decryptInfo();//decrypts info taken from db

user setCurrentUser(string username);//returns the current user info by constructing instance of user class, all from matching info given by username





