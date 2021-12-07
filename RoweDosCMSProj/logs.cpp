#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include "logs.h"
#include "time.h"
using namespace std;

bool logEvent(string username, string logDesc)
{
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	//logs an event that happens, giving user information, time, and action
	int year = 1900 + newtime.tm_year;
	int month = 1 + newtime.tm_mon;
	int day = newtime.tm_mday;
	int hour = newtime.tm_hour;
	int min = newtime.tm_min;
	int sec = newtime.tm_sec;

	string date = to_string(year) + "/" + to_string(month) + "/" + to_string(day);
	string time = to_string(hour) + ":" + to_string(min) + ":" + to_string(sec);



	logEntry log(date,time, username, logDesc);

	ofstream logFile;
	logFile.open("logFile.csv", ios::app);
	logFile << log.getDate() << "," << log.getTime() << "," << log.getUser() << "," << log.getEvent() << ",\n";
	logFile.close();
	
	return true;
}

bool logFileExist()
{
	fstream fileStream("logFile.csv");
	if (fileStream.fail())
	{
		return false;
	}
	return true;
}

bool createLogCsv()
{
	fstream logFile;
	logFile.open("logFile.csv", fstream::out);
	logFile << "DATE," << "TIME," << "USER," << "EVENT," << "\n";
	logFile.close();
	cout << "Log CSV Created" << endl;
	return true;
}

void printReport()
{
	//prints out the last 100 log entries from xlsx sheet
	cout << "LOG FILE\n_________________________________________\nNAME          FILESIZE         FILE LOCATION\n___________________________________________________\n";
	//For each line, if userID is equal to ownerID, print out the other 3
	vector<string> dates, times, users, events;
	fstream logFile("logFile.csv");
	vector<string> fileVal; //vector of all values comma delimited
	int columnNum = 0;
	int val, i;
	string line, value;

	while (getline(logFile, line))
	{
		size_t begin, end = 0;
		string delim = ",";
		while ((end = line.find(delim)) != string::npos)
		{
			fileVal.push_back(line.substr(0, end));
			line.erase(0, end + delim.length());
		}
	}

	for (i = 0; i < fileVal.size(); i += 4)
	{
		dates.push_back(fileVal[i]);
		times.push_back(fileVal[i+1]);
		users.push_back(fileVal[i+2]);
		events.push_back(fileVal[i+3]);
	}

	logFile.close();

	//cout << fileOwners.size();
	for (i = 0; i < dates.size(); i++)
	{
		cout << dates[i] << " : " << times[i] << " : " << users[i] << " : " << events[i] << endl;
	}
}

