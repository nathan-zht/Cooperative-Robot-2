# Cooperative-Robot-2
This repo contains the source files for the cobot 2 project.

Software environment:
Linux image based on ubuntu 16.04 LTS by xillybus with all the required IP already installed.
ROS Kinetic Kame and Lunar Loggerhead.

Libnavajo and other miscellaneous Linux libraries from the ubuntu repo that can be installed using apt-get.
Libnavajo can be obtained from https://github.com/titi38/libnavajo.
Note: we encountered a problem with one file on newer versions of libnavajo. It was solved by commenting out the relevant lines, or replacing the problem variable of an array of characters with std::string. Hopefully, this enough a clue to solve the problem if it appears.

The repository only contains the src and html folder of the catkin workspace as the other folders contain generated files and folders. To regenerate them use the catkin_make command. Also, in this repo is the html folder which contains files for the website use for the user interface. The syntax calling files required for the web server in (catkin workspace)/src/server_node/src/main.cc may need to be edited to reflect the correct directory of the file.
The branches master_fsm contains the files for the master robot and the slave_fsm branches contains the files for the slave robot. To use the software, the files can be copied into an initialized catkin workspace on the zybo boards. It should be compatible with the newer distributions of ROS.
The nodes are launched the roslaunch tool with cobot_master.launch and cobot_slave.launch. Instructions on how to use it can be found on the ROS wiki. Alternatively, the nodes can be launch individually, this can be useful for debugging purposes.
The setup_environment_master.sh and setup_environment_slave.sh can be used to setup the environment. Adjust the ROS_IP and ROS_MASTER_URI variables to the system being used.
