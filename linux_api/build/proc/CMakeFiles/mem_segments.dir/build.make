# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/onimas/C_Unix/project/linux_api

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/onimas/C_Unix/project/linux_api/build

# Include any dependencies generated for this target.
include proc/CMakeFiles/mem_segments.dir/depend.make

# Include the progress variables for this target.
include proc/CMakeFiles/mem_segments.dir/progress.make

# Include the compile flags for this target's objects.
include proc/CMakeFiles/mem_segments.dir/flags.make

proc/CMakeFiles/mem_segments.dir/mem_segments.c.o: proc/CMakeFiles/mem_segments.dir/flags.make
proc/CMakeFiles/mem_segments.dir/mem_segments.c.o: ../proc/mem_segments.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onimas/C_Unix/project/linux_api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object proc/CMakeFiles/mem_segments.dir/mem_segments.c.o"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mem_segments.dir/mem_segments.c.o   -c /home/onimas/C_Unix/project/linux_api/proc/mem_segments.c

proc/CMakeFiles/mem_segments.dir/mem_segments.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mem_segments.dir/mem_segments.c.i"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/onimas/C_Unix/project/linux_api/proc/mem_segments.c > CMakeFiles/mem_segments.dir/mem_segments.c.i

proc/CMakeFiles/mem_segments.dir/mem_segments.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mem_segments.dir/mem_segments.c.s"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/onimas/C_Unix/project/linux_api/proc/mem_segments.c -o CMakeFiles/mem_segments.dir/mem_segments.c.s

# Object files for target mem_segments
mem_segments_OBJECTS = \
"CMakeFiles/mem_segments.dir/mem_segments.c.o"

# External object files for target mem_segments
mem_segments_EXTERNAL_OBJECTS =

bin/mem_segments: proc/CMakeFiles/mem_segments.dir/mem_segments.c.o
bin/mem_segments: proc/CMakeFiles/mem_segments.dir/build.make
bin/mem_segments: lib/liblib.a
bin/mem_segments: proc/CMakeFiles/mem_segments.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onimas/C_Unix/project/linux_api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/mem_segments"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mem_segments.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proc/CMakeFiles/mem_segments.dir/build: bin/mem_segments

.PHONY : proc/CMakeFiles/mem_segments.dir/build

proc/CMakeFiles/mem_segments.dir/clean:
	cd /home/onimas/C_Unix/project/linux_api/build/proc && $(CMAKE_COMMAND) -P CMakeFiles/mem_segments.dir/cmake_clean.cmake
.PHONY : proc/CMakeFiles/mem_segments.dir/clean

proc/CMakeFiles/mem_segments.dir/depend:
	cd /home/onimas/C_Unix/project/linux_api/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onimas/C_Unix/project/linux_api /home/onimas/C_Unix/project/linux_api/proc /home/onimas/C_Unix/project/linux_api/build /home/onimas/C_Unix/project/linux_api/build/proc /home/onimas/C_Unix/project/linux_api/build/proc/CMakeFiles/mem_segments.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proc/CMakeFiles/mem_segments.dir/depend

