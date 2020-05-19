// Source file for Organise class and all derived classes
// Author: tbrooks

#include "Sort.h"

// Copy constructor
Sort::Sort(Sort &S){
	_sorted_events = S._sorted_events; _events = S._events;
}
// Copy assignment operator
Sort& Sort::operator=(Sort &S){
	// Check for self assignment
	if (&S == this) return *this;
	// Delete this objects data
	_sorted_events.clear(); _events.clear();
	// Copy data from S to this
	_sorted_events = S._sorted_events; _events = S._events;
	return *this;
}

// Move constructor
Sort::Sort(Sort &&S){
	// Steal the data
	_sorted_events = S._sorted_events; _events = S._events;
	S._sorted_events.clear(); S._events.clear();
}
// Move assignment operator
Sort& Sort::operator=(Sort &&S){
	// Use swap function to steal the data
	std::swap(_sorted_events, S._sorted_events); std::swap(_sorted_events, S._sorted_events);
	return *this;
}

// Overridden print results function - show id event type and name and sorted value - Template?
void Sort::printResults() const {
	std::cout << "Sorted Events:" << std::endl;
	for (auto sorted_event : _sorted_events){
		std::cout << "ID: " << sorted_event.first->getId() << " " << sorted_event.first->getType() << " ("
			<< sorted_event.first->getName() << ") Sorted value = " << sorted_event.second << std::endl;
	}
}

// Functions to sort events by name, type (string) or ID (integer)
void Sort::sortName(bool ascending) {
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> temp_sorted;
	for (auto event : _events){
		temp_sorted.push_back(std::make_pair(event.second, event.second->getName()));
	}
	// Use lambdas to sort by second value
	if (ascending) {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getName() < right.first->getName();
		});
	}
	// If ascending flag is false use lambda to sort in reverse order
	else {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getName() > right.first->getName();
		});
	}
	_sorted_events = temp_sorted;
}

void Sort::sortType(bool ascending) {
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> temp_sorted;
	for (auto event : _events){
		temp_sorted.push_back(std::make_pair(event.second, event.second->getType()));
	}
	// Use lambdas to sort by second value
	if (ascending) {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getType() < right.first->getType();
		});
	}
	// If ascending flag is false use lambda to sort in reverse order
	else {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getType() > right.first->getType();
		});
	}
	_sorted_events = temp_sorted;
}

void Sort::sortId(bool ascending) {
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> temp_sorted;
	for (auto event : _events){
		temp_sorted.push_back(std::make_pair(event.second, std::to_string(event.second->getId())));
	}
	// Use lambdas to sort by second value
	if (ascending) {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getId() < right.first->getId();
		});
	}
	// If ascending flag is false use lambda to sort in reverse order
	else {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getId() > right.first->getId();
		});
	}
	_sorted_events = temp_sorted;
}

// Functions to sort by start/end time and duration
void Sort::sortStart(bool ascending) {
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> temp_sorted;
	for (auto event : _events){
		temp_sorted.push_back(std::make_pair(event.second, (event.second->getStart()).makeString()));
	}
	// Use lambdas to sort by second value
	if (ascending) {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getStart() < right.first->getStart();
		});
	}
	// If ascending flag is false use lambda to sort in reverse order
	else {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getStart() > right.first->getStart();
		});
	}
	_sorted_events = temp_sorted;
}

void Sort::sortEnd(bool ascending) {
	std::vector<std::pair<std::shared_ptr<Event>, std::string>> temp_sorted;
	for (auto event : _events){
		temp_sorted.push_back(std::make_pair(event.second, (event.second->getEnd()).makeString()));
	}
	// Use lambdas to sort by second value
	if (ascending) {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getEnd() < right.first->getEnd();
		});
	}
	// If ascending flag is false use lambda to sort in reverse order
	else {
		std::sort(temp_sorted.begin(), temp_sorted.end(), [](const std::pair<std::shared_ptr<Event>, std::string> &left, const std::pair<std::shared_ptr<Event>, std::string> &right) {
			return left.first->getEnd() > right.first->getEnd();
		});
	}
	_sorted_events = temp_sorted;
}

// Accessor function for container of sorted results
std::vector<std::pair<std::shared_ptr<Event>, std::string>> Sort::getSortedEvents() {
	return _sorted_events;
}