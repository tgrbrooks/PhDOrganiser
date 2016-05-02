// Source file for functions used in the main script
// Author: tbrooks

#include "MainFunctions.h"

// FUNCTIONS NEEDED
// Print calender by date
/*void printCalendar(bool to_file, std::unordered_map<int, std::shared_ptr<Event>> events){

}

// Save state
void saveState(std::unordered_map<int, std::shared_ptr<Event>> events){

}*/

// Load state
std::vector<std::shared_ptr<Event>> loadEvents(std::string file_name, std::vector<std::shared_ptr<Event>> events){
	ifstream loadFile(file_name.c_str());
	std::string line;
	// Loop over the lines of the file until the end 
	while (std::getline(loadFile, line)){
		string::size_type pos = 0;
		if (noCaseFind(line, "Conference")){
			// Read the event from the file
			Conference temp;
			loadFile >> temp;
			// Push back to the corresponding vector
			events.push_back(std::make_shared<Conference>(temp));
		}
		// Do the same for all event types
		if (noCaseFind(line, "ErrorLog")){
			ErrorLog temp;
			loadFile >> temp;
			events.push_back(std::make_shared<ErrorLog>(temp));
		}
		if (noCaseFind(line, "Lecture")){
			Lecture temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Lecture>(temp));
		}
		if (noCaseFind(line, "Meeting")){
			Meeting temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Meeting>(temp));
		}
		if (noCaseFind(line, "Presentation")){
			Presentation temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Presentation>(temp));
		}
		if (noCaseFind(line, "Seminar")){
			Seminar temp;
			loadFile >> temp;
			events.push_back(std::make_shared<Seminar>(temp));
		}
		if (noCaseFind(line, "WeeklyLog")){
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
		!noCaseCompare(option, "weekly log")){
		std::cout << "What type of event do you want to create?: ";
		std::cin >> option;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// Loop until the input is a string
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Location: "; std::cin >> location;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Field: "; std::cin >> field;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Role: "; std::cin >> role;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	// Loop until the input is a DateAndTime class
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
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
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
			}
			// Create a new file
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Experiment: "; std::cin >> experiment;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Project: "; std::cin >> project;
	} while (cin.fail());
	// Try to create a new error log
	try {
		ErrorLog temp(name, project, experiment, false);
		std::string file_name;
		// Make user create a log
		do {
			std::cout << "Enter name of error log file: "; std::cin >> file_name;
		} while (cin.fail());
		temp.createFile(file_name);
		// Ask if the error has been fixed
		string is_solved;
		while (is_solved != "y"&&is_solved != "n"){
			std::cout << "Has this error been solved? (y/n): ";
			std::cin >> is_solved;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Location: "; std::cin >> location;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Group: "; std::cin >> group;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Experiment: "; std::cin >> experiment;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Number of attendees: "; std::cin >> attendees;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
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
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
			} while (cin.fail());
			temp.setMinutes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create minutes? (y/n): ";
				std::cin >> create_file;
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Location: "; std::cin >> location;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Lecturer: "; std::cin >> lecturer;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Lecture number: "; std::cin >> number;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
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
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Location: "; std::cin >> location;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Experiment: "; std::cin >> experiment;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Project: "; std::cin >> project;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Role: "; std::cin >> role;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
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
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Location: "; std::cin >> location;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Experiment: "; std::cin >> experiment;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
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
		}
		if (has_file == "y"){
			std::string file_name;
			do {
				std::cout << "File name: "; std::cin >> file_name;
			} while (cin.fail());
			temp.setNotes(file_name);
		}
		else {
			std::string create_file;
			while (create_file != "y"&&create_file != "n"){
				std::cout << "Would you like to create a file? (y/n): ";
				std::cin >> create_file;
			}
			if (create_file == "y"){
				std::string file_name;
				do {
					std::cout << "File name: "; std::cin >> file_name;
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
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Name: "; std::cin >> name;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Experiment: "; std::cin >> experiment;
	} while (cin.fail());
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do {
		std::cout << "Project: "; std::cin >> project;
	} while (cin.fail());
	// Try to create a weekly log
	try {
		WeeklyLog temp(name, project, experiment);
		std::string file_name;
		// Create a log file
		do {
			std::cout << "Enter name of weekly log file: "; std::cin >> file_name;
		} while (cin.fail());
		temp.createFile(file_name);
		events.emplace(temp.getId(), std::make_shared<WeeklyLog>(temp));
	}
	catch (...) {
		std::cout << "WARNING: Issue creating weekly log please try again" << std::endl;
	}
	return events;
}

// User creates a search with input checks

// User creates a sort with input checks

// User edits existing events with input checks
std::unordered_map<int, std::shared_ptr<Event>> editExistingEvent(int id, std::unordered_map<int, std::shared_ptr<Event>> events){
	auto evt = events.find(id);
	// Display the event the user wants to edit
	std::cout << "You want to edit" << std::endl;
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
			&& !noCaseCompare(option, "attendee number") && !noCaseCompare(option, "finished")){
			std::cout << "What field do you want to edit?: ";
			std::cin >> option;
		}
		// Edit the different options
		if (option == "name"){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Name: "; std::cin >> name;
			} while (cin.fail());
			evt->second->setName(name);
		}
		if (option == "start"){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Start dd/mm/yyyy (hour:min): "; std::cin >> start;
			} while (cin.fail());
			evt->second->setStart(start);
		}
		if (option == "end"){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "End dd/mm/yyyy (hour:min): "; std::cin >> end;
			} while (cin.fail());
			evt->second->setEnd(end);
		}
		if (option=="location") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Location: "; std::cin >> location;
			} while (cin.fail());
			evt->second->setLocation(location);
		}
		if (option == "experiment") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Experiment: "; std::cin >> experiment;
			} while (cin.fail());
			evt->second->setExperiment(experiment);
		}
		if (option == "project") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Project: "; std::cin >> project;
			} while (cin.fail());
			evt->second->setProject(project);
		}
		if (option == "group") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Group: "; std::cin >> group;
			} while (cin.fail());
			evt->second->setGroup(group);
		}
		if (option == "field") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Field: "; std::cin >> field;
			} while (cin.fail());
			evt->second->setField(field);
		}
		if (option == "role") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Role: "; std::cin >> role;
			} while (cin.fail());
			evt->second->setRole(role);
		}
		if (option == "lecturer") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Lecturer: "; std::cin >> lecturer;
			} while (cin.fail());
			evt->second->setLecturer(lecturer);
		}
		if (option == "lecture number") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Lecture number: "; std::cin >> number;
			} while (cin.fail());
			evt->second->setNumber(number);
		}
		if (option == "attendee number") {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Attendee number: "; std::cin >> num_attendees;
			} while (cin.fail());
			evt->second->setNumAttendees(num_attendees);
		}
		if (option == "solved") {
			std::string is_solved;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while(is_solved!="y"&&is_solved!="n") {
				std::cout << "Is the error solved? (y/n): "; std::cin >> is_solved;
			}
			if (is_solved == "y"){
				evt->second->setSolved(true);
			}
			else evt->second->setSolved(false);
		}
		// If the user wants to edit a textfile
		if ((option == "log") || (option == "minutes") || (option == "notes")){
			TextFile edit_file = evt->second->getFile();
			// If the text file does not exist ask if they want to create one
			if (edit_file.getName() == "none"){
				std::string create_file;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (create_file != "y"&&create_file != "n") {
					std::cout << "File does not exist, create one? (y/n): "; std::cin >> create_file;
				}
				// Ask for file name and create a new file
				if (create_file == "y"){
					std::string file_name;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					do {
						std::cout << "Choose file name: "; std::cin >> file_name;
					} while (cin.fail());
					edit_file.createFile(file_name);
				}
			}
			// If file already exists let user edit file, append to it or delete it
			else{
				std::string file_option;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (file_option != "append"&&file_option != "edit"&&file_option!="delete") {
					std::cout << "Do you want to edit, append or delete file?: "; std::cin >> file_option;
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
	std::cout << "Events in the next 24 hours: " << std::endl;
	// Retrive all events occuring in the next 24 hours
	for (auto event : events){
		if (event->getStart().timeUntil() < 86400 && event->getStart().timeUntil() > 0){
			std::cout << event->getType() << " (" << event->getName() << ") Start: " << event->getStart() << std::endl;
		}
	}
}
