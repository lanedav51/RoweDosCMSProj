#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
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
}
bool downloadReport()
{
	//allows admin to download the xlsx file? kind of like content that only admins can access, no owner
	return false;
}