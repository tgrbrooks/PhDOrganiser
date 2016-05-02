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
	// Give user option to load from a text file
	while (do_load != "y"&&do_load != "n"){
		std::cout << "Welcome to the interactive PhD calendar!" << std::endl << "Do you want to load a previously saved calendar? (y/n): ";
		std::cin >> do_load;
	}
	if (do_load == "y"){
		std::string file_name;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		// Ask user for a file name
		do {
			std::cout << "Enter the name of the load file: ";
			std::cin >> file_name;
		} while (cin.fail());
		// Check if file exists
		ifstream loadFile(file_name.c_str());
		if (!loadFile.good()){
			loadFile.close();
			cout << "WARNING: The file " << file_name << " does not exist" << endl;
		}
		else{
			loadFile.close();
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
		while (!noCaseCompare(option, "help") && !noCaseCompare(option, "new") && !noCaseCompare(option, "edit") && !noCaseCompare(option, "sort") && !noCaseCompare(option, "calendar") && !noCaseCompare(option, "search") && !noCaseCompare(option, "exit")){
			std::cout << "What do you want to do? (Type ""help"" for options): ";
			std::cin >> option;
		}
		// Display help to user
		if (noCaseCompare(option, "help")){
			std::cout << "The available options are:" << std::endl
				<< "help = Display available options" << std::endl
				<< "new = Create a new event" << std::endl
				<< "edit = Edit an existing event" << std::endl
				<< "sort = Sort chosen events by name, type, ID, start or end date" << std::endl
				<< "search = Search chosen events for any string, integer or date (can also search files)" << std::endl
				<< "calendar = Print a calendar for a chosen month to the screen or a tect file" << std::endl
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
			for (auto evt : event_map){
				std::cout << "ID(" << evt.second->getId() << ") " << evt.second->getType() << " (" << evt.second->getName() << ") Start: " << std::endl;
			}
			// Ask user for the ID of the event they want to edit
			int edit_id;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			do {
				std::cout << "Which event would you like to edit?: "; std::cin >> edit_id;
			} while (cin.fail());
			// Pass ID and relevant vector to function
			try{
				event_map = editExistingEvent(edit_id, event_map);
			}
			catch (...){
				std::cout << "WARNING: ID not available" << std::endl;
			}
		}
		// Sort the events -- use function
		else if (noCaseCompare(option, "sort")){
			// Function to select events and return map
			// Pass map to sort function
		}
		// Search the events -- use function
		else if (noCaseCompare(option, "search")){
			// Function to select events and return map
			// Pass map to search function
		}
		// Print a calender either to screen or text file by month -- use function
		else if (noCaseCompare(option, "calendar")){
			// Ask user for the month and year
			// Ask if they want to print to screen or to a text file
			// Pass to function along with all events
		}
		// Exit the organiser
		else if (noCaseCompare(option, "exit")){
			std::string confirm;
			while (confirm != "y"&&confirm != "n"){
				std::cout << "Are you sure you want to exit? (y/n): ";
				std::cin >> confirm;
			}
			if (confirm == "y") exit_flag = 1;
		}
		else { std::cout << "WARNING: Error in option choice" << std::endl; }
	}
	// When exit loop breaks, give option to save the system to a text file -- use function

	return 0;
}

// UNIT TESTING
// To test:

// DateAndTime                            DONE
// check constructors and destructors work
/*DateAndTime dt1;
cout << dt1 << endl;
// check for bad input here
DateAndTime dt2(10, 10, 2010, 6, 30);*/
/*cout << dt2 << endl;
// check all member functions work
// try to break this
//cin >> dt1;
cout << dt1 << endl;
// try to break
dt2.set(10, 10, 2000, 6, 30);
cout << dt2 << endl;
dt1.setDate(1, 2, 2050);
cout << dt2 << endl;
dt2.setTime(4, 5);
cout << dt2.getDay() << dt2.getMonth() << dt2.getYear() << dt2.getHour() << dt2.getMinutes() << endl;
cout << dt2.makeString() << endl;
cout << dt1.timeBetween(dt2) << endl;
dt1.printTimeBetween(dt2);
cout << dt1.timeUntil() << endl;
dt2.printTimeUntil();
// check copying and moving is ok
DateAndTime dt3;
dt3 = move(dt2);
cout << dt3 << " " << dt2 << endl;
dt2.setTime(2, 30);
cout << dt3 << " " << dt2 << endl;
*/

