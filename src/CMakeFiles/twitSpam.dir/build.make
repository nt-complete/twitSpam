# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nick/twitSpam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nick/twitSpam

# Include any dependencies generated for this target.
include src/CMakeFiles/twitSpam.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/twitSpam.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/twitSpam.dir/flags.make

src/CMakeFiles/twitSpam.dir/twitSpam.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/twitSpam.o: src/twitSpam.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/twitSpam.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/twitSpam.o -c /home/nick/twitSpam/src/twitSpam.cpp

src/CMakeFiles/twitSpam.dir/twitSpam.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/twitSpam.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/twitSpam.cpp > CMakeFiles/twitSpam.dir/twitSpam.i

src/CMakeFiles/twitSpam.dir/twitSpam.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/twitSpam.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/twitSpam.cpp -o CMakeFiles/twitSpam.dir/twitSpam.s

src/CMakeFiles/twitSpam.dir/twitSpam.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/twitSpam.o.requires

src/CMakeFiles/twitSpam.dir/twitSpam.o.provides: src/CMakeFiles/twitSpam.dir/twitSpam.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/twitSpam.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/twitSpam.o.provides

src/CMakeFiles/twitSpam.dir/twitSpam.o.provides.build: src/CMakeFiles/twitSpam.dir/twitSpam.o
.PHONY : src/CMakeFiles/twitSpam.dir/twitSpam.o.provides.build

src/CMakeFiles/twitSpam.dir/user.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/user.o: src/user.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/user.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/user.o -c /home/nick/twitSpam/src/user.cpp

src/CMakeFiles/twitSpam.dir/user.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/user.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/user.cpp > CMakeFiles/twitSpam.dir/user.i

src/CMakeFiles/twitSpam.dir/user.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/user.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/user.cpp -o CMakeFiles/twitSpam.dir/user.s

src/CMakeFiles/twitSpam.dir/user.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/user.o.requires

src/CMakeFiles/twitSpam.dir/user.o.provides: src/CMakeFiles/twitSpam.dir/user.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/user.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/user.o.provides

src/CMakeFiles/twitSpam.dir/user.o.provides.build: src/CMakeFiles/twitSpam.dir/user.o
.PHONY : src/CMakeFiles/twitSpam.dir/user.o.provides.build

src/CMakeFiles/twitSpam.dir/tinystr.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/tinystr.o: src/tinystr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/tinystr.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/tinystr.o -c /home/nick/twitSpam/src/tinystr.cpp

src/CMakeFiles/twitSpam.dir/tinystr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/tinystr.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/tinystr.cpp > CMakeFiles/twitSpam.dir/tinystr.i

src/CMakeFiles/twitSpam.dir/tinystr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/tinystr.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/tinystr.cpp -o CMakeFiles/twitSpam.dir/tinystr.s

src/CMakeFiles/twitSpam.dir/tinystr.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/tinystr.o.requires

src/CMakeFiles/twitSpam.dir/tinystr.o.provides: src/CMakeFiles/twitSpam.dir/tinystr.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/tinystr.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/tinystr.o.provides

src/CMakeFiles/twitSpam.dir/tinystr.o.provides.build: src/CMakeFiles/twitSpam.dir/tinystr.o
.PHONY : src/CMakeFiles/twitSpam.dir/tinystr.o.provides.build

src/CMakeFiles/twitSpam.dir/tinyxml.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/tinyxml.o: src/tinyxml.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/tinyxml.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/tinyxml.o -c /home/nick/twitSpam/src/tinyxml.cpp

src/CMakeFiles/twitSpam.dir/tinyxml.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/tinyxml.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/tinyxml.cpp > CMakeFiles/twitSpam.dir/tinyxml.i

src/CMakeFiles/twitSpam.dir/tinyxml.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/tinyxml.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/tinyxml.cpp -o CMakeFiles/twitSpam.dir/tinyxml.s

src/CMakeFiles/twitSpam.dir/tinyxml.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxml.o.requires

src/CMakeFiles/twitSpam.dir/tinyxml.o.provides: src/CMakeFiles/twitSpam.dir/tinyxml.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/tinyxml.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxml.o.provides

