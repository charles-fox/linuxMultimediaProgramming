# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/charles/Dropbox/test/cl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/charles/Dropbox/test/cl

# Include any dependencies generated for this target.
include CMakeFiles/go.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/go.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/go.dir/flags.make

CMakeFiles/go.dir/go.cpp.o: CMakeFiles/go.dir/flags.make
CMakeFiles/go.dir/go.cpp.o: go.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charles/Dropbox/test/cl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/go.dir/go.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/go.dir/go.cpp.o -c /home/charles/Dropbox/test/cl/go.cpp

CMakeFiles/go.dir/go.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/go.dir/go.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charles/Dropbox/test/cl/go.cpp > CMakeFiles/go.dir/go.cpp.i

CMakeFiles/go.dir/go.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/go.dir/go.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charles/Dropbox/test/cl/go.cpp -o CMakeFiles/go.dir/go.cpp.s

CMakeFiles/go.dir/go.cpp.o.requires:

.PHONY : CMakeFiles/go.dir/go.cpp.o.requires

CMakeFiles/go.dir/go.cpp.o.provides: CMakeFiles/go.dir/go.cpp.o.requires
	$(MAKE) -f CMakeFiles/go.dir/build.make CMakeFiles/go.dir/go.cpp.o.provides.build
.PHONY : CMakeFiles/go.dir/go.cpp.o.provides

CMakeFiles/go.dir/go.cpp.o.provides.build: CMakeFiles/go.dir/go.cpp.o


# Object files for target go
go_OBJECTS = \
"CMakeFiles/go.dir/go.cpp.o"

# External object files for target go
go_EXTERNAL_OBJECTS =

go: CMakeFiles/go.dir/go.cpp.o
go: CMakeFiles/go.dir/build.make
go: /usr/lib/x86_64-linux-gnu/libOpenCL.so
go: CMakeFiles/go.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/charles/Dropbox/test/cl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable go"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/go.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/go.dir/build: go

.PHONY : CMakeFiles/go.dir/build

CMakeFiles/go.dir/requires: CMakeFiles/go.dir/go.cpp.o.requires

.PHONY : CMakeFiles/go.dir/requires

CMakeFiles/go.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/go.dir/cmake_clean.cmake
.PHONY : CMakeFiles/go.dir/clean

CMakeFiles/go.dir/depend:
	cd /home/charles/Dropbox/test/cl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/charles/Dropbox/test/cl /home/charles/Dropbox/test/cl /home/charles/Dropbox/test/cl /home/charles/Dropbox/test/cl /home/charles/Dropbox/test/cl/CMakeFiles/go.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/go.dir/depend

