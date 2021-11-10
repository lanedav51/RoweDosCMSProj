#pragma once

#include <string>
#include <iostream>
#include "cmsSystem.h"
using namespace std;

int displayUserOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = false;

	do {
		cout << "1) View Content 2) Add Content 3) Delete Content\n4) Modify Content 5) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			viewContent(userID);
			break;;
		case 2:
			addContent(userID);
			break;;
		case 3:
			deleteContent(userID);
			break;;
		case 4:
			modifyContent(userID);
			break;;
		case 5:
			cout << "Come again" << endl;
			exit(0);
			break;;
		default:
			cout << "Please enter a valid choice, 1, 2, 3, or 4." << endl;
			choiceLoop = true;
		}
	} while (choiceLoop == true);
}
int displayAdminOptions(int userID)
{
	int choice = -1;
	bool choiceLoop = false;

	do {
		cout << "1) View Content 2) Add Content 3) Delete Content\n4) Modify Content 5) Edit User Privileges 6) Exit Program" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			viewContent(userID);
			break;;
		case 2:
			addContent(userID);
			break;;
		case 3:
			deleteContent(userID);
			break;;
		case 4:
			modifyContent(userID);
			break;;
		case 5:
			//edit user permissions
			break;;
		case 6:
			cout << "Come again" << endl;
			exit(0);
			break;;
		default:
			cout << "Please enter a valid choice, 1, 2, 3, or 4." << endl;
			choiceLoop = true;
		}
	} while (choiceLoop == true);

}