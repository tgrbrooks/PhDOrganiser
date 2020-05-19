// Header file for Lecture class
// Author: tbrooks

#ifndef Lecture_H
#define Lecture_H

#include "Event.h"

// Derived class for Lecture
class Lecture : public Event
{
	// Friend functions for overloading >> and <<
	friend ostream & operator<<(ostream &os, const Lecture &L);
	friend istream & operator>>(istream &is, Lecture &L);

protected:
	// Location of lecture, name of lecturer. Subject will be the name of the event
	std::string _location, _lecturer;
	// Lecture number - should be unique when combined with name - ADD CHECKS
	int _number;
	// Container for notes
	TextFile _notes;

public:
	// Default constructor
	Lecture();
	// Parameterised constructor
	Lecture(std::string namein, std::string locationin, std::string lecturerin, int numberin);
	// Destructor - clean up container of notes
	~Lecture(){}

	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();
	// Overridden save function - using overloaded >>
	void save(std::string file_name);
	void print();

	// Accessors and mutators for location, lecturer, number and notes
	std::string getLocation() const;
	void setLocation(std::string location);
	std::string getLecturer() const;
	void setLecturer(std::string lecturer);
	int getNumber() const;
	void setNumber(int number);
	TextFile getFile() const;
	void setNotes(std::string notes);

	// Not applicable functions to make searching easier
	int getNumAttendees() const;
	std::string getField() const;
	std::string getExperiment() const;
	std::string getProject() const;
	std::string getRole() const;
	std::string getGroup() const;

	// Not applicable mutators for easier editing
	void setNumAttendees(int);
	void setField(std::string);
	void setExperiment(std::string);
	void setProject(std::string);
	void setRole(std::string);
	void setGroup(std::string);
	void setSolved(bool);

};// End of Lecture class

#endif