# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

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
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lexa/develop/ffmpeg-gui

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lexa/develop/ffmpeg-gui

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
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
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lexa/develop/ffmpeg-gui/CMakeFiles /home/lexa/develop/ffmpeg-gui/CMakeFiles/progress.make
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lexa/develop/ffmpeg-gui/CMakeFiles 0
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
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

CodecSelection.o: CodecSelection.cpp.o
.PHONY : CodecSelection.o

# target to build an object file
CodecSelection.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/CodecSelection.cpp.o
.PHONY : CodecSelection.cpp.o

CodecSelection.i: CodecSelection.cpp.i
.PHONY : CodecSelection.i

# target to preprocess a source file
CodecSelection.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/CodecSelection.cpp.i
.PHONY : CodecSelection.cpp.i

CodecSelection.s: CodecSelection.cpp.s
.PHONY : CodecSelection.s

# target to generate assembly for a file
CodecSelection.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/CodecSelection.cpp.s
.PHONY : CodecSelection.cpp.s

FFMPEG.o: FFMPEG.cpp.o
.PHONY : FFMPEG.o

# target to build an object file
FFMPEG.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/FFMPEG.cpp.o
.PHONY : FFMPEG.cpp.o

FFMPEG.i: FFMPEG.cpp.i
.PHONY : FFMPEG.i

# target to preprocess a source file
FFMPEG.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/FFMPEG.cpp.i
.PHONY : FFMPEG.cpp.i

FFMPEG.s: FFMPEG.cpp.s
.PHONY : FFMPEG.s

# target to generate assembly for a file
FFMPEG.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/FFMPEG.cpp.s
.PHONY : FFMPEG.cpp.s

MainWindow.o: MainWindow.cpp.o
.PHONY : MainWindow.o

# target to build an object file
MainWindow.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/MainWindow.cpp.o
.PHONY : MainWindow.cpp.o

MainWindow.i: MainWindow.cpp.i
.PHONY : MainWindow.i

# target to preprocess a source file
MainWindow.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/MainWindow.cpp.i
.PHONY : MainWindow.cpp.i

MainWindow.s: MainWindow.cpp.s
.PHONY : MainWindow.s

# target to generate assembly for a file
MainWindow.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/MainWindow.cpp.s
.PHONY : MainWindow.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

moc_CodecSelection.o: moc_CodecSelection.cxx.o
.PHONY : moc_CodecSelection.o

# target to build an object file
moc_CodecSelection.cxx.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_CodecSelection.cxx.o
.PHONY : moc_CodecSelection.cxx.o

moc_CodecSelection.i: moc_CodecSelection.cxx.i
.PHONY : moc_CodecSelection.i

# target to preprocess a source file
moc_CodecSelection.cxx.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_CodecSelection.cxx.i
.PHONY : moc_CodecSelection.cxx.i

moc_CodecSelection.s: moc_CodecSelection.cxx.s
.PHONY : moc_CodecSelection.s

# target to generate assembly for a file
moc_CodecSelection.cxx.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_CodecSelection.cxx.s
.PHONY : moc_CodecSelection.cxx.s

moc_FFMPEG.o: moc_FFMPEG.cxx.o
.PHONY : moc_FFMPEG.o

# target to build an object file
moc_FFMPEG.cxx.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_FFMPEG.cxx.o
.PHONY : moc_FFMPEG.cxx.o

moc_FFMPEG.i: moc_FFMPEG.cxx.i
.PHONY : moc_FFMPEG.i

# target to preprocess a source file
moc_FFMPEG.cxx.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_FFMPEG.cxx.i
.PHONY : moc_FFMPEG.cxx.i

moc_FFMPEG.s: moc_FFMPEG.cxx.s
.PHONY : moc_FFMPEG.s

# target to generate assembly for a file
moc_FFMPEG.cxx.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_FFMPEG.cxx.s
.PHONY : moc_FFMPEG.cxx.s

moc_MainWindow.o: moc_MainWindow.cxx.o
.PHONY : moc_MainWindow.o

# target to build an object file
moc_MainWindow.cxx.o:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_MainWindow.cxx.o
.PHONY : moc_MainWindow.cxx.o

moc_MainWindow.i: moc_MainWindow.cxx.i
.PHONY : moc_MainWindow.i

# target to preprocess a source file
moc_MainWindow.cxx.i:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_MainWindow.cxx.i
.PHONY : moc_MainWindow.cxx.i

moc_MainWindow.s: moc_MainWindow.cxx.s
.PHONY : moc_MainWindow.s

# target to generate assembly for a file
moc_MainWindow.cxx.s:
	$(MAKE) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/moc_MainWindow.cxx.s
.PHONY : moc_MainWindow.cxx.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... main"
	@echo "... rebuild_cache"
	@echo "... CodecSelection.o"
	@echo "... CodecSelection.i"
	@echo "... CodecSelection.s"
	@echo "... FFMPEG.o"
	@echo "... FFMPEG.i"
	@echo "... FFMPEG.s"
	@echo "... MainWindow.o"
	@echo "... MainWindow.i"
	@echo "... MainWindow.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... moc_CodecSelection.o"
	@echo "... moc_CodecSelection.i"
	@echo "... moc_CodecSelection.s"
	@echo "... moc_FFMPEG.o"
	@echo "... moc_FFMPEG.i"
	@echo "... moc_FFMPEG.s"
	@echo "... moc_MainWindow.o"
	@echo "... moc_MainWindow.i"
	@echo "... moc_MainWindow.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

