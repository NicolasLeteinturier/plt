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
include test/shared/CMakeFiles/test_shared_dummy.dir/depend.make

# Include the progress variables for this target.
include test/shared/CMakeFiles/test_shared_dummy.dir/progress.make

# Include the compile flags for this target's objects.
include test/shared/CMakeFiles/test_shared_dummy.dir/flags.make

test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o: test/shared/CMakeFiles/test_shared_dummy.dir/flags.make
test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o: test/shared/test_shared_dummy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o"
	cd /home/anarchist1/PLT/plt/test/shared && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o -c /home/anarchist1/PLT/plt/test/shared/test_shared_dummy.cpp

test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.i"
	cd /home/anarchist1/PLT/plt/test/shared && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anarchist1/PLT/plt/test/shared/test_shared_dummy.cpp > CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.i

test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.s"
	cd /home/anarchist1/PLT/plt/test/shared && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anarchist1/PLT/plt/test/shared/test_shared_dummy.cpp -o CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.s

# Object files for target test_shared_dummy
test_shared_dummy_OBJECTS = \
"CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o"

# External object files for target test_shared_dummy
test_shared_dummy_EXTERNAL_OBJECTS =

test/shared/test_shared_dummy: test/shared/CMakeFiles/test_shared_dummy.dir/test_shared_dummy.cpp.o
test/shared/test_shared_dummy: test/shared/CMakeFiles/test_shared_dummy.dir/build.make
test/shared/test_shared_dummy: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
test/shared/test_shared_dummy: src/shared/libshared_static.a
test/shared/test_shared_dummy: src/client/libclient_static.a
test/shared/test_shared_dummy: src/shared/libshared_static.a
test/shared/test_shared_dummy: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
test/shared/test_shared_dummy: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
test/shared/test_shared_dummy: /usr/lib/x86_64-linux-gnu/libsfml-network.so.2.5.1
test/shared/test_shared_dummy: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
test/shared/test_shared_dummy: test/shared/CMakeFiles/test_shared_dummy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anarchist1/PLT/plt/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_shared_dummy"
	cd /home/anarchist1/PLT/plt/test/shared && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_shared_dummy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/shared/CMakeFiles/test_shared_dummy.dir/build: test/shared/test_shared_dummy

.PHONY : test/shared/CMakeFiles/test_shared_dummy.dir/build

test/shared/CMakeFiles/test_shared_dummy.dir/clean:
	cd /home/anarchist1/PLT/plt/test/shared && $(CMAKE_COMMAND) -P CMakeFiles/test_shared_dummy.dir/cmake_clean.cmake
.PHONY : test/shared/CMakeFiles/test_shared_dummy.dir/clean

test/shared/CMakeFiles/test_shared_dummy.dir/depend:
	cd /home/anarchist1/PLT/plt && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/test/shared /home/anarchist1/PLT/plt /home/anarchist1/PLT/plt/test/shared /home/anarchist1/PLT/plt/test/shared/CMakeFiles/test_shared_dummy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/shared/CMakeFiles/test_shared_dummy.dir/depend
