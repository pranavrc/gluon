# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

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
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sacha/programmation/gluon/examples/kcl/tutorial1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sacha/programmation/gluon/examples/kcl/tutorial1/build

# Include any dependencies generated for this target.
include CMakeFiles/kcl_tutorial1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kcl_tutorial1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kcl_tutorial1.dir/flags.make

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o: CMakeFiles/kcl_tutorial1.dir/flags.make
CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o: kcl_tutorial1_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o -c /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/kcl_tutorial1_automoc.cpp

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/kcl_tutorial1_automoc.cpp > CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.i

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/kcl_tutorial1_automoc.cpp -o CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.s

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.requires:
.PHONY : CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.requires

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.provides: CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.requires
	$(MAKE) -f CMakeFiles/kcl_tutorial1.dir/build.make CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.provides.build
.PHONY : CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.provides

CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.provides.build: CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o
.PHONY : CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.provides.build

CMakeFiles/kcl_tutorial1.dir/main.o: CMakeFiles/kcl_tutorial1.dir/flags.make
CMakeFiles/kcl_tutorial1.dir/main.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/kcl_tutorial1.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/kcl_tutorial1.dir/main.o -c /home/sacha/programmation/gluon/examples/kcl/tutorial1/main.cpp

CMakeFiles/kcl_tutorial1.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kcl_tutorial1.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sacha/programmation/gluon/examples/kcl/tutorial1/main.cpp > CMakeFiles/kcl_tutorial1.dir/main.i

CMakeFiles/kcl_tutorial1.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kcl_tutorial1.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sacha/programmation/gluon/examples/kcl/tutorial1/main.cpp -o CMakeFiles/kcl_tutorial1.dir/main.s

CMakeFiles/kcl_tutorial1.dir/main.o.requires:
.PHONY : CMakeFiles/kcl_tutorial1.dir/main.o.requires

CMakeFiles/kcl_tutorial1.dir/main.o.provides: CMakeFiles/kcl_tutorial1.dir/main.o.requires
	$(MAKE) -f CMakeFiles/kcl_tutorial1.dir/build.make CMakeFiles/kcl_tutorial1.dir/main.o.provides.build
.PHONY : CMakeFiles/kcl_tutorial1.dir/main.o.provides

CMakeFiles/kcl_tutorial1.dir/main.o.provides.build: CMakeFiles/kcl_tutorial1.dir/main.o
.PHONY : CMakeFiles/kcl_tutorial1.dir/main.o.provides.build

# Object files for target kcl_tutorial1
kcl_tutorial1_OBJECTS = \
"CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o" \
"CMakeFiles/kcl_tutorial1.dir/main.o"

# External object files for target kcl_tutorial1
kcl_tutorial1_EXTERNAL_OBJECTS =

kcl_tutorial1: CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o
kcl_tutorial1: CMakeFiles/kcl_tutorial1.dir/main.o
kcl_tutorial1: /usr/lib/libgluon.so
kcl_tutorial1: CMakeFiles/kcl_tutorial1.dir/build.make
kcl_tutorial1: CMakeFiles/kcl_tutorial1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable kcl_tutorial1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kcl_tutorial1.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D_filename=/home/sacha/programmation/gluon/examples/kcl/tutorial1/build/kcl_tutorial1.shell -D_library_path_variable=LD_LIBRARY_PATH -D_ld_library_path="/home/sacha/programmation/gluon/examples/kcl/tutorial1/build/lib/./:/usr/local/lib:/usr/lib:/usr/lib" -D_executable=/home/sacha/programmation/gluon/examples/kcl/tutorial1/build/kcl_tutorial1 -P /usr/share/kde4/apps/cmake/modules/kde4_exec_via_sh.cmake

# Rule to build all files generated by this target.
CMakeFiles/kcl_tutorial1.dir/build: kcl_tutorial1
.PHONY : CMakeFiles/kcl_tutorial1.dir/build

CMakeFiles/kcl_tutorial1.dir/requires: CMakeFiles/kcl_tutorial1.dir/kcl_tutorial1_automoc.o.requires
CMakeFiles/kcl_tutorial1.dir/requires: CMakeFiles/kcl_tutorial1.dir/main.o.requires
.PHONY : CMakeFiles/kcl_tutorial1.dir/requires

CMakeFiles/kcl_tutorial1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kcl_tutorial1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kcl_tutorial1.dir/clean

CMakeFiles/kcl_tutorial1.dir/depend:
	cd /home/sacha/programmation/gluon/examples/kcl/tutorial1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sacha/programmation/gluon/examples/kcl/tutorial1 /home/sacha/programmation/gluon/examples/kcl/tutorial1 /home/sacha/programmation/gluon/examples/kcl/tutorial1/build /home/sacha/programmation/gluon/examples/kcl/tutorial1/build /home/sacha/programmation/gluon/examples/kcl/tutorial1/build/CMakeFiles/kcl_tutorial1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kcl_tutorial1.dir/depend
