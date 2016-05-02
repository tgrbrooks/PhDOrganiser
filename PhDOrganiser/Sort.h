// Header file for Sort class
// Author: tbrooks

#ifndef SORT_H
#define SORT_H

#include "Organise.h"

// Derived class for sorting
class Sort : public Organise
{
protected:
	// Container of sorted results - can just be a vector
	std::vector<std::pair<std::shared_ptr<Event>,std::string>> _sorted_events;

public:
	// Default constructor
	Sort(){}
	// Parameterised constructor - pass unordered map of events - call base class constructor
	Sort(std::unordered_map<int, std::shared_ptr<Event>> eventsin) : Organise(eventsin) {} // Fill sorted events
	// Destructor - clean up the unordered map
	~Sort(){}
	// Copy constructor and copy assignment declaration
	Sort(Sort&);
	Sort& operator=(Sort&);
	// Move constructor and move assignment declaration
	Sort(Sort&&);
	Sort& operator=(Sort&&);
	// Overridden print results function - show id event type and name and sorted value - Template?
	void printResults() const;
	// Functions to sort events by name, type (string) or ID (integer)
	void sortName(bool ascending);
	void sortType(bool ascending);
	void sortId(bool ascending);
	// Functions to sort by start/end time and duration
	void sortStart(bool ascending);
	void sortEnd(bool ascending);
	// Accessor function for container of sorted results
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> getSortedEvents();

};// End of Sort class


#endif