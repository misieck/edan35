# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build"

# Include any dependencies generated for this target.
include src/core/CMakeFiles/bonobo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/core/CMakeFiles/bonobo.dir/compiler_depend.make

# Include the progress variables for this target.
include src/core/CMakeFiles/bonobo.dir/progress.make

# Include the compile flags for this target's objects.
include src/core/CMakeFiles/bonobo.dir/flags.make

src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o: ../src/core/Bonobo.cpp
src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o -MF CMakeFiles/bonobo.dir/Bonobo.cpp.o.d -o CMakeFiles/bonobo.dir/Bonobo.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Bonobo.cpp"

src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/Bonobo.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Bonobo.cpp" > CMakeFiles/bonobo.dir/Bonobo.cpp.i

src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/Bonobo.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Bonobo.cpp" -o CMakeFiles/bonobo.dir/Bonobo.cpp.s

src/core/CMakeFiles/bonobo.dir/helpers.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/helpers.cpp.o: ../src/core/helpers.cpp
src/core/CMakeFiles/bonobo.dir/helpers.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/core/CMakeFiles/bonobo.dir/helpers.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/helpers.cpp.o -MF CMakeFiles/bonobo.dir/helpers.cpp.o.d -o CMakeFiles/bonobo.dir/helpers.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/helpers.cpp"

src/core/CMakeFiles/bonobo.dir/helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/helpers.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/helpers.cpp" > CMakeFiles/bonobo.dir/helpers.cpp.i

src/core/CMakeFiles/bonobo.dir/helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/helpers.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/helpers.cpp" -o CMakeFiles/bonobo.dir/helpers.cpp.s

src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o: ../src/core/InputHandler.cpp
src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o -MF CMakeFiles/bonobo.dir/InputHandler.cpp.o.d -o CMakeFiles/bonobo.dir/InputHandler.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/InputHandler.cpp"

src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/InputHandler.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/InputHandler.cpp" > CMakeFiles/bonobo.dir/InputHandler.cpp.i

src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/InputHandler.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/InputHandler.cpp" -o CMakeFiles/bonobo.dir/InputHandler.cpp.s

src/core/CMakeFiles/bonobo.dir/Log.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/Log.cpp.o: ../src/core/Log.cpp
src/core/CMakeFiles/bonobo.dir/Log.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/core/CMakeFiles/bonobo.dir/Log.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/Log.cpp.o -MF CMakeFiles/bonobo.dir/Log.cpp.o.d -o CMakeFiles/bonobo.dir/Log.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Log.cpp"

src/core/CMakeFiles/bonobo.dir/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/Log.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Log.cpp" > CMakeFiles/bonobo.dir/Log.cpp.i

src/core/CMakeFiles/bonobo.dir/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/Log.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/Log.cpp" -o CMakeFiles/bonobo.dir/Log.cpp.s

src/core/CMakeFiles/bonobo.dir/LogView.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/LogView.cpp.o: ../src/core/LogView.cpp
src/core/CMakeFiles/bonobo.dir/LogView.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/core/CMakeFiles/bonobo.dir/LogView.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/LogView.cpp.o -MF CMakeFiles/bonobo.dir/LogView.cpp.o.d -o CMakeFiles/bonobo.dir/LogView.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/LogView.cpp"

src/core/CMakeFiles/bonobo.dir/LogView.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/LogView.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/LogView.cpp" > CMakeFiles/bonobo.dir/LogView.cpp.i

src/core/CMakeFiles/bonobo.dir/LogView.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/LogView.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/LogView.cpp" -o CMakeFiles/bonobo.dir/LogView.cpp.s

src/core/CMakeFiles/bonobo.dir/node.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/node.cpp.o: ../src/core/node.cpp
src/core/CMakeFiles/bonobo.dir/node.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/core/CMakeFiles/bonobo.dir/node.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/node.cpp.o -MF CMakeFiles/bonobo.dir/node.cpp.o.d -o CMakeFiles/bonobo.dir/node.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/node.cpp"

src/core/CMakeFiles/bonobo.dir/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/node.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/node.cpp" > CMakeFiles/bonobo.dir/node.cpp.i

src/core/CMakeFiles/bonobo.dir/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/node.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/node.cpp" -o CMakeFiles/bonobo.dir/node.cpp.s

src/core/CMakeFiles/bonobo.dir/opengl.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/opengl.cpp.o: ../src/core/opengl.cpp
src/core/CMakeFiles/bonobo.dir/opengl.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/core/CMakeFiles/bonobo.dir/opengl.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/opengl.cpp.o -MF CMakeFiles/bonobo.dir/opengl.cpp.o.d -o CMakeFiles/bonobo.dir/opengl.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/opengl.cpp"

src/core/CMakeFiles/bonobo.dir/opengl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/opengl.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/opengl.cpp" > CMakeFiles/bonobo.dir/opengl.cpp.i

