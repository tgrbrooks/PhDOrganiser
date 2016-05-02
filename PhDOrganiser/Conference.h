// Header file for Conference class
// Author: tbrooks

#ifndef CONFERENCE_H
#define CONFERENCE_H

#include"Event.h"

// Derived class for Conference
class Conference : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Conference &C);
	friend istream & operator>>(istream &is, Conference &C);

protected:
	// Location and field of conference and your role (e.g. Talk, Poster, Attendee)
	std::string _location, _field, _role;
	// Any notes made - should be some container of notes to allow multiple
	TextFile _notes;

public:
	// Default constructor
	Conference() : _location("unknown"), _field("unknown"), _role("unknown") { Event::_type = "Conference"; }
	// Parameterised constructor
	Conference(std::string namein, std::string locationin, std::string fieldin, std::string rolein) : Event(namein, "Conference"), _location(locationin), _field(fieldin), _role(rolein) {}
	// Destructor
	~Conference(){}
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
	std::string getField() const;
	void setField(std::string field);
	std::string getRole() const;
	void setRole(std::string role);
	TextFile getFile() const;
	void setNotes(std::string notes);

	// Not applicable functions to make searching easier
	int getNumber() const;
	int getNumAttendees() const;
	std::string getExperiment() const;
	std::string getProject() const;
	std::string getGroup() const;
	std::string getLecturer() const;
	// Not applicable mutators for easier editing
	void setNumber(int);
	void setNumAttendees(int);
	void setExperiment(std::string);
	void setProject(std::string);
	void setGroup(std::string);
	void setLecturer(std::string);
	void setSolved(bool);

};// End of Conference class

#endif