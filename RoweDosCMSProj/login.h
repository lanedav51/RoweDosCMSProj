#pragma once
#include <string>
using namespace std;
//login.h

bool regUser(string user, string pass); //register user to db
int checkDb(string user, string pass); //verify submitted info against db, will return 0 if not found, 1 if wrong, 2 if already exists?
string encryptInfo(); //encrypts info into db
string decryptInfo(); //decrypts info taken from db




