#pragma once
#include "user.h"
#include <string>
using namespace std;

class logEntry
{
private:
	string date;
	string time;
	string user;
	string event;
public:
	logEntry(string date, string time, string user, string event)
	{
		this->date = date;
		this->time = time;
		this->user = user;
		this->event = event;
	}
	logEntry()
	{
		date = "";
		time = "";
		user = "";
		event = "";
	}

	string getDate() { return date; }
	string getTime() { return time; }
	string getUser() { return user; }
	string getEvent() { return event; }

	string setDate(string date) { this->date = date; return date; }
	string setTime(string time) { this->time = time; return time; }
	string setUser(string user) { this->user = user; return user; }
	string setEvent(string event) { this->event = event; return event; }


};

