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
CMAKE_SOURCE_DIR = /home/xillinux/cobot/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xillinux/cobot/catkin_ws/build

# Include any dependencies generated for this target.
include server_node/CMakeFiles/server_node.dir/depend.make

# Include the progress variables for this target.
include server_node/CMakeFiles/server_node.dir/progress.make

# Include the compile flags for this target's objects.
include server_node/CMakeFiles/server_node.dir/flags.make

server_node/CMakeFiles/server_node.dir/src/main.cc.o: server_node/CMakeFiles/server_node.dir/flags.make
server_node/CMakeFiles/server_node.dir/src/main.cc.o: /home/xillinux/cobot/catkin_ws/src/server_node/src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xillinux/cobot/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server_node/CMakeFiles/server_node.dir/src/main.cc.o"
	cd /home/xillinux/cobot/catkin_ws/build/server_node && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server_node.dir/src/main.cc.o -c /home/xillinux/cobot/catkin_ws/src/server_node/src/main.cc

server_node/CMakeFiles/server_node.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_node.dir/src/main.cc.i"
	cd /home/xillinux/cobot/catkin_ws/build/server_node && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xillinux/cobot/catkin_ws/src/server_node/src/main.cc > CMakeFiles/server_node.dir/src/main.cc.i

server_node/CMakeFiles/server_node.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_node.dir/src/main.cc.s"
	cd /home/xillinux/cobot/catkin_ws/build/server_node && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xillinux/cobot/catkin_ws/src/server_node/src/main.cc -o CMakeFiles/server_node.dir/src/main.cc.s

server_node/CMakeFiles/server_node.dir/src/main.cc.o.requires:

.PHONY : server_node/CMakeFiles/server_node.dir/src/main.cc.o.requires

server_node/CMakeFiles/server_node.dir/src/main.cc.o.provides: server_node/CMakeFiles/server_node.dir/src/main.cc.o.requires
	$(MAKE) -f server_node/CMakeFiles/server_node.dir/build.make server_node/CMakeFiles/server_node.dir/src/main.cc.o.provides.build
.PHONY : server_node/CMakeFiles/server_node.dir/src/main.cc.o.provides

server_node/CMakeFiles/server_node.dir/src/main.cc.o.provides.build: server_node/CMakeFiles/server_node.dir/src/main.cc.o


# Object files for target server_node
server_node_OBJECTS = \
"CMakeFiles/server_node.dir/src/main.cc.o"

# External object files for target server_node
server_node_EXTERNAL_OBJECTS =

/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: server_node/CMakeFiles/server_node.dir/src/main.cc.o
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: server_node/CMakeFiles/server_node.dir/build.make
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/libroscpp.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/librosconsole.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/librosconsole_log4cxx.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/librosconsole_backend_interface.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/libxmlrpcpp.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/libroscpp_serialization.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/librostime.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /opt/ros/lunar/lib/libcpp_common.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node: server_node/CMakeFiles/server_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xillinux/cobot/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node"
	cd /home/xillinux/cobot/catkin_ws/build/server_node && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server_node/CMakeFiles/server_node.dir/build: /home/xillinux/cobot/catkin_ws/devel/lib/server_node/server_node

.PHONY : server_node/CMakeFiles/server_node.dir/build

server_node/CMakeFiles/server_node.dir/requires: server_node/CMakeFiles/server_node.dir/src/main.cc.o.requires

.PHONY : server_node/CMakeFiles/server_node.dir/requires

server_node/CMakeFiles/server_node.dir/clean:
	cd /home/xillinux/cobot/catkin_ws/build/server_node && $(CMAKE_COMMAND) -P CMakeFiles/server_node.dir/cmake_clean.cmake
.PHONY : server_node/CMakeFiles/server_node.dir/clean

server_node/CMakeFiles/server_node.dir/depend:
	cd /home/xillinux/cobot/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xillinux/cobot/catkin_ws/src /home/xillinux/cobot/catkin_ws/src/server_node /home/xillinux/cobot/catkin_ws/build /home/xillinux/cobot/catkin_ws/build/server_node /home/xillinux/cobot/catkin_ws/build/server_node/CMakeFiles/server_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server_node/CMakeFiles/server_node.dir/depend
