# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anonymous/CS/programming_list/programming/object/oop_project/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anonymous/CS/programming_list/programming/object/oop_project/test/build

# Include any dependencies generated for this target.
include CMakeFiles/date_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/date_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/date_test.dir/flags.make

CMakeFiles/date_test.dir/date_test.cc.o: CMakeFiles/date_test.dir/flags.make
CMakeFiles/date_test.dir/date_test.cc.o: ../date_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anonymous/CS/programming_list/programming/object/oop_project/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/date_test.dir/date_test.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/date_test.dir/date_test.cc.o -c /home/anonymous/CS/programming_list/programming/object/oop_project/test/date_test.cc

CMakeFiles/date_test.dir/date_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/date_test.dir/date_test.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anonymous/CS/programming_list/programming/object/oop_project/test/date_test.cc > CMakeFiles/date_test.dir/date_test.cc.i

CMakeFiles/date_test.dir/date_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/date_test.dir/date_test.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anonymous/CS/programming_list/programming/object/oop_project/test/date_test.cc -o CMakeFiles/date_test.dir/date_test.cc.s

# Object files for target date_test
date_test_OBJECTS = \
"CMakeFiles/date_test.dir/date_test.cc.o"

# External object files for target date_test
date_test_EXTERNAL_OBJECTS =

date_test: CMakeFiles/date_test.dir/date_test.cc.o
date_test: CMakeFiles/date_test.dir/build.make
date_test: libsource.a
date_test: CMakeFiles/date_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anonymous/CS/programming_list/programming/object/oop_project/test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable date_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/date_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/date_test.dir/build: date_test

.PHONY : CMakeFiles/date_test.dir/build

CMakeFiles/date_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/date_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/date_test.dir/clean

CMakeFiles/date_test.dir/depend:
	cd /home/anonymous/CS/programming_list/programming/object/oop_project/test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anonymous/CS/programming_list/programming/object/oop_project/test /home/anonymous/CS/programming_list/programming/object/oop_project/test /home/anonymous/CS/programming_list/programming/object/oop_project/test/build /home/anonymous/CS/programming_list/programming/object/oop_project/test/build /home/anonymous/CS/programming_list/programming/object/oop_project/test/build/CMakeFiles/date_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/date_test.dir/depend

