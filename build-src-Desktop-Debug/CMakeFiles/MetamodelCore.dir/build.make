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
CMAKE_SOURCE_DIR = /home/aferrand/dev/perso/Abject-Language/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/MetamodelCore.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MetamodelCore.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MetamodelCore.dir/flags.make

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/metamodel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/metamodel.cc

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/metamodel.cc > CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/metamodel.cc -o CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/module.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/module.cc

CMakeFiles/MetamodelCore.dir/metamodel/module.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/module.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/module.cc > CMakeFiles/MetamodelCore.dir/metamodel/module.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/module.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/module.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/module.cc -o CMakeFiles/MetamodelCore.dir/metamodel/module.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/modular.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/modular.cc

CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/modular.cc > CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/modular.cc -o CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/types.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/types.cc

CMakeFiles/MetamodelCore.dir/metamodel/types.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/types.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/types.cc > CMakeFiles/MetamodelCore.dir/metamodel/types.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/types.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/types.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/types.cc -o CMakeFiles/MetamodelCore.dir/metamodel/types.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/cfg.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/cfg.cc

CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/cfg.cc > CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/cfg.cc -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/instructions.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/instructions.cc

CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/instructions.cc > CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/instructions.cc -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o


CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o: CMakeFiles/MetamodelCore.dir/flags.make
CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o: /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/identifier.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o -c /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/identifier.cc

CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/identifier.cc > CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.i

CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aferrand/dev/perso/Abject-Language/src/metamodel/cfg/identifier.cc -o CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.s

CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.requires:

.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.requires

CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.provides: CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.requires
	$(MAKE) -f CMakeFiles/MetamodelCore.dir/build.make CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.provides.build
.PHONY : CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.provides

CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.provides.build: CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o


# Object files for target MetamodelCore
MetamodelCore_OBJECTS = \
"CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o" \
"CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o"

# External object files for target MetamodelCore
MetamodelCore_EXTERNAL_OBJECTS =

libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/build.make
libMetamodelCore.a: CMakeFiles/MetamodelCore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libMetamodelCore.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MetamodelCore.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MetamodelCore.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MetamodelCore.dir/build: libMetamodelCore.a

.PHONY : CMakeFiles/MetamodelCore.dir/build

CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/metamodel.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/module.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/modular.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/types.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/cfg/cfg.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/cfg/instructions.cc.o.requires
CMakeFiles/MetamodelCore.dir/requires: CMakeFiles/MetamodelCore.dir/metamodel/cfg/identifier.cc.o.requires

.PHONY : CMakeFiles/MetamodelCore.dir/requires

CMakeFiles/MetamodelCore.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MetamodelCore.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MetamodelCore.dir/clean

CMakeFiles/MetamodelCore.dir/depend:
	cd /home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aferrand/dev/perso/Abject-Language/src /home/aferrand/dev/perso/Abject-Language/src /home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug /home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug /home/aferrand/dev/perso/Abject-Language/build-src-Desktop-Debug/CMakeFiles/MetamodelCore.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MetamodelCore.dir/depend

