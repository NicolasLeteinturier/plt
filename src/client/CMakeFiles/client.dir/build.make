# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anarchist1/PLT/plt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anarchist1/PLT/plt

# Include any dependencies generated for this target.
include src/client/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include src/client/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include src/client/CMakeFiles/client.dir/flags.make

src/client/CMakeFiles/client.dir/main.cpp.o: src/client/CMakeFiles/client.dir/flags.make
src/client/CMakeFiles/client.dir/main.cpp.o: src/client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/client/CMakeFiles/client.dir/main.cpp.o"
	cd /home/anarchist1/PLT/plt/src/client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/main.cpp.o -c /home/anarchist1/PLT/plt/src/client/main.cpp

src/client/CMakeFiles/client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/main.cpp.i"
	cd /home/anarchist1/PLT/plt/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarchist1/PLT/plt/src/client/main.cpp > CMakeFiles/client.dir/main.cpp.i

src/client/CMakeFiles/client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/main.cpp.s"
	cd /home/anarchist1/PLT/plt/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarchist1/PLT/plt/src/client/main.cpp -o CMakeFiles/client.dir/main.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/main.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

bin/client: src/client/CMakeFiles/client.dir/main.cpp.o
bin/client: src/client/CMakeFiles/client.dir/build.make
bin/client: src/client/libclient_static.a
bin/client: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
bin/client: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
bin/client: /usr/lib/x86_64-linux-gnu/libsfml-network.so.2.5.1
bin/client: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
bin/client: src/shared/libshared_static.a
bin/client: src/client/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/client"
	cd /home/anarchist1/PLT/plt/src/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/client/CMakeFiles/client.dir/build: bin/client

.PHONY : src/client/CMakeFiles/client.dir/build

src/client/CMakeFiles/client.dir/clean:
	cd /home/anarchist1/PLT/plt/src/client && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : src/client/CMakeFiles/client.dir/clean

src/client/CMakeFiles/client.dir/depend:
	cd /home/anarchist1/PLT/plt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/src/client /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/src/client /home/anarchist1/PLT/plt/src/client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/client/CMakeFiles/client.dir/depend
