// Header file for Presentation class
// Author: tbrooks

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "Event.h"

// Derived class for Presentation
class Presentation : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Presentation &P);
	friend istream & operator>>(istream &is, Presentation &P);

protected:
	// Location of presentation, role (Poster, Talk, Both), associated experiment and  specific project
	std::string _location, _role, _project, _experiment;
	// Container for notes
	TextFile _notes;

public:
	// Default constructor
	Presentation() : _location("unknown"), _role("unknown"), _project("unknown"), _experiment("unknown") { Event::_type = "Presentation"; }
	// Parameterised constructor
	Presentation(std::string namein, std::string locationin, std::string rolein, std::string projectin, std::string experimentin) : Event(namein, "Presentation"), _location(locationin), _role(rolein), _project(projectin), _experiment(experimentin) {}
	// Destructor - clean up container of notes
	~Presentation(){}
	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();
	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();
	// Accessors and mutators for location, field, role and notes
	std::string getLocation() const;
	void setLocation(std::string location);
	std::string getRole() const;
	void setRole(std::string role);
	std::string getProject() const;
	void setProject(std::string project);
	std::string getExperiment() const;
	void setExperiment(std::string experiment);
	TextFile getFile() const;
	void setNotes(std::string notes);

	// Not applicable functions to make searching easier
	int getNumber() const;
	int getNumAttendees() const;
	std::string getField() const;
	std::string getGroup() const;
	std::string getLecturer() const;
	// Not applicable mutators for easier editing
	void setNumber(int);
	void setNumAttendees(int);
	void setField(std::string);
	void setGroup(std::string);
	void setLecturer(std::string);
	void setSolved(bool);

};// End of Presentation class

#endif