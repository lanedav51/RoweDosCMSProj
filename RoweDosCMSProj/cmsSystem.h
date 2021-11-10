#pragma once

#include <string>
using namespace std;

int displayUserOptions(int userID);
int displayAdminOptions(int userID);


bool encryptContent();
bool decryptContent();

string viewContent(int userID);
string addContent(int userID);
bool deleteContent(int userID);
bool modifyContent(int userID);
bool overrideContent(int userID);
bool changeFileName();

bool checkPerm();


