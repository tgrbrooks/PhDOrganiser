// Header file for Log class
// Author: tbrooks

#ifndef LOG_H
#define LOG_H

#include "Event.h"

// Abstract derived class for Log
class Log : public Event
{
protected:
	// Project and experiment the log is associated with
	std::string _project, _experiment;
	// The log itself
	TextFile _log;

public:
	// Default constructor
	Log();
	// Parameterised constructor
	Log(std::string namein, std::string typein, std::string projectin, std::string experimentin);
	// Virtual destructor
	virtual ~Log() {}

	// Overridden create file function
	void createFile(std::string file_name);
	// Overridden delete file function
	void deleteFile();

	// Accessors and mutators for project, experiment and log
	std::string getProject() const;
	void setProject(std::string project);
	std::string getExperiment() const;
	void setExperiment(std::string experiment);
	TextFile getFile() const;
	void setLog(std::string log);

	// Not applicable functions to make searching easier
	int getNumber() const;
	int getNumAttendees() const;
	std::string getLocation() const;
	std::string getField() const;
	std::string getRole()const;
	std::string getGroup() const;
	std::string getLecturer()const;

	// Not applicable mutators for easier editing
	void setNumber(int);
	void setNumAttendees(int);
	void setLocation(std::string);
	void setField(std::string);
	void setRole(std::string);
	void setGroup(std::string);
	void setLecturer(std::string);

};// End of Log class

#endif