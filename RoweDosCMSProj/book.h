#pragma once
#include <string>
using namespace std;

class book
{
public:
	book(string bookID, string title, string author, string user, string date)
	{
		this->bookID = bookID;
		this->title = title;
		this->author = author;
		this->user = user;
		this->date = date;
	}

	book
()
	{
		bookID = "";
		title = "";
		author = "";
		user = "";
		date = "";
	}

	string getBookID() { return bookID; }
	string getTitle() { return title; }
	string getAuthor() { return author; }
	string getUser() { return user; }
	string getDate() { return date; }

	bool setBookID(string bookID) { this->bookID = bookID; return true; }
	bool setTitle(string title) { this->title = title; return true; }
	bool setAuthor(string author) { this->author = author; return true; }
	bool setUser(string user) { this->user = user; return true; }
	bool setDate(string date) { this->date = date; return true; }

private:
	string bookID;
	string title;
	string author;
	string user;
	string date;
};