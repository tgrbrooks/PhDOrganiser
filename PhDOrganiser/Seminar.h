// Header file for Seminar class
// Author: tbrooks

#ifndef SEMINAR_H
#define SEMINAR_H

#include "Event.h"

// Derived class for Seminar
class Seminar : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Seminar &S);
	friend istream & operator>>(istream &is, Seminar &S);

protected:
	// Location of the seminar and the experiment it is on (e.g. SBND)
	std::string _location, _experiment;
	// Any notes made - should be some container of notes to allow multiple
	TextFile _notes;

public:
	// Default constructor
	Seminar() : _location("unknown"), _experiment("unknown") { Event::_type = "Seminar"; }
	// Parameterised constructor
	Seminar(std::string namein, std::string locationin, std::string experimentin) : Event(namein, "Seminar"), _location(locationin), _experiment(experimentin) {}
	// Destructor - clean up container of notes
	~Seminar(){}
	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();
	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();
	// Accessors and mutators for location, experiment and notes
	std::string getLocation() const;
	void setLocation(std::string location);
	std::string getExperiment() const;
	void setExperiment(std::string experiment);
	TextFile getFile() const;
	void setNotes(std::string notes);

	// Not applicable functions to make searching easier
	int getNumber() const;
	int getNumAttendees() const;
	std::string getField() const;
	std::string getProject() const;
	std::string getRole() const;
	std::string getGroup() const;
	std::string getLecturer() const;
	// Not applicable mutators for easier editing
	void setNumber(int);
	void setNumAttendees(int);
	void setField(std::string);
	void setProject(std::string);
	void setRole(std::string);
	void setGroup(std::string);
	void setLecturer(std::string);
	void setSolved(bool);

};// End of Seminar class

#endif