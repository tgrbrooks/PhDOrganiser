// Source file for Conference class
// Author: tbrooks

#include "Conference.h"

// Default constructor
Conference::Conference() : _location("unknown"), _field("unknown"), _role("unknown") { Event::_type = "Conference"; }

// Parameterised constructor
Conference::Conference(std::string namein, std::string locationin, std::string fieldin, std::string rolein) : Event(namein, "Conference"), _location(locationin), _field(fieldin), _role(rolein) {}

// Overridden create file function
void Conference::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;

	// If a file already exists ask if user wants to overwrite
	if (_notes.getName() != "none"){
		while (overwrite != "y" && overwrite != "n"){
			std::cout << "Notes for this conference already exist, overwrite? (y/n) ";
			std::cin >> overwrite;
			if (overwrite == "n") overwrite_flag = 0;
			if (overwrite == "y") overwrite_flag = 1;
		}

		// If user wants to overwrite delete old file and create a new one
		if (overwrite_flag){
			_notes.deleteFile();
			_notes.createFile(file_name);
		}
	}

	else {
		_notes.createFile(file_name);
	}
}

// Overridden delete file function
void Conference::deleteFile() {
	if (_notes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_notes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Conference::save(std::string file_name){
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Conference::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Conference::getLocation() const {
	return _location;
}
void Conference::setLocation(std::string location) {
	_location = location;
}
std::string Conference::getField() const {
	return _field;
}
void Conference::setField(std::string field){
	_field = field;
}
std::string Conference::getRole() const{
	return _role;
}
void Conference::setRole(std::string role){
	_role = role;
}
TextFile Conference::getFile() const{
	return _notes;
}
void Conference::setNotes(string notes){
	_notes.setName(notes);
}

// Not applicable functions to make searching easier
int Conference::getNumber() const{ return -1; }
int Conference::getNumAttendees() const{ return -1; }
std::string Conference::getExperiment() const{ return "null"; }
std::string Conference::getProject() const{ return "null"; }
std::string Conference::getGroup() const{ return "null"; }
std::string Conference::getLecturer() const{ return "null"; }

// Not applicable mutators for easier editing
void Conference::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setNumAttendees(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setExperiment(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setProject(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setGroup(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setLecturer(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Conference::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Conference &C) {
	os << "---- Event::Conference ----" << std::endl
		<< "Name: " << C._name << std::endl << "Location: " << C._location << std::endl
		<< "Start: " << C._start << std::endl << "End: " << C._end << std::endl
		<< "Field: " << C._field << std::endl << "Role: " << C._role << std::endl
		<< "Notes: " << C._notes.getName() << std::endl
		<< "--------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Conference &C) {
	std::string ignore;
	std::string name, location, field, role, notes;
	DateAndTime start, end;

	// Input matches << operator apart from the first and last lines - dealt with in load function
	getline(is, name); name.erase(0, 6);
	getline(is, location); location.erase(0, 10);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, field); field.erase(0, 7);
	getline(is, role); role.erase(0, 6);
	is >> ignore >> notes;

	// Create a temporary conference
	Conference temp(name, location, field, role);
	temp.setStart(start); temp.setEnd(end); temp.setNotes(notes);
	C = temp;
	return is;
}