# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/piotr/Piotr/IGF/libcloudphxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piotr/Piotr/IGF/libcloudphxx/build

# Include any dependencies generated for this target.
include tests/particles/CMakeFiles/test_particles.dir/depend.make

# Include the progress variables for this target.
include tests/particles/CMakeFiles/test_particles.dir/progress.make

# Include the compile flags for this target's objects.
include tests/particles/CMakeFiles/test_particles.dir/flags.make

tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.o: tests/particles/CMakeFiles/test_particles.dir/flags.make
tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.o: ../tests/particles/tests_particles.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/piotr/Piotr/IGF/libcloudphxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.o"
	cd /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_particles.dir/tests_particles.cpp.o -c /home/piotr/Piotr/IGF/libcloudphxx/tests/particles/tests_particles.cpp

tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_particles.dir/tests_particles.cpp.i"
	cd /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/piotr/Piotr/IGF/libcloudphxx/tests/particles/tests_particles.cpp > CMakeFiles/test_particles.dir/tests_particles.cpp.i

tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_particles.dir/tests_particles.cpp.s"
	cd /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/piotr/Piotr/IGF/libcloudphxx/tests/particles/tests_particles.cpp -o CMakeFiles/test_particles.dir/tests_particles.cpp.s

# Object files for target test_particles
test_particles_OBJECTS = \
"CMakeFiles/test_particles.dir/tests_particles.cpp.o"

# External object files for target test_particles
test_particles_EXTERNAL_OBJECTS =

tests/particles/test_particles: tests/particles/CMakeFiles/test_particles.dir/tests_particles.cpp.o
tests/particles/test_particles: tests/particles/CMakeFiles/test_particles.dir/build.make
tests/particles/test_particles: libcloudphxx_lgrngn.so
tests/particles/test_particles: /usr/lib/gcc/x86_64-linux-gnu/7/libgomp.so
tests/particles/test_particles: /usr/lib/x86_64-linux-gnu/libpthread.so
tests/particles/test_particles: tests/particles/CMakeFiles/test_particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/piotr/Piotr/IGF/libcloudphxx/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_particles"
	cd /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_particles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/particles/CMakeFiles/test_particles.dir/build: tests/particles/test_particles

.PHONY : tests/particles/CMakeFiles/test_particles.dir/build

tests/particles/CMakeFiles/test_particles.dir/clean:
	cd /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles && $(CMAKE_COMMAND) -P CMakeFiles/test_particles.dir/cmake_clean.cmake
.PHONY : tests/particles/CMakeFiles/test_particles.dir/clean

tests/particles/CMakeFiles/test_particles.dir/depend:
	cd /home/piotr/Piotr/IGF/libcloudphxx/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piotr/Piotr/IGF/libcloudphxx /home/piotr/Piotr/IGF/libcloudphxx/tests/particles /home/piotr/Piotr/IGF/libcloudphxx/build /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles /home/piotr/Piotr/IGF/libcloudphxx/build/tests/particles/CMakeFiles/test_particles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/particles/CMakeFiles/test_particles.dir/depend

