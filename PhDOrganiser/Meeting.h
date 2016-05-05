// Header file for Meeting class
// Author: tbrooks

#ifndef MEETING_H
#define MEETING_H

#include"Event.h"

// Derived class for Meeting
class Meeting : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Meeting &M);
	friend istream & operator>>(istream &is, Meeting &M);

protected:
	// Location of meeting, the experiment and group it is associated with
	std::string _location, _group, _experiment;
	// Number of attendees
	int _num_attendees;
	// Minutes for the meeting
	TextFile _minutes;

public:
	// Default constructor
	Meeting();
	// Parameterised constructor
	Meeting(std::string namein, std::string locationin, std::string experimentin, std::string groupin, int attendeesin);
	// Destructor
	~Meeting(){}

	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();
	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();

	// Accessors and mutators for location, project, number of attendees and minutes
	std::string getLocation() const;
	void setLocation(std::string location);
	std::string getGroup() const;
	void setGroup(std::string group);
	std::string getExperiment() const;
	void setExperiment(std::string experiment);
	int getNumAttendees() const;
	void setNumAttendees(int num_attendees);
	TextFile getFile() const;
	void setMinutes(string minutes);

	// Not applicable functions to make searching easier
	int getNumber() const;
	std::string getField() const;
	std::string getProject() const;
	std::string getRole() const;
	std::string getLecturer() const;

	// Not applicable mutators for easier editing
	void setNumber(int);
	void setField(std::string);
	void setProject(std::string);
	void setRole(std::string);
	void setLecturer(std::string);
	void setSolved(bool);


};// End of Meeting class

#endif