#pragma once
#include <string>
using namespace std;

class user
{
	private:
		string username;
		int userID;
		string group;

	public:
		user(string username, int userID, string group)
		{
			this->username = username;
			this->userID = userID;
			this->group = group;
		}
		user()
		{
			username = "";
			userID = -1;
			group = "";
		}

		bool setUser(string username) { this->username = username; return true; }
		bool setUserID() { this->userID = userID; return true; }
		bool setGroup() { this->group = group; return true; }

		string getUser() { return username; }
		int getUserID() { return userID; }
		string getGroup() { return group; }
};