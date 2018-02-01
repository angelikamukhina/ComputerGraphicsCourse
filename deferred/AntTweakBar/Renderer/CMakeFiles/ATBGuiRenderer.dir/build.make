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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar

# Include any dependencies generated for this target.
include Renderer/CMakeFiles/ATBGuiRenderer.dir/depend.make

# Include the progress variables for this target.
include Renderer/CMakeFiles/ATBGuiRenderer.dir/progress.make

# Include the compile flags for this target's objects.
include Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make

Renderer/Dummy: Renderer/compile/TwDirect3D11.hlsl
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Dummy"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/local/bin/cmake -E touch Dummy

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o: Renderer/compile/TwPrecomp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwPrecomp.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwPrecomp.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwPrecomp.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o: Renderer/compile/TwColors.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwColors.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwColors.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwColors.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o: Renderer/compile/TwFonts.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwFonts.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwFonts.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwFonts.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o: Renderer/compile/TwGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwGraph.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwGraph.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwGraph.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o: Renderer/compile/TwOpenGL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGL.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGL.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGL.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o: Renderer/compile/LoadOGL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGL.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGL.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGL.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o: Renderer/compile/TwOpenGLCore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGLCore.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGLCore.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwOpenGLCore.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o: Renderer/compile/LoadOGLCore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGLCore.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGLCore.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/LoadOGLCore.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o: Renderer/compile/TwDirect3D9.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D9.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D9.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D9.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o: Renderer/compile/TwDirect3D10.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D10.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D10.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D10.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o


Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o: Renderer/CMakeFiles/ATBGuiRenderer.dir/flags.make
Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o: Renderer/compile/TwDirect3D11.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o -c /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D11.cpp

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.i"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D11.cpp > CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.i

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.s"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/compile/TwDirect3D11.cpp -o CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.s

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.requires:

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.provides: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.requires
	$(MAKE) -f Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.provides.build
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.provides

Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.provides.build: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o


# Object files for target ATBGuiRenderer
ATBGuiRenderer_OBJECTS = \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o" \
"CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o"

# External object files for target ATBGuiRenderer
ATBGuiRenderer_EXTERNAL_OBJECTS =

Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/build.make
Renderer/libATBGuiRenderer.a: Renderer/CMakeFiles/ATBGuiRenderer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX static library libATBGuiRenderer.a"
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && $(CMAKE_COMMAND) -P CMakeFiles/ATBGuiRenderer.dir/cmake_clean_target.cmake
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ATBGuiRenderer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Renderer/CMakeFiles/ATBGuiRenderer.dir/build: Renderer/libATBGuiRenderer.a

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/build

Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwPrecomp.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwColors.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwFonts.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwGraph.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGL.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGL.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwOpenGLCore.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/LoadOGLCore.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D9.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D10.cpp.o.requires
Renderer/CMakeFiles/ATBGuiRenderer.dir/requires: Renderer/CMakeFiles/ATBGuiRenderer.dir/compile/TwDirect3D11.cpp.o.requires

.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/requires

Renderer/CMakeFiles/ATBGuiRenderer.dir/clean:
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer && $(CMAKE_COMMAND) -P CMakeFiles/ATBGuiRenderer.dir/cmake_clean.cmake
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/clean

Renderer/CMakeFiles/ATBGuiRenderer.dir/depend: Renderer/Dummy
	cd /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer /home/angelika/Desktop/au-cg-master/3rdparty/AntTweakBar/Renderer/CMakeFiles/ATBGuiRenderer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Renderer/CMakeFiles/ATBGuiRenderer.dir/depend

