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
CMAKE_SOURCE_DIR = /home/anonymous/CS/programming_list/programming/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anonymous/CS/programming_list/programming/cpp/build

# Include any dependencies generated for this target.
include CMakeFiles/array3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/array3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/array3.dir/flags.make

CMakeFiles/array3.dir/array3.cc.o: CMakeFiles/array3.dir/flags.make
CMakeFiles/array3.dir/array3.cc.o: ../array3.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anonymous/CS/programming_list/programming/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/array3.dir/array3.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/array3.dir/array3.cc.o -c /home/anonymous/CS/programming_list/programming/cpp/array3.cc

CMakeFiles/array3.dir/array3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/array3.dir/array3.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anonymous/CS/programming_list/programming/cpp/array3.cc > CMakeFiles/array3.dir/array3.cc.i

CMakeFiles/array3.dir/array3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/array3.dir/array3.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anonymous/CS/programming_list/programming/cpp/array3.cc -o CMakeFiles/array3.dir/array3.cc.s

# Object files for target array3
array3_OBJECTS = \
"CMakeFiles/array3.dir/array3.cc.o"

# External object files for target array3
array3_EXTERNAL_OBJECTS =

array3: CMakeFiles/array3.dir/array3.cc.o
array3: CMakeFiles/array3.dir/build.make
array3: CMakeFiles/array3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anonymous/CS/programming_list/programming/cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable array3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/array3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/array3.dir/build: array3

.PHONY : CMakeFiles/array3.dir/build

CMakeFiles/array3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/array3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/array3.dir/clean

CMakeFiles/array3.dir/depend:
	cd /home/anonymous/CS/programming_list/programming/cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anonymous/CS/programming_list/programming/cpp /home/anonymous/CS/programming_list/programming/cpp /home/anonymous/CS/programming_list/programming/cpp/build /home/anonymous/CS/programming_list/programming/cpp/build /home/anonymous/CS/programming_list/programming/cpp/build/CMakeFiles/array3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/array3.dir/depend

