// Source file for functions used in the main script
// Author: tbrooks

#include "MainFunctions.h"

// Print calender by date
void printCalendar(bool to_file, std::unordered_map<int, std::shared_ptr<Event>> events){
	std::unordered_map<int, std::shared_ptr<Event>> temp_events = events;
	// Ask user for month and year
	int year{ 0 };
	int month{ 0 };
	int days{ 0 };
	while (!(year >= 2000 && year <= 2050) || std::cin.fail()){
		std::cout << std::endl << "Enter a year: ";
		std::cin >> year;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	while (!(month >= 1 && month <= 12) || std::cin.fail()){
		std::cout << "Enter a month: ";
		std::cin >> month;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	// Get the number of days in that month
	if (month == 4 || month == 6 || month == 9 || month == 11) days = 30;
	else if (month == 2)
	{
		bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (leap) days = 29;
		else days = 28;
	}
	else days = 31;
	// Print out the names of the weekdays
	std::cout << std::endl << "|----------|----------|----------|----------|----------|----------|----------|" << std::endl;
	std::cout << "|Sunday    |Monday    |Tuesday   |Wednesday |Thursday  |Friday    |Saturday  |" << std::endl;
	std::cout << "|----------|----------|----------|----------|----------|----------|----------|" << std::endl;
	// Loop over the days in the month
	for (int day(1); day < (days + 1); day++){
		// Use tm struct to get the corresponding days
		time_t raw_time;
		struct tm time_info;
		time(&raw_time);
		localtime_s(&time_info, &raw_time);
		time_info.tm_year = year - 1900;
		time_info.tm_mon = month - 1;
		time_info.tm_mday = day;
		mktime(&time_info);
		int week_day = time_info.tm_wday; // 0 = sunday - 6 = saturday
		// For the first day check what day it is and leave corresponding amount of space for a monday start
		if (day == 1){
			for (int i(0); i < week_day ; i++){ std::cout << "|          "; }
		}
		if (day < 10) std::cout << "|" << day << "         ";
		else std::cout << "|" << day << "        ";
		// After every sunday start a new row
		if (week_day == 6){
			// Loop from 1-4
			for (int height(0); height < 4; height++){
				std::cout << "|" << std::endl;
				// Loop through day-6 (check valid) to day
				for (int dy(day - 6); dy < day + 1; dy++){
					bool print_flag{ 0 };
					// Loop through events
					for (auto evt : temp_events){
						if (dy > 0) {
							DateAndTime dt(dy, month, year, 12, 0);
							// If there is an event on this day print (max size = 10) and remove event from map
							if (evt.second->getStart() == dt){
								std::string name = evt.second->getName();
								name.resize(10, ' ');
								std::cout << "|" << name;
								int id = evt.second->getId();
								temp_events.erase(id);
								print_flag = 1;
								break;
							}
						}
					}// Event loop
					if (!print_flag) std::cout << "|          ";
				}// Day loop
			}// Box height loop
			std::cout << "|" << std::endl << "|----------|----------|----------|----------|----------|----------|----------|" << std::endl;
		}
		// Continue until the last day of the month
		if (day == days){
			for (int i(0); i<(6 - week_day); i++) std::cout << "|          ";
			for (int height(0); height < 4; height++){
				std::cout << "|" << std::endl;
				// Loop through day-6 (check valid) to day
				for (int dy(day - week_day); dy < (day-week_day) + 7; dy++){
					bool print_flag{ 0 };
					// Loop through events
					for (auto evt : temp_events){
						if (dy<=days) {
							DateAndTime dt(dy, month, year, 12, 0);
							// If there is an event on this day print (max size = 10) and remove event from map
							if (evt.second->getStart() == dt){
								std::string name = evt.second->getName();
								name.resize(10, ' ');
								std::cout << "|" << name;
								int id = evt.second->getId();
								temp_events.erase(id);
								print_flag = 1;
							}
							// Else print filler
						}
					}// Event loop
					if (!print_flag) std::cout << "|          ";
				}// Day loop
			}// Box height loop
			std::cout << "|" << std::endl << "|----------|----------|----------|----------|----------|----------|----------|" << std::endl;
		}
	}
}

inline bool testFile(const std::string& file_name) {
	ifstream f(file_name.c_str());
	return f.good();
}

// Save state
void saveState(std::string file_name, std::unordered_map<int, std::shared_ptr<Event>> events){
	if (file_name != "none"){
		// Check file exists
		if (testFile(file_name)){
			// Delete the file
			remove(file_name.c_str());
			// Loop over all events in the map and save them to the new file
			for (auto evt : events){
				evt.second->save(file_name);
			}
		}
		else{
			std::cout << "WARNING: The file " << file_name << " does not exist, cannot delete" << endl;
		}
	}
	else{
		// Ask user for a file name that doesn't already exist
		do{
			std::cout << std::endl << "Enter a file name: ";
			std::cin >> file_name;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (testFile(file_name));
		ofstream saveFile(file_name.c_str());
		saveFile << file_name << std::endl;
		// Loop over all events in the map and save them to the new file
		for (auto evt : events){
			evt.second->save(file_name);
		}
	}
}

// Load state
std::vector<std::shared_ptr<Event>> loadEvents(std::string file_name, std::vector<std::shared_ptr<Event>> events){
	ifstream loadFile(file_name.c_str());
	std::string line;
	// Loop over the lines of the file until the end 
	while (std::getline(loadFile, line)){
		string::size_type pos = 0;
		if (noCaseFind(line, "Event::Conference")){
			// Read the event from the file
			Conference temp;
			loadFile >> temp;
			// Push back to the corresponding vector
			events.push_back(std::make_shared<Conference>(temp));
		}
		// Do the same for all event types
		if (noCaseFind(line, "Event::ErrorLog")){
			ErrorLog temp;
			loadFile >> temp;
			events.push_back(std::make_shared<ErrorLog>(temp));
		}
		if (noCaseFind(line, "Event::Lecture")){
			Lecture temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Lecture>(temp));
		}
		if (noCaseFind(line, "Event::Meeting")){
			Meeting temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Meeting>(temp));
		}
		if (noCaseFind(line, "Event::Presentation")){
			Presentation temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Presentation>(temp));
		}
		if (noCaseFind(line, "Event::Seminar")){
			Seminar temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Seminar>(temp));
		}
		if (noCaseFind(line, "Event::WeeklyLog")){
			WeeklyLog temp;
			loadFile >> temp;
			events.push_back(std::make_shared<WeeklyLog>(temp));
		}
	}
	// Close the file and return vector of events
	loadFile.close();
	return events;
}

