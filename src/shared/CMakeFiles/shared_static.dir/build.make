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
include src/shared/CMakeFiles/shared_static.dir/depend.make

# Include the progress variables for this target.
include src/shared/CMakeFiles/shared_static.dir/progress.make

# Include the compile flags for this target's objects.
include src/shared/CMakeFiles/shared_static.dir/flags.make

src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.o: src/shared/CMakeFiles/shared_static.dir/flags.make
src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.o: src/shared/state/Exemple.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.o"
	cd /home/anarchist1/PLT/plt/src/shared && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/shared_static.dir/state/Exemple.cpp.o -c /home/anarchist1/PLT/plt/src/shared/state/Exemple.cpp

src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shared_static.dir/state/Exemple.cpp.i"
	cd /home/anarchist1/PLT/plt/src/shared && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarchist1/PLT/plt/src/shared/state/Exemple.cpp > CMakeFiles/shared_static.dir/state/Exemple.cpp.i

src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shared_static.dir/state/Exemple.cpp.s"
	cd /home/anarchist1/PLT/plt/src/shared && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarchist1/PLT/plt/src/shared/state/Exemple.cpp -o CMakeFiles/shared_static.dir/state/Exemple.cpp.s

# Object files for target shared_static
shared_static_OBJECTS = \
"CMakeFiles/shared_static.dir/state/Exemple.cpp.o"

# External object files for target shared_static
shared_static_EXTERNAL_OBJECTS =

src/shared/libshared_static.a: src/shared/CMakeFiles/shared_static.dir/state/Exemple.cpp.o
src/shared/libshared_static.a: src/shared/CMakeFiles/shared_static.dir/build.make
src/shared/libshared_static.a: src/shared/CMakeFiles/shared_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libshared_static.a"
	cd /home/anarchist1/PLT/plt/src/shared && $(CMAKE_COMMAND) -P CMakeFiles/shared_static.dir/cmake_clean_target.cmake
	cd /home/anarchist1/PLT/plt/src/shared && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shared_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/shared/CMakeFiles/shared_static.dir/build: src/shared/libshared_static.a

.PHONY : src/shared/CMakeFiles/shared_static.dir/build

src/shared/CMakeFiles/shared_static.dir/clean:
	cd /home/anarchist1/PLT/plt/src/shared && $(CMAKE_COMMAND) -P CMakeFiles/shared_static.dir/cmake_clean.cmake
.PHONY : src/shared/CMakeFiles/shared_static.dir/clean

src/shared/CMakeFiles/shared_static.dir/depend:
	cd /home/anarchist1/PLT/plt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/src/shared /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/src/shared /home/anarchist1/PLT/plt/src/shared/CMakeFiles/shared_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/shared/CMakeFiles/shared_static.dir/depend
