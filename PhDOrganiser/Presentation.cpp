// Source file for Presentation class
// Author: tbrooks

#include "Presentation.h"

// Default constructor
Presentation::Presentation() : _location("unknown"), _role("unknown"), _project("unknown"), _experiment("unknown") { Event::_type = "Presentation"; }

// Parameterised constructor
Presentation::Presentation(std::string namein, std::string locationin, std::string rolein, std::string projectin, std::string experimentin) : Event(namein, "Presentation"), _location(locationin), _role(rolein), _project(projectin), _experiment(experimentin) {}

// Overridden create file function
void Presentation::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_notes.getName() != "none"){
		while (overwrite != "y" && overwrite != "n"){
			std::cout << "Notes for this presentation already exist, overwrite? (y/n) ";
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
void Presentation::deleteFile() {
	if (_notes.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_notes.deleteFile();
	}
}

// Overridden save function - using overloaded >>
void Presentation::save(std::string file_name) {
	// Check if file already exists, if it does write to the end of it
	ofstream saveFile;
	saveFile.open(file_name.c_str(), std::ios::app);
	saveFile << *this;
	saveFile.close();
}

void Presentation::print(){
	std::cout << *this;
}

// Accessors and mutators for location, project, number of attendees and minutes
std::string Presentation::getLocation() const {
	return _location;
}
void Presentation::setLocation(std::string location) {
	_location = location;
}
std::string Presentation::getExperiment() const {
	return _experiment;
}
void Presentation::setExperiment(std::string experiment){
	_experiment = experiment;
}
std::string Presentation::getRole() const{
	return _role;
}
void Presentation::setRole(std::string role){
	_role = role;
}
std::string Presentation::getProject() const{
	return _project;
}
void Presentation::setProject(std::string project){
	_project = project;
}
TextFile Presentation::getFile() const{
	return _notes;
}
void Presentation::setNotes(string notes){
	_notes.setName(notes);
}

// Not applicable functions to make searching easier
int Presentation::getNumber() const{ return -1; }
int Presentation::getNumAttendees() const{ return -1; }
std::string Presentation::getField() const{ return "null"; }
std::string Presentation::getGroup() const{ return "null"; }
std::string Presentation::getLecturer() const{ return "null"; }
// Not applicable mutators for easier editing
void Presentation::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Presentation::setNumAttendees(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Presentation::setField(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Presentation::setGroup(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Presentation::setLecturer(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Presentation::setSolved(bool){ std::cout << "WARNING: Field does not exist" << std::endl; }

// Output stream friend function for saving state
ostream & operator<<(ostream &os, const Presentation &P) {
	os << "---- Event::Presentation ----" << std::endl
		<< "Name: " << P._name << std::endl << "Location: " << P._location << std::endl
		<< "Start: " << P._start << std::endl << "End: " << P._end << std::endl
		<< "Experiment: " << P._experiment << std::endl << "Project: " << P._project << std::endl
		<< "Role: " << P._role << std::endl << "Notes: " << P._notes.getName() << std::endl
		<< "-----------------------------" << std::endl;
	return os;
}

// Input stream friend function for loading state - not used for user input
istream & operator>>(istream &is, Presentation &P) {
	std::string ignore;
	std::string name, location, experiment, project, role, notes;
	DateAndTime start, end;
	// Input matches << operator apart from the first and last lines - dealt with in load function
	getline(is, name); name.erase(0, 6);
	getline(is, location); location.erase(0, 10);
	is >> ignore >> start >> ignore >> end;
	getline(is, ignore);
	getline(is, experiment); experiment.erase(0, 12);
	getline(is, project); project.erase(0, 9);
	getline(is, role); role.erase(0, 6);
	is >> ignore >> notes;
	Presentation temp(name, location, experiment, project, role);
	temp.setStart(start); temp.setEnd(end); temp.setNotes(notes);
	P = temp;
	return is;
}