// User enters new event with input checks
std::unordered_map<int, std::shared_ptr<Event>> createNewEvent(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Let user choose what type of event they want to create
	std::string option;
	while (!noCaseCompare(option, "conference") && !noCaseCompare(option, "error log") && !noCaseCompare(option, "lecture") && 
		!noCaseCompare(option, "meeting") && !noCaseCompare(option, "presentation") && !noCaseCompare(option, "seminar") && 
		!noCaseCompare(option, "weekly log") && !noCaseCompare(option, "help")){
		std::cout << std::endl << "What type of event do you want to create?: ";
		getline(cin, option);
	}
	// Display available options to user
	if (noCaseCompare(option, "help")){
		std::cout << std::endl << "The available event types are:" << std::endl
			<< "conference, error log, lecture, meeting, presentation, seminar or weekly log" << std::endl;
	}
	// Send user to relevant creation funtion for that event type
	if (noCaseCompare(option, "conference")){
		events = createNewConference(events);
	}
	if (noCaseCompare(option, "error log")){
		events = createNewErrorLog(events);
	}
	if (noCaseCompare(option, "lecture")){
		events = createNewLecture(events);
	}
	if (noCaseCompare(option, "meeting")){
		events = createNewMeeting(events);
	}
	if (noCaseCompare(option, "presentation")){
		events = createNewPresentation(events);
	}
	if (noCaseCompare(option, "seminar")){
		events = createNewSeminar(events);
	}
	if (noCaseCompare(option, "weekly log")){
		events = createNewWeeklyLog(events);
	}
	// Return all events with the new event added
	return events;
}

