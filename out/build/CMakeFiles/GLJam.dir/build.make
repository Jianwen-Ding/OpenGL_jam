# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build"

# Include any dependencies generated for this target.
include CMakeFiles/GLJam.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GLJam.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GLJam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GLJam.dir/flags.make

CMakeFiles/GLJam.dir/main.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/main.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/main.cpp
CMakeFiles/GLJam.dir/main.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GLJam.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/main.cpp.o -MF CMakeFiles/GLJam.dir/main.cpp.o.d -o CMakeFiles/GLJam.dir/main.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/main.cpp"

CMakeFiles/GLJam.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/main.cpp" > CMakeFiles/GLJam.dir/main.cpp.i

CMakeFiles/GLJam.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/main.cpp" -o CMakeFiles/GLJam.dir/main.cpp.s

CMakeFiles/GLJam.dir/src/Camera.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Camera.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Camera.cpp
CMakeFiles/GLJam.dir/src/Camera.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GLJam.dir/src/Camera.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Camera.cpp.o -MF CMakeFiles/GLJam.dir/src/Camera.cpp.o.d -o CMakeFiles/GLJam.dir/src/Camera.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Camera.cpp"

CMakeFiles/GLJam.dir/src/Camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Camera.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Camera.cpp" > CMakeFiles/GLJam.dir/src/Camera.cpp.i

CMakeFiles/GLJam.dir/src/Camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Camera.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Camera.cpp" -o CMakeFiles/GLJam.dir/src/Camera.cpp.s

CMakeFiles/GLJam.dir/src/Mesh.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Mesh.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Mesh.cpp
CMakeFiles/GLJam.dir/src/Mesh.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GLJam.dir/src/Mesh.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Mesh.cpp.o -MF CMakeFiles/GLJam.dir/src/Mesh.cpp.o.d -o CMakeFiles/GLJam.dir/src/Mesh.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Mesh.cpp"

CMakeFiles/GLJam.dir/src/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Mesh.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Mesh.cpp" > CMakeFiles/GLJam.dir/src/Mesh.cpp.i

CMakeFiles/GLJam.dir/src/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Mesh.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Mesh.cpp" -o CMakeFiles/GLJam.dir/src/Mesh.cpp.s

CMakeFiles/GLJam.dir/src/Model.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Model.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Model.cpp
CMakeFiles/GLJam.dir/src/Model.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GLJam.dir/src/Model.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Model.cpp.o -MF CMakeFiles/GLJam.dir/src/Model.cpp.o.d -o CMakeFiles/GLJam.dir/src/Model.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Model.cpp"

CMakeFiles/GLJam.dir/src/Model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Model.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Model.cpp" > CMakeFiles/GLJam.dir/src/Model.cpp.i

CMakeFiles/GLJam.dir/src/Model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Model.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Model.cpp" -o CMakeFiles/GLJam.dir/src/Model.cpp.s

CMakeFiles/GLJam.dir/src/Render_Management.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Render_Management.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Render_Management.cpp
CMakeFiles/GLJam.dir/src/Render_Management.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GLJam.dir/src/Render_Management.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Render_Management.cpp.o -MF CMakeFiles/GLJam.dir/src/Render_Management.cpp.o.d -o CMakeFiles/GLJam.dir/src/Render_Management.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Render_Management.cpp"

CMakeFiles/GLJam.dir/src/Render_Management.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Render_Management.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Render_Management.cpp" > CMakeFiles/GLJam.dir/src/Render_Management.cpp.i

CMakeFiles/GLJam.dir/src/Render_Management.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Render_Management.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Render_Management.cpp" -o CMakeFiles/GLJam.dir/src/Render_Management.cpp.s

CMakeFiles/GLJam.dir/src/Shader.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Shader.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Shader.cpp
CMakeFiles/GLJam.dir/src/Shader.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/GLJam.dir/src/Shader.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Shader.cpp.o -MF CMakeFiles/GLJam.dir/src/Shader.cpp.o.d -o CMakeFiles/GLJam.dir/src/Shader.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Shader.cpp"

CMakeFiles/GLJam.dir/src/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Shader.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Shader.cpp" > CMakeFiles/GLJam.dir/src/Shader.cpp.i

CMakeFiles/GLJam.dir/src/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Shader.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Shader.cpp" -o CMakeFiles/GLJam.dir/src/Shader.cpp.s

CMakeFiles/GLJam.dir/src/Texture.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/Texture.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/Texture.cpp
CMakeFiles/GLJam.dir/src/Texture.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/GLJam.dir/src/Texture.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/Texture.cpp.o -MF CMakeFiles/GLJam.dir/src/Texture.cpp.o.d -o CMakeFiles/GLJam.dir/src/Texture.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Texture.cpp"

CMakeFiles/GLJam.dir/src/Texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/Texture.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Texture.cpp" > CMakeFiles/GLJam.dir/src/Texture.cpp.i

