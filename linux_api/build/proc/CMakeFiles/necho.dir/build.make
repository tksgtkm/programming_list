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
include proc/CMakeFiles/necho.dir/depend.make

# Include the progress variables for this target.
include proc/CMakeFiles/necho.dir/progress.make

# Include the compile flags for this target's objects.
include proc/CMakeFiles/necho.dir/flags.make

proc/CMakeFiles/necho.dir/necho.c.o: proc/CMakeFiles/necho.dir/flags.make
proc/CMakeFiles/necho.dir/necho.c.o: ../proc/necho.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/onimas/C_Unix/project/linux_api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object proc/CMakeFiles/necho.dir/necho.c.o"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/necho.dir/necho.c.o   -c /home/onimas/C_Unix/project/linux_api/proc/necho.c

proc/CMakeFiles/necho.dir/necho.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/necho.dir/necho.c.i"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/onimas/C_Unix/project/linux_api/proc/necho.c > CMakeFiles/necho.dir/necho.c.i

proc/CMakeFiles/necho.dir/necho.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/necho.dir/necho.c.s"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/onimas/C_Unix/project/linux_api/proc/necho.c -o CMakeFiles/necho.dir/necho.c.s

# Object files for target necho
necho_OBJECTS = \
"CMakeFiles/necho.dir/necho.c.o"

# External object files for target necho
necho_EXTERNAL_OBJECTS =

bin/necho: proc/CMakeFiles/necho.dir/necho.c.o
bin/necho: proc/CMakeFiles/necho.dir/build.make
bin/necho: lib/liblib.a
bin/necho: proc/CMakeFiles/necho.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/onimas/C_Unix/project/linux_api/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/necho"
	cd /home/onimas/C_Unix/project/linux_api/build/proc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/necho.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proc/CMakeFiles/necho.dir/build: bin/necho

.PHONY : proc/CMakeFiles/necho.dir/build

proc/CMakeFiles/necho.dir/clean:
	cd /home/onimas/C_Unix/project/linux_api/build/proc && $(CMAKE_COMMAND) -P CMakeFiles/necho.dir/cmake_clean.cmake
.PHONY : proc/CMakeFiles/necho.dir/clean

proc/CMakeFiles/necho.dir/depend:
	cd /home/onimas/C_Unix/project/linux_api/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/onimas/C_Unix/project/linux_api /home/onimas/C_Unix/project/linux_api/proc /home/onimas/C_Unix/project/linux_api/build /home/onimas/C_Unix/project/linux_api/build/proc /home/onimas/C_Unix/project/linux_api/build/proc/CMakeFiles/necho.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proc/CMakeFiles/necho.dir/depend

