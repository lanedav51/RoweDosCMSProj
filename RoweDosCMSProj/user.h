#pragma once
#include <string>
using namespace std;

class user
{
	public:

		string getUser() { return user; }
		int getUserID() { return userID; }
		string getGroup() { return group; }
	private:
		string user = "";
		int userID = -1;
		string group = "";
};