// Create a new conference with all input fields and checks
std::unordered_map<int, std::shared_ptr<Event>> createNewConference(std::unordered_map<int, std::shared_ptr<Event>> events){
	std::string name, location, field, role;
	DateAndTime start, end;
	// Let user fill in all the relevant fields
	// Loop until the input is a string
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Location: "; getline(std::cin, location);
	} while (cin.fail());
	do {
		std::cout << "Field: "; getline(std::cin, field);
	} while (cin.fail());
	do {
		std::cout << "Role: "; getline(std::cin, role);
	} while (cin.fail());
	// Loop until the input is a DateAndTime class
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	// Try to create the class catching any errors
	try {
		Conference temp(name, location, field, role);
		temp.setStart(start); temp.setEnd(end);
		// Let the user either add a text file or create a new one
		std::string has_file;
		while (has_file != "y"&&has_file != "n"){
			std::cout << "Is there a text file associated with this event? (y/n): ";
			std::cin >> has_file;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// Create a new file
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.createFile(file_name);
			}
		}
		// Push the new event back on to the unordered map
		events.emplace(temp.getId(), std::make_shared<Conference>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating conference please try again" << std::endl;
	}
	return events;
}

// Create a new error log with all input fields and checks
std::unordered_map<int, std::shared_ptr<Event>> createNewErrorLog(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, project, experiment;
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (std::cin.fail());
	do {
		std::cout << "Experiment: "; getline(std::cin, experiment);
	} while (cin.fail());
	do {
		std::cout << "Project: "; getline(std::cin, project);
	} while (cin.fail());
	// Try to create a new error log
	try {
		ErrorLog temp(name, project, experiment, false);
		std::string file_name;
		// Make user create a log
		do {
			std::cout << "Enter name of error log file: "; std::cin >> file_name;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		temp.createFile(file_name);
		// Ask if the error has been fixed
		string is_solved;
		while (is_solved != "y"&&is_solved != "n"){
			std::cout << "Has this error been solved? (y/n): ";
			std::cin >> is_solved;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (is_solved == "y") temp.setSolved(true);
		// Push to the event container
		events.emplace(temp.getId(),std::make_shared<ErrorLog>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating error log please try again" << std::endl;
	}
	return events;
}

// Create a new meeting
std::unordered_map<int, std::shared_ptr<Event>> createNewMeeting(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, location, group, experiment;
	int attendees;
	DateAndTime start, end;
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Location: "; getline(std::cin, location);
	} while (cin.fail());
	do {
		std::cout << "Group: "; getline(std::cin, group);
	} while (cin.fail());
	do {
		std::cout << "Experiment: "; getline(std::cin, experiment);
	} while (cin.fail());
	do {
		std::cout << "Number of attendees: "; std::cin >> attendees;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	// Try to create a meeting
	try {
		Meeting temp(name, location, experiment, group, attendees);
		temp.setStart(start); temp.setEnd(end);
		// Set or create a file
		std::string has_file;
		while (has_file != "y"&&has_file != "n"){
			std::cout << "Are there already minutes for this meeting? (y/n): ";
			std::cin >> has_file;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			temp.setMinutes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create minutes? (y/n): ";
				std::cin >> create_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.createFile(file_name);
			}
		}
		events.emplace(temp.getId(), std::make_shared<Meeting>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating meeting please try again" << std::endl;
	}
	return events;
}

// Create a new lecture
std::unordered_map<int, std::shared_ptr<Event>> createNewLecture(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, location, lecturer;
	int number;
	DateAndTime start, end;
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Location: "; getline(std::cin, location);
	} while (cin.fail());
	do {
		std::cout << "Lecturer: "; getline(std::cin, lecturer);
	} while (cin.fail());
	do {
		std::cout << "Lecture number: "; std::cin >> number;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	// Try to create a lecture
	try {
		Lecture temp(name, location, lecturer, number);
		temp.setStart(start); temp.setEnd(end);
		// Set or create a file
		std::string has_file;
		while (has_file != "y"&&has_file != "n"){
			std::cout << "Is there a text file associated with this event? (y/n): ";
			std::cin >> has_file;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.createFile(file_name);
			}
		}
		events.emplace(temp.getId(), std::make_shared<Lecture>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating lecture please try again" << std::endl;
	}
	return events;
}

// Create a new presentation
std::unordered_map<int, std::shared_ptr<Event>> createNewPresentation(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, location, project, role, experiment;
	DateAndTime start, end;
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Location: "; getline(std::cin, location);
	} while (cin.fail());
	do {
		std::cout << "Experiment: "; getline(std::cin, experiment);
	} while (cin.fail());
	do {
		std::cout << "Project: "; getline(std::cin, project);
	} while (cin.fail());
	do {
		std::cout << "Role: "; getline(std::cin, role);
	} while (cin.fail());
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	// Try to create a presentation
	try {
		Presentation temp(name, location, role, project, experiment);
		temp.setStart(start); temp.setEnd(end);
		// Set or create a text file
		std::string has_file;
		while (has_file != "y"&&has_file != "n"){
			std::cout << "Is there a text file associated with this event? (y/n): ";
			std::cin >> has_file;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.createFile(file_name);
			}
		}
		events.emplace(temp.getId(), std::make_shared<Presentation>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating presentation please try again" << std::endl;
	}
	return events;
}

// Create a new seminar
std::unordered_map<int, std::shared_ptr<Event>> createNewSeminar(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, location, experiment;
	DateAndTime start, end;
	do {
		std::cout << std::endl << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Location: "; getline(std::cin, location);
	} while (cin.fail());
	do {
		std::cout << "Experiment: "; getline(std::cin, experiment);
	} while (cin.fail());
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (cin.fail());
	// Try to create a seminar
	try {
		Seminar temp(name, location, experiment);
		temp.setStart(start); temp.setEnd(end);
		// Set or create a text file
		std::string has_file;
		while (has_file != "y"&&has_file != "n"){
			std::cout << "Is there a text file associated with this event? (y/n): ";
			std::cin >> has_file;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				temp.createFile(file_name);
			}
		}
		events.emplace(temp.getId(), std::make_shared<Seminar>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating seminar please try again" << std::endl;
	}
	return events;
}

// Create a new weekly log
std::unordered_map<int, std::shared_ptr<Event>> createNewWeeklyLog(std::unordered_map<int, std::shared_ptr<Event>> events){
	// Fill all relevant fields
	std::string name, project, experiment;
	do {
		std::cout << "Name: "; getline(std::cin, name);
	} while (cin.fail());
	do {
		std::cout << "Experiment: "; getline(std::cin, experiment);
	} while (cin.fail());
	do {
		std::cout << "Project: "; getline(std::cin, project);
	} while (cin.fail());
	// Try to create a weekly log
	try {
		WeeklyLog temp(name, project, experiment);
		std::string file_name;
		// Create a log file
		do {
			std::cout << "Enter name of weekly log file: "; std::cin >> file_name;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		temp.createFile(file_name);
		events.emplace(temp.getId(), std::make_shared<WeeklyLog>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating weekly log please try again" << std::endl;
	}
	return events;
}

// User creates a sort with input checks
void sortEvents(std::unordered_map<int, std::shared_ptr<Event>> events){
	Sort sort1(events);
	bool finished{ 0 };
	while (!finished){
		std::string option;
		std::string ascending;
		bool ascending_flag{ 1 };
		// Ask user what they want to sort by
		while (!noCaseCompare(option, "name") && !noCaseCompare(option, "type") && !noCaseCompare(option, "id")
			&& !noCaseCompare(option, "start") && !noCaseCompare(option, "end") && !noCaseCompare(option, "finished")
			&& !noCaseCompare(option, "help")){
			std::cout << std::endl << "What field do you want to sort by?: ";
			std::cin >> option;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		// Ask user if thew want to sort in ascending order
		while (ascending != "y"&&ascending != "n"&&option != "finished"&&option != "help") {
			std::cout << std::endl << "Ascending order? (y/n)";
			std::cin >> ascending;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (ascending == "n") ascending_flag = 0;
		// Display help to user
		if (noCaseCompare(option, "help")){
			std::cout << std::endl << "The available options are:" << std::endl << "name, type, id, start, end" << std::endl
				<< "Exit: finished" << std::endl;
		}
		// Sort by Id
		if (noCaseCompare(option, "id")){
			sort1.sortId(ascending_flag);
			sort1.printResults();
		}
		// Sort by Name
		if (noCaseCompare(option, "name")){
			sort1.sortName(ascending_flag);
			sort1.printResults();
		}
		// Sort by type
		if (noCaseCompare(option, "type")){
			sort1.sortType(ascending_flag);
			sort1.printResults();
		}
		// Sort by start date
		if (noCaseCompare(option, "start")){
			sort1.sortStart(ascending_flag);
			sort1.printResults();
		}
		// Sort by end date
		if (noCaseCompare(option, "end")){
			sort1.sortEnd(ascending_flag);
			sort1.printResults();
		}
		// Finished
		if (noCaseCompare(option, "finished")){
			finished = 1;
		}
	}
}

// User creates a search with input checks
void searchEvents(std::unordered_map<int, std::shared_ptr<Event>> events){
	Search search(events);
	bool finished{ 0 };
	while (!finished){
		std::string search_type;
		std::string keyword;
		std::string string_parameter;
		int int_parameter;
		DateAndTime dt_parameter;
		std::string option;
		// Ask user what they want to sort by
		while (!noCaseCompare(option, "general") && !noCaseCompare(option, "keyword") && !noCaseCompare(option, "file")
			&& !noCaseCompare(option, "finished") && !noCaseCompare(option, "help")){
			std::cout << std::endl << "What type of search do you want to perform?: ";
			std::cin >> option;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		// Display help to user
		if (noCaseCompare(option, "help")){
			std::cout << std::endl << "The available options are:" << std::endl << "General: Search all fields for a string, integer or date" << std::endl
				<< "Keyword: Same as general but search through a specific field" << std::endl
				<< "File: Search through the notes, logs and minutes for a word or phrase" << std::endl
				<< "Exit: finished" << std::endl;
		}
		// Do a general search
		if (noCaseCompare(option, "general")){
			// Ask user what type the would like to search for
			while (!noCaseCompare(search_type, "int") && !noCaseCompare(search_type, "string") && !noCaseCompare(search_type, "date")){
				std::cout << std::endl << "Do you want to search for a string, int or date?: ";
				std::cin >> search_type;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// If type is an integer
			if (noCaseCompare(search_type, "int")){
				do {
					std::cout << "Enter the search parameter: ";
					std::cin >> int_parameter;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				search.searchFor(int_parameter);
				search.printResults();
			}
			// If type is a string
			if (noCaseCompare(search_type, "string")){
				do {
					std::cout << "Enter the search parameter: ";
					getline(cin, string_parameter);
				} while (cin.fail());
				search.searchFor(string_parameter);
				search.printResults();
			}
			// If type is a date and time
			if (noCaseCompare(search_type, "date")){
				do {
					std::cout << "Enter the search parameter: ";
					std::cin >> dt_parameter;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				search.searchFor(dt_parameter);
				search.printResults();
			}
		}
		// Do a keyword search
		if (noCaseCompare(option, "keyword")){
			do {
				std::cout << std::endl << "Enter the keyword you want to search through: ";
				getline(std::cin, keyword);
			} while (cin.fail());
			// Ask user what type the would like to search for
			while (!noCaseCompare(search_type, "int") && !noCaseCompare(search_type, "string") && !noCaseCompare(search_type, "date")){
				std::cout << std::endl << "Do you want to search for a string, int or date?: ";
				std::cin >> search_type;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// If type is an integer
			if (noCaseCompare(search_type, "int")){
				do {
					std::cout << "Enter the search parameter: ";
					std::cin >> int_parameter;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				search.searchKeywordFor(keyword, int_parameter);
				search.printResults();
			}
			// If type is a string
			if (noCaseCompare(search_type, "string")){
				do {
					std::cout << "Enter the search parameter: ";
					getline(cin, string_parameter);
				} while (cin.fail());
				search.searchKeywordFor(keyword, string_parameter);
				search.printResults();
			}
			// If type is a date and time
			if (noCaseCompare(search_type, "date")){
				do {
					std::cout << "Enter the search parameter: ";
					std::cin >> dt_parameter;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				} while (cin.fail());
				search.searchKeywordFor(keyword, dt_parameter);
				search.printResults();
			}
		}
		// Do a file search
		if (noCaseCompare(option, "file")){
			do {
				std::cout << std::endl << "Enter the search parameter: ";
				getline(cin, string_parameter);
			} while (cin.fail());
			search.searchFilesFor(string_parameter);
		}
		// Finished
		if (noCaseCompare(option, "finished")){
			finished = 1;
		}
	}
}

// User edits existing events with input checks
std::unordered_map<int, std::shared_ptr<Event>> editExistingEvent(int id, std::unordered_map<int, std::shared_ptr<Event>> events){
	auto evt = events.find(id);
	// Display the event the user wants to edit
	std::cout << std::endl << "You want to edit" << std::endl;
	(evt->second)->print();
	bool finished{ 0 };
	while (!finished){
		std::string option;
		std::string name, location, experiment, project, group, field, role, lecturer;
		int number{ 0 }, num_attendees{ 0 };
		DateAndTime start, end;
		// Ask which field the user wants to edit
		while (!noCaseCompare(option, "name") && !noCaseCompare(option, "location") && !noCaseCompare(option, "experiment")
			&& !noCaseCompare(option, "project") && !noCaseCompare(option, "group") && !noCaseCompare(option, "field")
			&& !noCaseCompare(option, "start") && !noCaseCompare(option, "end") && !noCaseCompare(option, "role")
			&& !noCaseCompare(option, "notes") && !noCaseCompare(option, "minutes") && !noCaseCompare(option, "log")
			&& !noCaseCompare(option, "solved") && !noCaseCompare(option, "lecturer") && !noCaseCompare(option, "lecture number")
			&& !noCaseCompare(option, "attendee number") && !noCaseCompare(option, "finished") && !noCaseCompare(option, "help")){
			std::cout << std::endl << "What field do you want to edit?: ";
			getline(std::cin, option);
		}
		// Show help to the user
		if (noCaseCompare(option, "help")){
			std::cout << std::endl << "The available fields for editing are" << std::endl
				<< "All: name, start, end" << std::endl << "Conference: location, field, role, notes" << std::endl
				<< "Error Log: project, experiment, solved, log" << std::endl << "Lecture: location, lecturer, lecture number, notes" << std::endl
				<< "Meeting: location, experiment, group, attendee number, minutes" << std::endl
				<< "Presentation: location, role, experiment, project, notes" << std::endl << "Seminar: location, experiment, notes" << std::endl
				<< "Weekly Log: project, experiment, log" << std::endl << "Exit: finished" << std::endl;
		}
		// Edit the different options
		if (noCaseCompare(option, "name")){
			do {
				std::cout << std::endl << "Name: "; getline(std::cin, name);
			} while (cin.fail());
			evt->second->setName(name);
		}
		if (noCaseCompare(option, "start")){
			do {
				std::cout << std::endl << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			evt->second->setStart(start);
		}
		if (noCaseCompare(option, "end")){
			do {
				std::cout << std::endl << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			evt->second->setEnd(end);
		}
		if (noCaseCompare(option, "location")) {
			do {
				std::cout << std::endl << "Location: "; getline(std::cin, location);
			} while (cin.fail());
			evt->second->setLocation(location);
		}
		if (noCaseCompare(option, "experiment")) {
			do {
				std::cout << std::endl << "Experiment: "; getline(std::cin, experiment);
			} while (cin.fail());
			evt->second->setExperiment(experiment);
		}
		if (noCaseCompare(option, "project")) {
			do {
				std::cout << std::endl << "Project: "; getline(std::cin, project);
			} while (cin.fail());
			evt->second->setProject(project);
		}
		if (noCaseCompare(option, "group")) {
			do {
				std::cout << std::endl << "Group: "; getline(std::cin, group);
			} while (cin.fail());
			evt->second->setGroup(group);
		}
		if (noCaseCompare(option, "field")) {
			do {
				std::cout << std::endl << "Field: "; getline(std::cin, field);
			} while (cin.fail());
			evt->second->setField(field);
		}
		if (noCaseCompare(option, "role")) {
			do {
				std::cout << std::endl << "Role: "; getline(std::cin, role);
			} while (cin.fail());
			evt->second->setRole(role);
		}
		if (noCaseCompare(option, "lecturer")) {
			do {
				std::cout << std::endl << "Lecturer: "; getline(std::cin, lecturer);
			} while (cin.fail());
			evt->second->setLecturer(lecturer);
		}
		if (noCaseCompare(option, "lecture number")) {
			do {
				std::cout << std::endl << "Lecture number: "; std::cin >> number;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			evt->second->setNumber(number);
		}
		if (noCaseCompare(option, "attendee number")) {
			do {
				std::cout << std::endl << "Attendee number: "; std::cin >> num_attendees;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			evt->second->setNumAttendees(num_attendees);
		}
		if (noCaseCompare(option, "solved")) {
			std::string is_solved;
			while(is_solved!="y"&&is_solved!="n") {
				std::cout << std::endl << "Is the error solved? (y/n): "; std::cin >> is_solved;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (is_solved == "y"){
				evt->second->setSolved(true);
			}
			else evt->second->setSolved(false);
		}
		// If the user wants to edit a textfile
		if (noCaseCompare(option, "log") || noCaseCompare(option, "minutes") || noCaseCompare(option, "notes")){
			TextFile edit_file = evt->second->getFile();
			// If the text file does not exist ask if they want to create one
			if (edit_file.getName() == "none"){
				std::string create_file;
				while (create_file != "y"&&create_file != "n") {
					std::cout << std::endl << "File does not exist, create one? (y/n): "; std::cin >> create_file;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				// Ask for file name and create a new file
				if (create_file == "y"){
					std::string file_name;
					do {
						std::cout << "Choose file name: "; std::cin >> file_name;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					edit_file.createFile(file_name);
				}
			}
			// If file already exists let user edit file, append to it, delete it or rename it
			else{
				std::string file_option;
				while (file_option != "append"&&file_option != "edit"&&file_option != "delete"&&file_option != "rename") {
					std::cout << std::endl << "Do you want to edit, append, delete, or rename file?: "; std::cin >> file_option;
					cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (file_option == "append"){
					edit_file.appendFile();
				}
				if (file_option == "edit"){
					edit_file.editFile();
				}
				if (file_option == "delete"){
					edit_file.deleteFile();
				}
				if (file_option == "rename"){
					std::string new_file_name;
					do {
						std::cout << "Choose file name: "; std::cin >> new_file_name;
						cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
					} while (cin.fail());
					edit_file.changeName(new_file_name);
				}
			}
		}
		if (option == "finished") {
			finished = 1;
		}
	}
	return events;
}

// Display events for the current day
void upcomingEvents(std::vector<std::shared_ptr<Event>> events){
	std::cout << std::endl << "Events in the next 24 hours: " << std::endl;
	// Retrive all events occuring in the next 24 hours
	for (auto event : events){
		if (event->getStart().timeUntil() < 86400 && event->getStart().timeUntil() > 0){
			std::cout << event->getType() << " (" << event->getName() << ") Start: " << event->getStart() << std::endl;
		}
	}
}
