// Header file for ErrorLog class
// Author: tbrooks

#ifndef ERRORLOG_H
#define ERRORLOG_H

#include "Log.h"

// Derived class for ErrorLog
class ErrorLog : public Log
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const ErrorLog &EL);
	friend istream & operator>>(istream &is, ErrorLog &EL);

protected:
	// True if error fixed, false if not
	bool _solved;

public:
	// Default constructor - Set start and end as the same
	ErrorLog();
	// Parameterised constructor
	ErrorLog(std::string namein, std::string projectin, std::string experimentin, bool solvedin);
	// Destructor
	~ErrorLog(){}

	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();
	void setSolved(bool is_solved);

};// End of ErrorLog class


#endif