// TextFile
// check constructors and detructors work
/*TextFile tf1;
cout << tf1.getName() << endl;
TextFile tf2("test2.txt");
cout << tf2.getName() << endl;
// check all member functions work
tf1.createFile("test1.txt");
tf1.editFile();
tf1.appendFile();
int num = tf1.searchFile("hello");
cout << num << endl;
tf1.deleteFile();
// check all copying and moving is ok
TextFile tf3;
tf3 = tf2;
cout << tf2.getName() << " " << tf3.getName() << endl;
tf3 = move(tf2);
cout << tf2.getName() << " " << tf3.getName() << endl;*/


// Event and derived classes
// check constructors and detructors work
/*Meeting m1;
Conference c1;
ErrorLog el1;
Lecture l1;
Presentation p1;
Seminar s1;
WeeklyLog wl1;
cout << m1 << endl << c1 << endl << el1 << endl << l1 << endl << p1 << endl << s1 << endl << wl1 << endl;*/
/*Meeting m2("meeting", "schuster", "SBND", "oscillations", 6);
Conference c2("conference", "brighton", "hep", "poster");
ErrorLog el2("error", "comp", "SBND", false);
Lecture l2("lecture", "bragg", "governator", 1);
Presentation p2("pres", "conference room", "DUNE", "trigger", "speaker");
Seminar s2("seminar", "schuster", "SBND");
WeeklyLog wl2("log", "comp", "SBND");*/
/*cout << m2 << endl << c2 << endl << el2 << endl << l2 << endl << p2 << endl << s2 << endl << wl2 << endl;
// check all member functions work
// do for just for seminar and hope for the best for the rest
s1.setStart(dt1); s1.setEnd(dt2); s1.setName("seminar"); s1.setLocation("hicks"); s1.setExperiment("SBND"); s1.setNotes("test2.txt");
cout << s1.timeToEvent() << s1.getStart() << s1.getEnd() << s1.getDuration() << s1.getName() << s1.getLocation() << s1.getExperiment() << s1.getType() << s1.getId() << endl;
cout << s1 << endl;
s1.printTimeToEvent(); s1.printDuration();
//s1.createFile("test3.txt");
//s1.save("test3.txt");
//s1.deleteFile();
// check all copying and moving is ok
// The id's don't change when copying or moving, see if this is a problem in the actual code
// even if I don't ever use them might have to write move and copy to deal with the static id
Seminar s3;
s3 = move(s1);
cout << s3 << "  " << s3.getId() << "  " << s1.getId() << s1 << endl;*/

// Sort
// In the program, have a vector for each event type and push back to that vector each time a new event is created
/*std::vector<std::shared_ptr<Event>> event_feed;
c2.setNotes("test3.txt");
event_feed.push_back(std::make_shared<Lecture>(Lecture("lecture", "bragg", "governator", 1)));
event_feed.push_back(std::make_shared<Conference>(c2));
event_feed.push_back(std::make_shared<ErrorLog>(el2));
std::unordered_map<int, std::shared_ptr<Event>> events;
for (auto evt : event_feed) {
	cout << evt.use_count() << endl;
	events.emplace(evt->getId(), evt);
}*/
// check constructors and detructors work
/*Sort sort1(events);
sort1.addAllEvents(event_feed);
sort1.removeEvent(2);
sort1.printAddedEvents();
std::shared_ptr<Event> l3 = std::make_shared<Lecture>(Lecture("lecture", "bragg", "governator", 1));
sort1.addEvent(l3);
sort1.printAddedEvents();
sort1.sortName(false);
sort1.printResults();
sort1.sortId(false);
sort1.printResults();
sort1.sortType(true);
sort1.printResults();
sort1.sortStart(true);
sort1.printResults();
sort1.removeAllEvents();
sort1.printAddedEvents();
// check all member functions work
// first check that the shared pointers are working correctly for pointers being passed to functions, if they are then write move and copy operators to create new shared pointer instances
// check all copying and moving is ok
Sort sort2;
sort2 = sort1;
std::unordered_map<int, std::shared_ptr<Event>> events2 = sort2.getEvents();
for (const auto &event : events2) {
std::cout << "ID: " << event.first << " " << event.second->getType() << ": " << event.second.use_count() << std::endl;
}*/

// Search
/*Search search1;
search1.addAllEvents(event_feed);
search1.printAddedEvents();
std::string search_parameter = "bragg";
search1.searchFilesFor(search_parameter);
search1.printResults();*/
// check constructors and detructors work
// check all member functions work
// check all copying and moving is ok