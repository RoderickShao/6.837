# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\Cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\Cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\user020\Desktop\Code\6.837\Assignment 8"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\user020\Desktop\Code\6.837\Assignment 8\build"

# Include any dependencies generated for this target.
include CMakeFiles/Assignment8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Assignment8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Assignment8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Assignment8.dir/flags.make

CMakeFiles/Assignment8.dir/codegen:
.PHONY : CMakeFiles/Assignment8.dir/codegen

CMakeFiles/Assignment8.dir/curve.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/curve.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/curve.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/curve.C
CMakeFiles/Assignment8.dir/curve.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Assignment8.dir/curve.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/curve.C.obj -MF CMakeFiles\Assignment8.dir\curve.C.obj.d -o CMakeFiles\Assignment8.dir\curve.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\curve.C"

CMakeFiles/Assignment8.dir/curve.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/curve.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\curve.C" > CMakeFiles\Assignment8.dir\curve.C.i

CMakeFiles/Assignment8.dir/curve.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/curve.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\curve.C" -o CMakeFiles\Assignment8.dir\curve.C.s

CMakeFiles/Assignment8.dir/glCanvas.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/glCanvas.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/glCanvas.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/glCanvas.C
CMakeFiles/Assignment8.dir/glCanvas.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Assignment8.dir/glCanvas.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/glCanvas.C.obj -MF CMakeFiles\Assignment8.dir\glCanvas.C.obj.d -o CMakeFiles\Assignment8.dir\glCanvas.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\glCanvas.C"

CMakeFiles/Assignment8.dir/glCanvas.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/glCanvas.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\glCanvas.C" > CMakeFiles\Assignment8.dir\glCanvas.C.i

CMakeFiles/Assignment8.dir/glCanvas.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/glCanvas.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\glCanvas.C" -o CMakeFiles\Assignment8.dir\glCanvas.C.s

CMakeFiles/Assignment8.dir/main.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/main.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/main.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/main.C
CMakeFiles/Assignment8.dir/main.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Assignment8.dir/main.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/main.C.obj -MF CMakeFiles\Assignment8.dir\main.C.obj.d -o CMakeFiles\Assignment8.dir\main.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\main.C"

CMakeFiles/Assignment8.dir/main.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/main.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\main.C" > CMakeFiles\Assignment8.dir\main.C.i

CMakeFiles/Assignment8.dir/main.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/main.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\main.C" -o CMakeFiles\Assignment8.dir\main.C.s

CMakeFiles/Assignment8.dir/matrix.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/matrix.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/matrix.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/matrix.C
CMakeFiles/Assignment8.dir/matrix.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Assignment8.dir/matrix.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/matrix.C.obj -MF CMakeFiles\Assignment8.dir\matrix.C.obj.d -o CMakeFiles\Assignment8.dir\matrix.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\matrix.C"

CMakeFiles/Assignment8.dir/matrix.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/matrix.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\matrix.C" > CMakeFiles\Assignment8.dir\matrix.C.i

CMakeFiles/Assignment8.dir/matrix.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/matrix.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\matrix.C" -o CMakeFiles\Assignment8.dir\matrix.C.s

CMakeFiles/Assignment8.dir/spline_parser.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/spline_parser.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/spline_parser.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/spline_parser.C
CMakeFiles/Assignment8.dir/spline_parser.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Assignment8.dir/spline_parser.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/spline_parser.C.obj -MF CMakeFiles\Assignment8.dir\spline_parser.C.obj.d -o CMakeFiles\Assignment8.dir\spline_parser.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\spline_parser.C"

CMakeFiles/Assignment8.dir/spline_parser.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/spline_parser.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\spline_parser.C" > CMakeFiles\Assignment8.dir\spline_parser.C.i

CMakeFiles/Assignment8.dir/spline_parser.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/spline_parser.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\spline_parser.C" -o CMakeFiles\Assignment8.dir\spline_parser.C.s

