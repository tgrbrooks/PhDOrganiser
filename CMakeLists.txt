# Set minimum version
cmake_minimum_required(VERSION 2.8.9)
project (phdorganiser)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(PHD_BINARY_DIR ${PROJECT_BINARY_DIR}/bin CACHE PATH "Where to output executables")
#set(PHD_INCDIR ${PROJECT_BINARY_DIR}/include CACHE PATH "Where to collect headers")

# Configure local scripts
set(PHDROOT ${PROJECT_BINARY_DIR})
configure_file(${CMAKE_SOURCE_DIR}/config/setup.sh.in
               ${PROJECT_SOURCE_DIR}/setup.sh
               @ONLY NEWLINE_STYLE UNIX)

# Point CMake towards header files
include_directories(include)

# Configure global scripts
#set(PHDROOT ${CMAKE_INSTALL_PREFIX})
#configure_file(${CMAKE_SOURCE_DIR}/config/setup.sh.in
#               ${PHD_BINARY_DIR}/setup.sh
#               @ONLY NEWLINE_STYLE UNIX)

# Install env files
install(FILES ${PHD_BINARY_DIR}/setup.sh
       DESTINATION bin)

file(GLOB SOURCES "source/*.cpp")
# Create the executable
add_executable(phd ${SOURCES})
