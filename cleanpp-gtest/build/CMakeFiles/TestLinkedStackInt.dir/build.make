# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build

# Include any dependencies generated for this target.
include CMakeFiles/TestLinkedStackInt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestLinkedStackInt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestLinkedStackInt.dir/flags.make

CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o: CMakeFiles/TestLinkedStackInt.dir/flags.make
CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o: ../TestLinkedStackInt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o -c /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/TestLinkedStackInt.cpp

CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/TestLinkedStackInt.cpp > CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.i

CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/TestLinkedStackInt.cpp -o CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.s

# Object files for target TestLinkedStackInt
TestLinkedStackInt_OBJECTS = \
"CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o"

# External object files for target TestLinkedStackInt
TestLinkedStackInt_EXTERNAL_OBJECTS =

TestLinkedStackInt: CMakeFiles/TestLinkedStackInt.dir/TestLinkedStackInt.cpp.o
TestLinkedStackInt: CMakeFiles/TestLinkedStackInt.dir/build.make
TestLinkedStackInt: lib/libgtest_main.a
TestLinkedStackInt: lib/libgtest.a
TestLinkedStackInt: CMakeFiles/TestLinkedStackInt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestLinkedStackInt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestLinkedStackInt.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=TestLinkedStackInt -D TEST_EXECUTABLE=/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/TestLinkedStackInt -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=TestLinkedStackInt_TESTS -D CTEST_FILE=/home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/TestLinkedStackInt[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -P /usr/share/cmake-3.16/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/TestLinkedStackInt.dir/build: TestLinkedStackInt

.PHONY : CMakeFiles/TestLinkedStackInt.dir/build

CMakeFiles/TestLinkedStackInt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestLinkedStackInt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestLinkedStackInt.dir/clean

CMakeFiles/TestLinkedStackInt.dir/depend:
	cd /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build /home/wwjanning400m/forked_cleanpplib_linux/cleanpplib/cleanpp-gtest/build/CMakeFiles/TestLinkedStackInt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestLinkedStackInt.dir/depend

