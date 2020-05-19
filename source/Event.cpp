// Source file for Event class and all derived classes
// Author: tbrooks

#include "Event.h"

// Function to return time until event in seconds
double Event::timeToEvent() {
	return _start.timeUntil();
}

// Function to display the time until event
void Event::printTimeToEvent() {
	int input_seconds = (int)_start.timeUntil();
	int days = abs(input_seconds) / 60 / 60 / 24;
	double hours = (abs(input_seconds) / 60 / 60) % 24;
	int minutes = (abs(input_seconds) / 60) % 60;
	int seconds = abs(input_seconds) % 60;
	if (input_seconds > 0) {
		cout << "The time until this " << _type
			<< " is " << days << " days " << hours << " hours " << minutes << " minutes and " << seconds << " seconds" << endl;
	}
	else{
		cout << "This " << _type << " was " << days << " days " << hours << " hours " << minutes << " minutes and " << seconds << " seconds ago" << endl;
	}
}

// Function to return the duration of the event in seconds
double Event::getDuration() {
	return _start.timeBetween(_end);
}

// Function to display the duration of the event
void Event::printDuration() {
	int input_seconds = (int)_start.timeBetween(_end);
	int days = abs(input_seconds) / 60 / 60 / 24;
	double hours = (abs(input_seconds) / 60 / 60) % 24;
	int minutes = (abs(input_seconds) / 60) % 60;
	int seconds = abs(input_seconds) % 60;
	cout << "This " << _type << " is " << days << " days " << hours << " hours " << minutes << " minutes and " << seconds << " seconds long" << endl;
}

// Accessor and mutator functions for data members
int Event::getId() const {
	return _id;
}
std::string Event::getName() const {
	return _name;
}
void Event::setName(std::string namein) {
	_name = namein;
}
std::string Event::getType() const {
	return _type;
}
DateAndTime Event::getStart() const {
	return _start;
}
void Event::setStart(DateAndTime startin) {
	_start = startin;
}
DateAndTime Event::getEnd() const {
	return _end;
}
void Event::setEnd(DateAndTime endin) {
	// Check that the end is sensible
	if (endin.timeBetween(_start) > 0){
		cout << "WARNING: The event cannot end before it has begun" << endl;
	}
	else {
		_end = endin;
	}
}