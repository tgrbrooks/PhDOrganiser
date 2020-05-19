# PhD Organiser

Short masters project for C++ Object Orientated Programming course.
A terminal based calendar/organiser for PhD students with no external dependencies.

## Installation

Create a build directory

```
mkdir build
cd build
```

Configure and build

```
cmake ..
make
```

Source the setup script that should now be in your top level directory

```
cd ..
. setup.sh
```

Run the organiser with the `phd` command.

## Features

* Save and load different calendars
* Create different types of events
  * Conferences
  * Lectures
  * Meetings
  * Presentations
  * Seminars
* Edit existing events
* Sort and search through events
* Display a calendar
* Keep daily and weekly logs and track issues
* Basic txt file editor
