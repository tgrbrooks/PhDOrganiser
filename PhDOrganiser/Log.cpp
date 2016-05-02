// Source file for Log class
// Author: tbrooks

#include "Log.h"

// Overridden create file function
void Log::createFile(std::string file_name) {
	bool overwrite_flag;
	std::string overwrite;
	// If a file already exists ask if user wants to overwrite
	if (_log.getName() != "none"){
		while (overwrite != "y" || overwrite != "n"){
			std::cout << "Log already exists, overwrite? (y/n) ";
			std::cin >> overwrite;
			std::cout << std::endl;
			if (overwrite == "n") overwrite_flag = 0;
			if (overwrite == "y") overwrite_flag = 1;
		}
		// If user wants to overwrite delete old file and create a new one
		if (overwrite_flag){
			_log.deleteFile();
			_log.createFile(file_name);
		}
	}
	else {
		_log.createFile(file_name);
	}
}

// Overridden delete file function
void Log::deleteFile() {
	if (_log.getName() == "none"){
		std::cout << "File doesn't exist, nothing to delete" << std::endl;
	}
	else {
		_log.deleteFile();
	}
}

// Accessors and mutators for project, experiment and log
std::string Log::getExperiment() const {
	return _experiment;
}
void Log::setExperiment(std::string experiment){
	_experiment = experiment;
}
std::string Log::getProject() const{
	return _project;
}
void Log::setProject(std::string project){
	_project = project;
}
TextFile Log::getFile() const{
	return _log;
}
void Log::setLog(string log){
	_log.setName(log);
}

// Not applicable functions to make searching easier
int Log::getNumber() const{ return -1; }
int Log::getNumAttendees() const{ return -1; }
std::string Log::getLocation() const{ return "null"; }
std::string Log::getField() const{ return "null"; }
std::string Log::getRole() const{ return "null"; }
std::string Log::getGroup() const{ return "null"; }
std::string Log::getLecturer() const{ return "null"; }
// Not applicable mutators for easier editing
void Log::setNumber(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setNumAttendees(int){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setLocation(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setField(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setRole(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setGroup(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }
void Log::setLecturer(std::string){ std::cout << "WARNING: Field does not exist" << std::endl; }