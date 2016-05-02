// Source file for WeeklyLog class
// Author: tbrooks

#include "WeeklyLog.h"

// Default constructor - Set start and end automatically
WeeklyLog::WeeklyLog(){
	Event::_type = "Weekly Log";
	// Get the time on creation and set as the start date
	time_t now = time(NULL);
	// Add a week and set as the end date
	time_t next_week = now + 7 * 24 * 60 * 60;
	struct tm now_info;
	struct tm next_week_info;
	localtime_s(&now_info, &now);
	localtime_s(&next_week_info, &next_week);
	_start.set(now_info.tm_mday, now_info.tm_mon + 1, now_info.tm_year + 1900, now_info.tm_hour, now_info.tm_min);
	_end.set(next_week_info.tm_mday, next_week_info.tm_mon + 1, next_week_info.tm_year + 1900, next_week_info.tm_hour, next_week_info.tm_min);
	// When loaded this will be overidden
}

// Parameterised constructor
WeeklyLog::WeeklyLog(std::string namein, std::string projectin, std::string experimentin) : Log(namein, "Weekly Log", projectin, experimentin) {
	time_t now = time(NULL);
	time_t next_week = now + 7 * 24 * 60 * 60;
	struct tm now_info;
	struct tm next_week_info;
	localtime_s(&now_info, &now);
	localtime_s(&next_week_info, &next_week);
	_start.set(now_info.tm_mday, now_info.tm_mon + 1, now_info.tm_year + 1900, now_info.tm_hour, now_info.tm_min);
	_end.set(next_week_info.tm_mday, next_week_info.tm_mon + 1, next_week_info.tm_year + 1900, next_week_info.tm_hour, next_week_info.tm_min);
}

// Overridden save function - using overloaded >>
void WeeklyLog::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void WeeklyLog::print(){
	std::cout << *this;
}

void WeeklyLog::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const WeeklyLog &WL) {
	os << "---- Event::WeeklyLog ----" << std::endl
		<< "Name: " << WL._name << " Start: " << WL._start << " End: " << WL._end << std::endl
		<< "Experiment: " << WL._experiment << " Project: " << WL._project << std::endl
		<< "Log: " << WL._log.getName() << std::endl
		<< "--------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, WeeklyLog &WL) {
	std::string ignore;
	std::string name, experiment, project, log;
	DateAndTime start, end;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	is >> ignore >> name >> ignore >> start >> ignore >> end
		>> ignore >> experiment >> ignore >> project
		>> ignore >> log;
	WeeklyLog temp(name, project, experiment);
	temp.setStart(start); temp.setEnd(end); temp.setLog(log);
	WL = temp;
	return is;
}