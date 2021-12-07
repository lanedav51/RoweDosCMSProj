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

string getUsername(int userID);

bool bookListExist();
bool createBookCsv();
int displayBookUserOptions(int userID);
int displayBookAdminOptions(int userID);
bool checkIn(int userID);
bool checkOut(int userID);
bool listCheckOut(int userID);
bool listAll(int userID);
bool addBook(int userID);
bool deleteBook(int userID);
bool getBookInfo(vector<string>& names, vector<string>& authors, vector<string>& users, vector<string>& times);

bool fileExist(string fileLoc);
bool changePerm(int userID);