src/CMakeFiles/twitSpam.dir/tinyxml.o.provides.build: src/CMakeFiles/twitSpam.dir/tinyxml.o
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxml.o.provides.build

src/CMakeFiles/twitSpam.dir/tinyxmlerror.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/tinyxmlerror.o: src/tinyxmlerror.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/tinyxmlerror.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/tinyxmlerror.o -c /home/nick/twitSpam/src/tinyxmlerror.cpp

src/CMakeFiles/twitSpam.dir/tinyxmlerror.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/tinyxmlerror.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/tinyxmlerror.cpp > CMakeFiles/twitSpam.dir/tinyxmlerror.i

src/CMakeFiles/twitSpam.dir/tinyxmlerror.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/tinyxmlerror.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/tinyxmlerror.cpp -o CMakeFiles/twitSpam.dir/tinyxmlerror.s

src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.requires

src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.provides: src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.provides

src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.provides.build: src/CMakeFiles/twitSpam.dir/tinyxmlerror.o
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.provides.build

src/CMakeFiles/twitSpam.dir/tinyxmlparser.o: src/CMakeFiles/twitSpam.dir/flags.make
src/CMakeFiles/twitSpam.dir/tinyxmlparser.o: src/tinyxmlparser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/nick/twitSpam/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/twitSpam.dir/tinyxmlparser.o"
	cd /home/nick/twitSpam/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/twitSpam.dir/tinyxmlparser.o -c /home/nick/twitSpam/src/tinyxmlparser.cpp

src/CMakeFiles/twitSpam.dir/tinyxmlparser.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/twitSpam.dir/tinyxmlparser.i"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/nick/twitSpam/src/tinyxmlparser.cpp > CMakeFiles/twitSpam.dir/tinyxmlparser.i

src/CMakeFiles/twitSpam.dir/tinyxmlparser.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/twitSpam.dir/tinyxmlparser.s"
	cd /home/nick/twitSpam/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/nick/twitSpam/src/tinyxmlparser.cpp -o CMakeFiles/twitSpam.dir/tinyxmlparser.s

src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.requires:
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.requires

src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.provides: src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.requires
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.provides.build
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.provides

src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.provides.build: src/CMakeFiles/twitSpam.dir/tinyxmlparser.o
.PHONY : src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.provides.build

# Object files for target twitSpam
twitSpam_OBJECTS = \
"CMakeFiles/twitSpam.dir/twitSpam.o" \
"CMakeFiles/twitSpam.dir/user.o" \
"CMakeFiles/twitSpam.dir/tinystr.o" \
"CMakeFiles/twitSpam.dir/tinyxml.o" \
"CMakeFiles/twitSpam.dir/tinyxmlerror.o" \
"CMakeFiles/twitSpam.dir/tinyxmlparser.o"

# External object files for target twitSpam
twitSpam_EXTERNAL_OBJECTS =

src/twitSpam: src/CMakeFiles/twitSpam.dir/twitSpam.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/user.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/tinystr.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/tinyxml.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/tinyxmlerror.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/tinyxmlparser.o
src/twitSpam: src/CMakeFiles/twitSpam.dir/build.make
src/twitSpam: src/CMakeFiles/twitSpam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable twitSpam"
	cd /home/nick/twitSpam/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/twitSpam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/twitSpam.dir/build: src/twitSpam
.PHONY : src/CMakeFiles/twitSpam.dir/build

src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/twitSpam.o.requires
src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/user.o.requires
src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/tinystr.o.requires
src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/tinyxml.o.requires
src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/tinyxmlerror.o.requires
src/CMakeFiles/twitSpam.dir/requires: src/CMakeFiles/twitSpam.dir/tinyxmlparser.o.requires
.PHONY : src/CMakeFiles/twitSpam.dir/requires

src/CMakeFiles/twitSpam.dir/clean:
	cd /home/nick/twitSpam/src && $(CMAKE_COMMAND) -P CMakeFiles/twitSpam.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/twitSpam.dir/clean

src/CMakeFiles/twitSpam.dir/depend:
	cd /home/nick/twitSpam && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nick/twitSpam /home/nick/twitSpam/src /home/nick/twitSpam /home/nick/twitSpam/src /home/nick/twitSpam/src/CMakeFiles/twitSpam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/twitSpam.dir/depend

