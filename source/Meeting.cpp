// Source file for Meeting class
// Author: tbrooks

#include "Meeting.h"

// Default constructor
Meeting::Meeting() : _location("unknown"), _group("unknown"), _experiment("unknown"), _num_attendees(0) { Event::_type = "Meeting"; }

// Parameterised constructor
Meeting::Meeting(std::string namein, std::string locationin, std::string experimentin, std::string groupin, int attendeesin) : Event(namein, "Meeting"), _location(locationin), _group(groupin), _experiment(experimentin), _num_attendees(attendeesin) {}

// Overridden create file function
void Meeting::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_minutes.getName() != "none"){
		while (overwrite != "y" || overwrite != "n"){
			std::cout << "Minutes for this meeting already exist, overwrite? (y/n) ";
			std::cin >> overwrite;
			std::cout << std::endl;
			if (overwrite == "n") overwrite_flag = 0;
			if (overwrite == "y") overwrite_flag = 1;
		}
		// If user wants to overwrite delete old file and create a new one
		if (overwrite_flag){
			_minutes.deleteFile();
			_minutes.createFile(file_name);
		}
	}
	else {
		_minutes.createFile(file_name);
	}
}

// Overridden delete file function
void Meeting::deleteFile() {
	if (_minutes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_minutes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Meeting::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(),std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Meeting::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Meeting::getLocation() const {
	return _location;
}
void Meeting::setLocation(std::string location) {
	_location = location;
}
std::string Meeting::getGroup() const {
	return _group;
}
void Meeting::setGroup(std::string group){
	_group = group;
}
std::string Meeting::getExperiment() const{
	return _experiment;
}
void Meeting::setExperiment(std::string experiment){
	_experiment = experiment;
}
int Meeting::getNumAttendees() const{
	return _num_attendees;
}
void Meeting::setNumAttendees(int num_attendees){
	_num_attendees = num_attendees;
}
TextFile Meeting::getFile() const{
	return _minutes;
}
void Meeting::setMinutes(string minutes){
	_minutes.setName(minutes);
}

// Not applicable functions to make searching easier
int Meeting::getNumber() const{ return -1; }
std::string Meeting::getField() const{ return "null"; }
std::string Meeting::getProject() const{ return "null"; }
std::string Meeting::getRole() const{ return "null"; }
std::string Meeting::getLecturer() const{ return "null"; }
// Not applicable mutators for easier editing
void Meeting::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setField(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setProject(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setRole(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setLecturer(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Meeting::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Meeting &M) {
	os << "---- Event::Meeting ----" << std::endl
		<< "Name: " << M._name << std::endl << "Location: " << M._location << std::endl
		<< "Start: " << M._start << std::endl << "End: " << M._end << std::endl
		<< "Experiment: " << M._experiment << std::endl << "Group: " << M._group << std::endl
		<< "Number of Attendees: " << M._num_attendees << std::endl
		<< "Minutes: " << M._minutes.getName() << std::endl
		<< "------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Meeting &M) {
	std::string ignore;
	std::string name, location, experiment, group, minutes;
	DateAndTime start, end;
	int num_attendees;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	getline(is, name); name.erase(0, 6);
	getline(is, location); location.erase(0, 10);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, experiment); experiment.erase(0, 12);
	getline(is, group); group.erase(0, 7);
	is >> ignore >> ignore >> ignore >> num_attendees >> ignore >> minutes;
	Meeting temp(name, location, experiment, group, num_attendees);
	temp.setStart(start); temp.setEnd(end); temp.setMinutes(minutes);
	M = temp;
	return is;
}
