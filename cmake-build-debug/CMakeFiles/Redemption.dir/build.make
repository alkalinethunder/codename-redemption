# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Projects\Games\Redemption

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Projects\Games\Redemption\cmake-build-debug

# Utility rule file for Redemption.

# Include the progress variables for this target.
include CMakeFiles\Redemption.dir\progress.make

CMakeFiles\Redemption:
	call "C:/Program Files/Epic Games/UE_4.26/Engine/Build/BatchFiles/Build.bat" Redemption Win64 Development -project=D:/Projects/Games/Redemption/Redemption.uproject -game -progress -buildscw

Redemption: CMakeFiles\Redemption
Redemption: CMakeFiles\Redemption.dir\build.make

.PHONY : Redemption

# Rule to build all files generated by this target.
CMakeFiles\Redemption.dir\build: Redemption

.PHONY : CMakeFiles\Redemption.dir\build

CMakeFiles\Redemption.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Redemption.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Redemption.dir\clean

CMakeFiles\Redemption.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" D:\Projects\Games\Redemption D:\Projects\Games\Redemption D:\Projects\Games\Redemption\cmake-build-debug D:\Projects\Games\Redemption\cmake-build-debug D:\Projects\Games\Redemption\cmake-build-debug\CMakeFiles\Redemption.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Redemption.dir\depend

