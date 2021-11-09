#include <string>
#include <cstdlib>
#include <iostream>
#include "cmsSystem.h"
#include "content.h"
#include "login.h"
#include "logs.h"
#include "user.h"
using namespace std;

void main()
{
	user currentUser;
	string group;
	int userID;
	string username;

	//literally call to all
	currentUser = login();
	group = currentUser.getGroup();
	userID = currentUser.getUserID();
	username = currentUser.getUser();
	//once logged in, prompt user based on options
	if (group == "admin")
	{
		//run admin options
		cout << "Welcome " + username + ", here are your administrative privileges" << endl;
		displayAdminOptions(userID);
	}
	else if (group == "user")
	{
		//run user options
		cout << "Welcome " + username + ", here are your standard user privileges" << endl;
		displayUserOptions(userID);
	}
	else
	{
		cout << "Problem getting user group" << endl;
		exit(EXIT_FAILURE);
		//exit with failure to get group
	}


}