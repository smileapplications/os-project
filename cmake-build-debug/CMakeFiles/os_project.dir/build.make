# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/carde/Documents/Workspace/os_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/carde/Documents/Workspace/os_project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/os_project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/os_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/os_project.dir/flags.make

CMakeFiles/os_project.dir/main.c.o: CMakeFiles/os_project.dir/flags.make
CMakeFiles/os_project.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/carde/Documents/Workspace/os_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/os_project.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/os_project.dir/main.c.o   -c /Users/carde/Documents/Workspace/os_project/main.c

CMakeFiles/os_project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/os_project.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/carde/Documents/Workspace/os_project/main.c > CMakeFiles/os_project.dir/main.c.i

CMakeFiles/os_project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/os_project.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/carde/Documents/Workspace/os_project/main.c -o CMakeFiles/os_project.dir/main.c.s

CMakeFiles/os_project.dir/main.c.o.requires:

.PHONY : CMakeFiles/os_project.dir/main.c.o.requires

CMakeFiles/os_project.dir/main.c.o.provides: CMakeFiles/os_project.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/os_project.dir/build.make CMakeFiles/os_project.dir/main.c.o.provides.build
.PHONY : CMakeFiles/os_project.dir/main.c.o.provides

CMakeFiles/os_project.dir/main.c.o.provides.build: CMakeFiles/os_project.dir/main.c.o


# Object files for target os_project
os_project_OBJECTS = \
"CMakeFiles/os_project.dir/main.c.o"

# External object files for target os_project
os_project_EXTERNAL_OBJECTS =

os_project: CMakeFiles/os_project.dir/main.c.o
os_project: CMakeFiles/os_project.dir/build.make
os_project: CMakeFiles/os_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/carde/Documents/Workspace/os_project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable os_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/os_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/os_project.dir/build: os_project

.PHONY : CMakeFiles/os_project.dir/build

CMakeFiles/os_project.dir/requires: CMakeFiles/os_project.dir/main.c.o.requires

.PHONY : CMakeFiles/os_project.dir/requires

CMakeFiles/os_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/os_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/os_project.dir/clean

CMakeFiles/os_project.dir/depend:
	cd /Users/carde/Documents/Workspace/os_project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/carde/Documents/Workspace/os_project /Users/carde/Documents/Workspace/os_project /Users/carde/Documents/Workspace/os_project/cmake-build-debug /Users/carde/Documents/Workspace/os_project/cmake-build-debug /Users/carde/Documents/Workspace/os_project/cmake-build-debug/CMakeFiles/os_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/os_project.dir/depend