src/core/CMakeFiles/bonobo.dir/opengl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/opengl.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/opengl.cpp" -o CMakeFiles/bonobo.dir/opengl.cpp.s

src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o: ../src/core/ShaderProgramManager.cpp
src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o -MF CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o.d -o CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/ShaderProgramManager.cpp"

src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/ShaderProgramManager.cpp" > CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.i

src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/ShaderProgramManager.cpp" -o CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.s

src/core/CMakeFiles/bonobo.dir/various.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/various.cpp.o: ../src/core/various.cpp
src/core/CMakeFiles/bonobo.dir/various.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/core/CMakeFiles/bonobo.dir/various.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/various.cpp.o -MF CMakeFiles/bonobo.dir/various.cpp.o.d -o CMakeFiles/bonobo.dir/various.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/various.cpp"

src/core/CMakeFiles/bonobo.dir/various.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/various.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/various.cpp" > CMakeFiles/bonobo.dir/various.cpp.i

src/core/CMakeFiles/bonobo.dir/various.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/various.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/various.cpp" -o CMakeFiles/bonobo.dir/various.cpp.s

src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o: ../src/core/WindowManager.cpp
src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o -MF CMakeFiles/bonobo.dir/WindowManager.cpp.o.d -o CMakeFiles/bonobo.dir/WindowManager.cpp.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/WindowManager.cpp"

src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bonobo.dir/WindowManager.cpp.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/WindowManager.cpp" > CMakeFiles/bonobo.dir/WindowManager.cpp.i

src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bonobo.dir/WindowManager.cpp.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/WindowManager.cpp" -o CMakeFiles/bonobo.dir/WindowManager.cpp.s

src/core/CMakeFiles/bonobo.dir/stb_impl.c.o: src/core/CMakeFiles/bonobo.dir/flags.make
src/core/CMakeFiles/bonobo.dir/stb_impl.c.o: ../src/core/stb_impl.c
src/core/CMakeFiles/bonobo.dir/stb_impl.c.o: src/core/CMakeFiles/bonobo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building C object src/core/CMakeFiles/bonobo.dir/stb_impl.c.o"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/core/CMakeFiles/bonobo.dir/stb_impl.c.o -MF CMakeFiles/bonobo.dir/stb_impl.c.o.d -o CMakeFiles/bonobo.dir/stb_impl.c.o -c "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/stb_impl.c"

src/core/CMakeFiles/bonobo.dir/stb_impl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bonobo.dir/stb_impl.c.i"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/stb_impl.c" > CMakeFiles/bonobo.dir/stb_impl.c.i

src/core/CMakeFiles/bonobo.dir/stb_impl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bonobo.dir/stb_impl.c.s"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core/stb_impl.c" -o CMakeFiles/bonobo.dir/stb_impl.c.s

# Object files for target bonobo
bonobo_OBJECTS = \
"CMakeFiles/bonobo.dir/Bonobo.cpp.o" \
"CMakeFiles/bonobo.dir/helpers.cpp.o" \
"CMakeFiles/bonobo.dir/InputHandler.cpp.o" \
"CMakeFiles/bonobo.dir/Log.cpp.o" \
"CMakeFiles/bonobo.dir/LogView.cpp.o" \
"CMakeFiles/bonobo.dir/node.cpp.o" \
"CMakeFiles/bonobo.dir/opengl.cpp.o" \
"CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o" \
"CMakeFiles/bonobo.dir/various.cpp.o" \
"CMakeFiles/bonobo.dir/WindowManager.cpp.o" \
"CMakeFiles/bonobo.dir/stb_impl.c.o"

# External object files for target bonobo
bonobo_EXTERNAL_OBJECTS =

src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/Bonobo.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/helpers.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/InputHandler.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/Log.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/LogView.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/node.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/opengl.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/ShaderProgramManager.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/various.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/WindowManager.cpp.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/stb_impl.c.o
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/build.make
src/core/libbonobo.a: src/core/CMakeFiles/bonobo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libbonobo.a"
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && $(CMAKE_COMMAND) -P CMakeFiles/bonobo.dir/cmake_clean_target.cmake
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bonobo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/core/CMakeFiles/bonobo.dir/build: src/core/libbonobo.a
.PHONY : src/core/CMakeFiles/bonobo.dir/build

src/core/CMakeFiles/bonobo.dir/clean:
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" && $(CMAKE_COMMAND) -P CMakeFiles/bonobo.dir/cmake_clean.cmake
.PHONY : src/core/CMakeFiles/bonobo.dir/clean

src/core/CMakeFiles/bonobo.dir/depend:
	cd "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master" "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/src/core" "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build" "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core" "/home/pedro/Desktop/Faculdade_Ubuntu/Computer graphics/CG_Labs-master/Build/src/core/CMakeFiles/bonobo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/core/CMakeFiles/bonobo.dir/depend

