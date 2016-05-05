// Header file for functions used in the main script
// Author: tbrooks

#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "DateAndTime.h"
#include "TextFile.h"
#include "Meeting.h"
#include "Conference.h"
#include "ErrorLog.h"
#include "Lecture.h"
#include "Presentation.h"
#include "Search.h"
#include "Seminar.h"
#include "Sort.h"
#include "WeeklyLog.h"

// FUNCTIONS NEEDED
// Print calender by date
void printCalendar(bool to_file, std::unordered_map<int, std::shared_ptr<Event>> events);

// Save state
void saveState(std::string file_name, std::unordered_map<int, std::shared_ptr<Event>> events);

// Load state
std::vector<std::shared_ptr<Event>> loadEvents(std::string file_name, std::vector<std::shared_ptr<Event>> events);

// User enters new event with input checks
std::unordered_map<int, std::shared_ptr<Event>> createNewEvent(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewConference(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewErrorLog(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewLecture(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewMeeting(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewPresentation(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewSeminar(std::unordered_map<int, std::shared_ptr<Event>> events);
std::unordered_map<int, std::shared_ptr<Event>> createNewWeeklyLog(std::unordered_map<int, std::shared_ptr<Event>> events);


// User creates a search with input checks
void searchEvents(std::unordered_map<int, std::shared_ptr<Event>> events);

// User creates a sort with input checks
void sortEvents(std::unordered_map<int, std::shared_ptr<Event>> events);

// User edits existing events with input checks
std::unordered_map<int, std::shared_ptr<Event>> editExistingEvent(int id, std::unordered_map<int, std::shared_ptr<Event>> events);

// Display events for the current day
void upcomingEvents(std::vector<std::shared_ptr<Event>> events);

#endif