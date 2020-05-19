// Source file for Lecture class
// Author: tbrooks

#include "Lecture.h"

// Default constructor
Lecture::Lecture() : _location("unknown"), _lecturer("unknown"), _number(0) { Event::_type = "Lecture"; }

// Parameterised constructor
Lecture::Lecture(std::string namein, std::string locationin, std::string lecturerin, int numberin) : Event(namein, "Lecture"), _location(locationin), _lecturer(lecturerin), _number(numberin) {}

// Overridden create file function
void Lecture::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_notes.getName() != "none"){
		while (overwrite != "y" && overwrite != "n"){
			std::cout << "Notes for this lecture already exist, overwrite? (y/n) ";
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
void Lecture::deleteFile() {
	if (_notes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_notes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Lecture::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Lecture::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Lecture::getLocation() const {
	return _location;
}
void Lecture::setLocation(std::string location) {
	_location = location;
}
std::string Lecture::getLecturer() const {
	return _lecturer;
}
void Lecture::setLecturer(std::string lecturer){
	_lecturer = lecturer;
}
int Lecture::getNumber() const{
	return _number;
}
void Lecture::setNumber(int number){
	_number = number;
}
TextFile Lecture::getFile() const{
	return _notes;
}
void Lecture::setNotes(string notes){
	_notes.setName(notes);
}

// Not applicable functions to make searching easier
int Lecture::getNumAttendees() const{ return -1; }
std::string Lecture::getField() const{ return "null"; }
std::string Lecture::getExperiment() const{ return "null"; }
std::string Lecture::getProject() const{ return "null"; }
std::string Lecture::getRole() const{ return "null"; }
std::string Lecture::getGroup() const{ return "null"; }
// Not applicable mutators for easier editing
void Lecture::setNumAttendees(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setField(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setExperiment(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setProject(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setRole(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setGroup(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Lecture::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Lecture &L) {
	os << "---- Event::Lecture ----" << std::endl
		<< "Name: " << L._name << std::endl << "Location: " << L._location << std::endl
		<< "Start: " << L._start << std::endl << "End: " << L._end << std::endl
		<< "Lecturer: " << L._lecturer << std::endl << "Lecture number: " << L._number << std::endl
		<< "Notes: " << L._notes.getName() << std::endl
		<< "------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Lecture &L) {
	std::string ignore;
	std::string name, location, lecturer, notes;
	DateAndTime start, end;
	int number;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	getline(is, name); name.erase(0, 6);
	getline(is, location); location.erase(0, 10);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, lecturer); lecturer.erase(0, 10);
	is >> ignore >> ignore >> number >> ignore >> notes;
	Lecture temp(name, location, lecturer, number);
	temp.setStart(start); temp.setEnd(end); temp.setNotes(notes);
	L = temp;
	return is;
}