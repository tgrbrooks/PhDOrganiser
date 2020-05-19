// Header file for Event class and all derived classes
// Author: tbrooks

#ifndef EVENT_H
#define EVENT_H

#include<string>
#include "DateAndTime.h"
#include "TextFile.h"

// Abstract base class for event
class Event
{
protected:
	// Unique identifier for event, use random number to set in constructor
	int _id;
	static int num_events;
	// Name and type of the event
	std::string _name, _type;
	// Start and end times/dates of event
	DateAndTime _start, _end;

public:
	// Default constructor
	Event() :_name("none"){ _id = num_events; num_events++; }
	// Parameterised constructor
	Event(std::string namein, std::string typein){ _name = namein; _type = typein; _id = num_events; num_events++; }
	// Virtual destructor
	virtual ~Event(){}

	// Virtual create file function
	virtual void createFile(std::string file_name) = 0;
	// Virtual delete file
	virtual void deleteFile() = 0;
	// Virtual get file function
	virtual TextFile getFile() const = 0;
	// Virtual save function
	virtual void save(std::string file_name) = 0;
	virtual void print() = 0;

	// Virtual accessors for easy looping through classes
	virtual int getNumber() const = 0;
	virtual int getNumAttendees() const = 0;
	virtual std::string getLocation() const = 0;
	virtual std::string getField() const = 0;
	virtual std::string getExperiment() const = 0;
	virtual std::string getProject() const = 0;
	virtual std::string getRole() const = 0;
	virtual std::string getGroup() const = 0;
	virtual std::string getLecturer() const = 0;

	// Virtual mutators for easier editing
	virtual void setNumber(int) = 0;
	virtual void setNumAttendees(int) = 0;
	virtual void setLocation(std::string) = 0;
	virtual void setField(std::string) = 0;
	virtual void setExperiment(std::string) = 0;
	virtual void setProject(std::string) = 0;
	virtual void setRole(std::string) = 0;
	virtual void setGroup(std::string) = 0;
	virtual void setLecturer(std::string) = 0;
	virtual void setSolved(bool) = 0;

	// Real function for time until event function
	double timeToEvent();
	void printTimeToEvent();
	double getDuration();
	void printDuration();

	// Real accessor and mutator functions for ID, name and start/end times
	int getId() const;
	std::string getName() const;
	void setName(std::string namein);
	std::string getType() const;
	DateAndTime getStart() const;
	void setStart(DateAndTime startin);
	DateAndTime getEnd() const;
	void setEnd(DateAndTime endin);

};// End of Event class

#endif