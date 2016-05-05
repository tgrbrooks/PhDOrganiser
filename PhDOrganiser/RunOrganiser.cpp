// Main script for running the PhD organiser program
// Author: tbrooks
// Conventions: - Classes: MyClass
// Namespaces: mynamespace
// - Functions: myFunction
// - Member variables: _my_member_variable
// - Variables: my_variable
// - Static variables: s_my_static_variable
// - Constants: MY_CONSTANT

#include "MainFunctions.h"

int Event::num_events(0);
using namespace std;
int main() {

	bool exit_flag{ 0 };
	bool loaded{ 0 };
	// Create vectors of each type of event
	std::vector<std::shared_ptr<Event>> events;
	std::unordered_map<int, std::shared_ptr<Event>> event_map;
	std::string do_load;
	std::cout << "|----------------------------------------------------------------------------|" << std::endl;
	std::cout << "|  ____   _      ____      ____         _                   _                |" << std::endl;
	std::cout << "| |  _ \\ | |__  |  _ \\    / ___|  __ _ | |  ___  _ __    __| |  __ _  _ __   |" << std::endl;
	std::cout << "| | |_) ||  _ \\ | | | |  | |     / _' || | / _ \\| '_ \\  / _  | / _' || '__|  |" << std::endl;
	std::cout << "| |  __/ | | | || |_| |  | |___ | (_| || ||  __/| | | || (_| || (_| || |     |" << std::endl;
	std::cout << "| |_|    |_| |_||____/    \\____| \\__,_||_| \\___||_| |_| \\__,_| \\__,_||_|     |" << std::endl;
	std::cout << "|----------------------------------------------------------------------------|" << std::endl;
	std::cout << std::endl << "Welcome to the interactive PhD calendar!" << std::endl;
	// Give user option to load from a text file
	while (do_load != "y"&&do_load != "n"){
		std::cout << std::endl << "Do you want to load a previously saved calendar? (y/n): ";
		std::cin >> do_load;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	std::string file_name;
	if (do_load == "y"){
		// Ask user for a file name
		do {
			std::cout << std::endl << "Enter the name of the load file: ";
			std::cin >> file_name;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (cin.fail());
		// Check if file exists
		ifstream load_file(file_name.c_str());
		if (!load_file.good()){
			load_file.close();
			cout << "WARNING: The file " << file_name << " does not exist" << endl;
		}
		else{
			load_file.close();
			// Load in all events and fill vectors of each type of event -- use function
			std::vector<std::shared_ptr<Event>> events = loadEvents(file_name, events);
			// Display any events that are coming up on the same day -- use function
			upcomingEvents(events);
			for (auto evt : events){
				event_map.emplace(evt->getId(), evt);
			}
			loaded = 1;
		}
	}
	// Everything done within exit while loop
	while (!exit_flag){
		// Give user options of what to do next (have a help command to display all the options)
		std::string option;
		while (!noCaseCompare(option, "help") && !noCaseCompare(option, "new") && !noCaseCompare(option, "edit") 
			&& !noCaseCompare(option, "sort") && !noCaseCompare(option, "calendar") && !noCaseCompare(option, "search")
			&& !noCaseCompare(option, "exit")){
			std::cout << std::endl << "What do you want to do? (Type ""help"" for options): ";
			std::cin >> option;
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		// Display help to user
		if (noCaseCompare(option, "help")){
			std::cout << std::endl << "The available options are:" << std::endl
				<< "help = Display available options" << std::endl
				<< "new = Create a new event" << std::endl
				<< "edit = Edit an existing event" << std::endl
				<< "sort = Sort chosen events by name, type, ID, start or end date" << std::endl
				<< "search = Search chosen events for any string, integer or date (can also search files)" << std::endl
				<< "calendar = Print a calendar for a chosen month to the screen or a text file" << std::endl
				<< "exit = Exit the calendar" << std::endl;
		}
		// Create new events -- use function
		else if (noCaseCompare(option, "new")){
			// Ask user which type of event they want to create
			// Pass type and relevant vector to function
			event_map = createNewEvent(event_map);
		}
		// Edit existing events -- use function
		else if (noCaseCompare(option, "edit")){
			// Print all events with their ID type and name
			std::cout << std::endl << "Events: " << std::endl;
			for (auto evt : event_map){
				std::cout << "ID(" << evt.second->getId() << ") " << evt.second->getType()
					<< " (" << evt.second->getName() << ")" << std::endl;
			}
			// Ask user for the ID of the event they want to edit
			int edit_id;
			do {
				std::cout << std::endl << "Which event would you like to edit?: "; std::cin >> edit_id;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} while (cin.fail());
			// Ask user if they want to edit or delete the event
			std::string edit_or_delete;
			while (edit_or_delete != "e"&&edit_or_delete != "d"){
				std::cout << std::endl << "Do you want to edit (e) or delete (d) this event?: ";
				std::cin >> edit_or_delete;
				cin.clear();  cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			// Pass ID and relevant vector to function
			if (event_map.find(edit_id) == event_map.end()){
				std::cout << "WARNING: ID not available" << std::endl;
			}
			else {
				if (edit_or_delete == "e"){
					event_map = editExistingEvent(edit_id, event_map);
				}
				if (edit_or_delete == "d"){
					event_map.erase(edit_id);
				}
			}
		}
		// Sort the events -- use function
		else if (noCaseCompare(option, "sort")){
			// Pass map to sort function
			sortEvents(event_map);

		}
		// Search the events -- use function
		else if (noCaseCompare(option, "search")){
			// Pass map to search function
			searchEvents(event_map);
		}
		// Print a calender either to screen or text file by month -- use function
		else if (noCaseCompare(option, "calendar")){
			// Ask if they want to print to screen or to a text file
			// Pass to function along with all events
			printCalendar(true, event_map);
		}
		// Exit the organiser
		else if (noCaseCompare(option, "exit")){
			std::string confirm;
			while (confirm != "y"&&confirm != "n"){
				std::cout << std::endl << "Are you sure you want to exit? (y/n): ";
				std::cin >> confirm;
				cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (confirm == "y") exit_flag = 1;
		}
		else { std::cout << "WARNING: Error in option choice" << std::endl; }
	}
	// When exit loop breaks, give option to save the system to a text file -- use function
	std::string save_state;
	while (save_state != "y"&&save_state != "n"){
		std::cout << std::endl << "Do you want to save any changes you have made? (y/n): ";
		std::cin >> save_state;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if (save_state == "y"){
		// If the current calendar was loaded overwrite the file with the new list of events
		if (loaded){
			saveState(file_name, event_map);
		}
		// If not create a new file to save to
		else saveState("none", event_map);
	}
	else std::cout << std::endl << "Goodbye!" << std::endl;

	return 0;
}
