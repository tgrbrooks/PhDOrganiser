// Source file for ErrorLog class
// Author: tbrooks

#include "ErrorLog.h"

// Default constructor - Set start and end as the same
ErrorLog::ErrorLog() : _solved(false) {
	Event::_type = "Error Log";
	// Gets the current time and sets this as the start and end time of the log
	time_t now = time(NULL);
	struct tm now_info;
	localtime_s(&now_info, &now);
	_start.set(now_info.tm_mday, now_info.tm_mon + 1, now_info.tm_year + 1900, now_info.tm_hour, now_info.tm_min);
	_end = _start;
	// When loading this will be overidden by the previous time
}

// Parameterised constructor
ErrorLog::ErrorLog(std::string namein, std::string projectin, std::string experimentin, bool solvedin) : Log(namein, "Error Log", projectin, experimentin), _solved(solvedin) {
	time_t now = time(NULL);
	struct tm now_info;
	localtime_s(&now_info, &now);
	_start.set(now_info.tm_mday, now_info.tm_mon + 1, now_info.tm_year + 1900, now_info.tm_hour, now_info.tm_min);
	_end = _start;
}

// Overridden save function - using overloaded >>
void ErrorLog::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void ErrorLog::print(){
	std::cout << *this;
}

void ErrorLog::setSolved(bool is_solved){
	_solved = is_solved;
}

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const ErrorLog &EL) {
	os << "---- Event::ErrorLog ----" << std::endl
		<< "Name: " << EL._name << std::endl << "Start: " << EL._start << std::endl << "End: " << EL._end << std::endl
		<< "Experiment: " << EL._experiment << std::endl << "Project: " << EL._project << std::endl
		<< "Solved?: " << std::boolalpha << EL._solved << std::endl
		<< "Log: " << EL._log.getName() << std::endl
		<< "-------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, ErrorLog &EL) {
	std::string ignore;
	std::string name, experiment, project, log;
	DateAndTime start, end;
	bool solved;
	getline(is, name); name.erase(0, 6);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, experiment); experiment.erase(0, 12);
	getline(is, project); project.erase(0, 9);
	is >> ignore >> std::boolalpha >> solved >> ignore >> log;
	ErrorLog temp(name, project, experiment, solved);
	temp.setStart(start); temp.setEnd(end); temp.setLog(log);
	EL = temp;
	return is;
}