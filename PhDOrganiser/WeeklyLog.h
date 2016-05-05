// Header file for WeeklyLog class
// Author: tbrooks

#ifndef WEEKLYLOG_H
#define WEEKLYLOG_H

#include "Log.h"

// Derived class for WeeklyLog
class WeeklyLog : public Log
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const WeeklyLog &WL);
	friend istream & operator>>(istream &is, WeeklyLog &WL);

public:
	// Default constructor - Set start and end automatically
	WeeklyLog();
	WeeklyLog(std::string namein, std::string projectin, std::string experimentin);
	// Destructor
	~WeeklyLog(){}

	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();

	void setSolved(bool);

};// End of WeeklyLog class

#endif