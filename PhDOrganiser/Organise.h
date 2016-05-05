// Header file for Organise class and all derived classes
// Author: tbrooks

// Need to look at best way to use templates here
// If it takes containers or containers of containers is it possible to use recursion to loop through the actual events?
// Should there be a member function to search through the files or containers of files 

#ifndef ORGANISE_H
#define ORGANISE_H

#include<unordered_map>
#include<algorithm>
#include<memory>
#include<type_traits>
#include "Event.h"

// Abstract organiser base class
class Organise
{
protected:
	// Container of events - have a unordered_map of events here id and event
	std::unordered_map<int, std::shared_ptr<Event>> _events;

public:
	// Default constructor
	Organise() {}
	// Parameterised constructor - pass an unordered map of events
	Organise(std::unordered_map<int, std::shared_ptr<Event>> eventsin) : _events(eventsin) {}
	// Virtual destructor
	virtual ~Organise(){}

	// Virtual print results function
	virtual void printResults() const = 0;
	// Function to print the map - print the id and event type and name
	void printAddedEvents() const;

	// Function to add event
	void addEvent(std::shared_ptr<Event> &event);
	// Function to remove Event by id
	void removeEvent(int id);
	// Function to add all Events - can match id's to make sure events are not added twice
	void addAllEvents(std::vector<std::shared_ptr<Event>> &new_events);
	// Function to remove all Events
	void removeAllEvents();

	std::unordered_map<int, std::shared_ptr<Event>> getEvents();

};// End of Organise class

#endif