CMakeFiles/GLJam.dir/src/Texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/Texture.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/Texture.cpp" -o CMakeFiles/GLJam.dir/src/Texture.cpp.s

CMakeFiles/GLJam.dir/src/TextureArray.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/TextureArray.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/TextureArray.cpp
CMakeFiles/GLJam.dir/src/TextureArray.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/GLJam.dir/src/TextureArray.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/TextureArray.cpp.o -MF CMakeFiles/GLJam.dir/src/TextureArray.cpp.o.d -o CMakeFiles/GLJam.dir/src/TextureArray.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/TextureArray.cpp"

CMakeFiles/GLJam.dir/src/TextureArray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/TextureArray.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/TextureArray.cpp" > CMakeFiles/GLJam.dir/src/TextureArray.cpp.i

CMakeFiles/GLJam.dir/src/TextureArray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/TextureArray.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/TextureArray.cpp" -o CMakeFiles/GLJam.dir/src/TextureArray.cpp.s

CMakeFiles/GLJam.dir/src/stb_imag.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/stb_imag.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/stb_imag.cpp
CMakeFiles/GLJam.dir/src/stb_imag.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/GLJam.dir/src/stb_imag.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/stb_imag.cpp.o -MF CMakeFiles/GLJam.dir/src/stb_imag.cpp.o.d -o CMakeFiles/GLJam.dir/src/stb_imag.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/stb_imag.cpp"

CMakeFiles/GLJam.dir/src/stb_imag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/stb_imag.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/stb_imag.cpp" > CMakeFiles/GLJam.dir/src/stb_imag.cpp.i

CMakeFiles/GLJam.dir/src/stb_imag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/stb_imag.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/stb_imag.cpp" -o CMakeFiles/GLJam.dir/src/stb_imag.cpp.s

CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/structs/Vertex.cpp
CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o -MF CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o.d -o CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/structs/Vertex.cpp"

CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/structs/Vertex.cpp" > CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.i

CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/structs/Vertex.cpp" -o CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.s

CMakeFiles/GLJam.dir/src/glad.c.o: CMakeFiles/GLJam.dir/flags.make
CMakeFiles/GLJam.dir/src/glad.c.o: /Users/jianwending/Documents/ProjectsFolder/Current\ Projects/OpenGL_jam/src/glad.c
CMakeFiles/GLJam.dir/src/glad.c.o: CMakeFiles/GLJam.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/GLJam.dir/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/GLJam.dir/src/glad.c.o -MF CMakeFiles/GLJam.dir/src/glad.c.o.d -o CMakeFiles/GLJam.dir/src/glad.c.o -c "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/glad.c"

CMakeFiles/GLJam.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/GLJam.dir/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/glad.c" > CMakeFiles/GLJam.dir/src/glad.c.i

CMakeFiles/GLJam.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/GLJam.dir/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/src/glad.c" -o CMakeFiles/GLJam.dir/src/glad.c.s

# Object files for target GLJam
GLJam_OBJECTS = \
"CMakeFiles/GLJam.dir/main.cpp.o" \
"CMakeFiles/GLJam.dir/src/Camera.cpp.o" \
"CMakeFiles/GLJam.dir/src/Mesh.cpp.o" \
"CMakeFiles/GLJam.dir/src/Model.cpp.o" \
"CMakeFiles/GLJam.dir/src/Render_Management.cpp.o" \
"CMakeFiles/GLJam.dir/src/Shader.cpp.o" \
"CMakeFiles/GLJam.dir/src/Texture.cpp.o" \
"CMakeFiles/GLJam.dir/src/TextureArray.cpp.o" \
"CMakeFiles/GLJam.dir/src/stb_imag.cpp.o" \
"CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o" \
"CMakeFiles/GLJam.dir/src/glad.c.o"

# External object files for target GLJam
GLJam_EXTERNAL_OBJECTS =

GLJam: CMakeFiles/GLJam.dir/main.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Camera.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Mesh.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Model.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Render_Management.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Shader.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/Texture.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/TextureArray.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/stb_imag.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/structs/Vertex.cpp.o
GLJam: CMakeFiles/GLJam.dir/src/glad.c.o
GLJam: CMakeFiles/GLJam.dir/build.make
GLJam: /Library/Frameworks/SDL2.framework/Versions/A/SDL2
GLJam: /opt/homebrew/lib/libassimp.5.4.3.dylib
GLJam: /Library/Developer/CommandLineTools/SDKs/MacOSX14.sdk/usr/lib/libz.tbd
GLJam: CMakeFiles/GLJam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable GLJam"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GLJam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GLJam.dir/build: GLJam
.PHONY : CMakeFiles/GLJam.dir/build

CMakeFiles/GLJam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/GLJam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/GLJam.dir/clean

CMakeFiles/GLJam.dir/depend:
	cd "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam" "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam" "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build" "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build" "/Users/jianwending/Documents/ProjectsFolder/Current Projects/OpenGL_jam/out/build/CMakeFiles/GLJam.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/GLJam.dir/depend

