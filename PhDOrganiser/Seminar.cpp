// Source file for Seminar class
// Author: tbrooks

#include "Seminar.h"

// Overridden create file function
void Seminar::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_notes.getName() != "none"){
		while (overwrite != "y" && overwrite != "n"){
			std::cout << "Notes for this seminar already exist, overwrite? (y/n) ";
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
void Seminar::deleteFile() {
	if (_notes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_notes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Seminar::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Seminar::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Seminar::getLocation() const {
	return _location;
}
void Seminar::setLocation(std::string location) {
	_location = location;
}
std::string Seminar::getExperiment() const {
	return _experiment;
}
void Seminar::setExperiment(std::string experiment){
	_experiment = experiment;
}
TextFile Seminar::getFile() const{
	return _notes;
}
void Seminar::setNotes(string notes){
	_notes.setName(notes);
}

// Not applicable functions to make searching easier
int Seminar::getNumber() const{ return -1; }
int Seminar::getNumAttendees() const{ return -1; }
std::string Seminar::getField() const{ return "null"; }
std::string Seminar::getProject() const{ return "null"; }
std::string Seminar::getRole() const{ return "null"; }
std::string Seminar::getGroup() const{ return "null"; }
std::string Seminar::getLecturer() const{ return "null"; }
void Seminar::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setNumAttendees(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setField(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setProject(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setRole(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setGroup(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setLecturer(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Seminar::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Seminar &S) {
	os << "---- Event::Seminar ----" << std::endl
		<< "Name: " << S._name << " Location: " << S._location << " Start: " << S._start << " End: " << S._end << std::endl
		<< "Experiment: " << S._experiment << std::endl
		<< "Notes: " << S._notes.getName() << std::endl
		<< "------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Seminar &S) {
	std::string ignore;
	std::string name, location, experiment, notes;
	DateAndTime start, end;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	is >> ignore >> name >> ignore >> location >> ignore >> start >> ignore >> end
		>> ignore >> experiment 
		>> ignore >> notes;
	Seminar temp(name, location, experiment);
	temp.setStart(start); temp.setEnd(end); temp.setNotes(notes);
	S = temp;
	return is;
}