CMakeFiles/Assignment8.dir/surface.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/surface.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/surface.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/surface.C
CMakeFiles/Assignment8.dir/surface.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Assignment8.dir/surface.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/surface.C.obj -MF CMakeFiles\Assignment8.dir\surface.C.obj.d -o CMakeFiles\Assignment8.dir\surface.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\surface.C"

CMakeFiles/Assignment8.dir/surface.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/surface.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\surface.C" > CMakeFiles\Assignment8.dir\surface.C.i

CMakeFiles/Assignment8.dir/surface.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/surface.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\surface.C" -o CMakeFiles\Assignment8.dir\surface.C.s

CMakeFiles/Assignment8.dir/triangle_mesh.C.obj: CMakeFiles/Assignment8.dir/flags.make
CMakeFiles/Assignment8.dir/triangle_mesh.C.obj: CMakeFiles/Assignment8.dir/includes_CXX.rsp
CMakeFiles/Assignment8.dir/triangle_mesh.C.obj: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/triangle_mesh.C
CMakeFiles/Assignment8.dir/triangle_mesh.C.obj: CMakeFiles/Assignment8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Assignment8.dir/triangle_mesh.C.obj"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Assignment8.dir/triangle_mesh.C.obj -MF CMakeFiles\Assignment8.dir\triangle_mesh.C.obj.d -o CMakeFiles\Assignment8.dir\triangle_mesh.C.obj -c "C:\Users\user020\Desktop\Code\6.837\Assignment 8\triangle_mesh.C"

CMakeFiles/Assignment8.dir/triangle_mesh.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Assignment8.dir/triangle_mesh.C.i"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\user020\Desktop\Code\6.837\Assignment 8\triangle_mesh.C" > CMakeFiles\Assignment8.dir\triangle_mesh.C.i

CMakeFiles/Assignment8.dir/triangle_mesh.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Assignment8.dir/triangle_mesh.C.s"
	D:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\user020\Desktop\Code\6.837\Assignment 8\triangle_mesh.C" -o CMakeFiles\Assignment8.dir\triangle_mesh.C.s

# Object files for target Assignment8
Assignment8_OBJECTS = \
"CMakeFiles/Assignment8.dir/curve.C.obj" \
"CMakeFiles/Assignment8.dir/glCanvas.C.obj" \
"CMakeFiles/Assignment8.dir/main.C.obj" \
"CMakeFiles/Assignment8.dir/matrix.C.obj" \
"CMakeFiles/Assignment8.dir/spline_parser.C.obj" \
"CMakeFiles/Assignment8.dir/surface.C.obj" \
"CMakeFiles/Assignment8.dir/triangle_mesh.C.obj"

# External object files for target Assignment8
Assignment8_EXTERNAL_OBJECTS =

Assignment8.exe: CMakeFiles/Assignment8.dir/curve.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/glCanvas.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/main.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/matrix.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/spline_parser.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/surface.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/triangle_mesh.C.obj
Assignment8.exe: CMakeFiles/Assignment8.dir/build.make
Assignment8.exe: C:/Users/user020/Desktop/Code/6.837/Assignment\ 8/glut/Debug/freeglutd.lib
Assignment8.exe: CMakeFiles/Assignment8.dir/linkLibs.rsp
Assignment8.exe: CMakeFiles/Assignment8.dir/objects1.rsp
Assignment8.exe: CMakeFiles/Assignment8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Assignment8.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Assignment8.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Assignment8.dir/build: Assignment8.exe
.PHONY : CMakeFiles/Assignment8.dir/build

CMakeFiles/Assignment8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Assignment8.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Assignment8.dir/clean

CMakeFiles/Assignment8.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\user020\Desktop\Code\6.837\Assignment 8" "C:\Users\user020\Desktop\Code\6.837\Assignment 8" "C:\Users\user020\Desktop\Code\6.837\Assignment 8\build" "C:\Users\user020\Desktop\Code\6.837\Assignment 8\build" "C:\Users\user020\Desktop\Code\6.837\Assignment 8\build\CMakeFiles\Assignment8.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Assignment8.dir/depend

