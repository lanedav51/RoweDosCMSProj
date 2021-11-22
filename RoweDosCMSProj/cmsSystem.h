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

int displayUserOptions(int userID);
int displayAdminOptions(int userID);


bool encryptContent();
bool decryptContent();

vector<string> getFileNames();
vector<string> getFileLocations();
vector<string> getFileSizes();
vector<string> getFileOwners();

bool fileExist(string fileLoc);
bool contentListExist();
bool createContentCsv();

bool viewContent(int userID);
bool addContent(int userID, string fileName, string fileLoc);
bool deleteContent(int userID, string fileName);
bool modifyContent(int userID);
bool overrideContent(int userID, string fileName);
bool changeFileName(int userID, string fileName);

bool checkPerm(int userID, string fileName);
bool changePerm(int userID);


