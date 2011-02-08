# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nick/twitSpam/CMakeFiles /home/nick/twitSpam/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nick/twitSpam/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named curlURL

# Build rule for target.
curlURL: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 curlURL
.PHONY : curlURL

# fast build rule for target.
curlURL/fast:
	$(MAKE) -f src/CMakeFiles/curlURL.dir/build.make src/CMakeFiles/curlURL.dir/build
.PHONY : curlURL/fast

#=============================================================================
# Target rules for targets named ptTwitSpam

# Build rule for target.
ptTwitSpam: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ptTwitSpam
.PHONY : ptTwitSpam

# fast build rule for target.
ptTwitSpam/fast:
	$(MAKE) -f src/CMakeFiles/ptTwitSpam.dir/build.make src/CMakeFiles/ptTwitSpam.dir/build
.PHONY : ptTwitSpam/fast

#=============================================================================
# Target rules for targets named spamCheck

# Build rule for target.
spamCheck: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 spamCheck
.PHONY : spamCheck

# fast build rule for target.
spamCheck/fast:
	$(MAKE) -f src/CMakeFiles/spamCheck.dir/build.make src/CMakeFiles/spamCheck.dir/build
.PHONY : spamCheck/fast

#=============================================================================
# Target rules for targets named twitSpam

# Build rule for target.
twitSpam: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 twitSpam
.PHONY : twitSpam

# fast build rule for target.
twitSpam/fast:
	$(MAKE) -f src/CMakeFiles/twitSpam.dir/build.make src/CMakeFiles/twitSpam.dir/build
.PHONY : twitSpam/fast

#=============================================================================
# Target rules for targets named userData

# Build rule for target.
userData: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 userData
.PHONY : userData

# fast build rule for target.
userData/fast:
	$(MAKE) -f src/CMakeFiles/userData.dir/build.make src/CMakeFiles/userData.dir/build
.PHONY : userData/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... curlURL"
	@echo "... ptTwitSpam"
	@echo "... spamCheck"
	@echo "... twitSpam"
	@echo "... userData"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

