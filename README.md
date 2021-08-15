# home_service_robot# Welcome to Home Service robot project!

This project uses a **Differential drive turtlebot robot** to pickup any object( mimicked using visualisation marker messages **CUBE**) from object's location and dropoff the object at any desired location in a mapped environment using **Navigation Stack**


# Packages used

**Custom packages**
**myrobot :** It contains the gazebo world file along with some other sample urdf files of a simple differential drive robot
**add_markers :** It contains files for visualising the objects as cubes
**pickup_objects :** It contains files for passing custom goals to the navigation stack

**Open Source packages**
gmapping, turtlebot_gazebo, turtlebot_navigation, turtlebot_bringup, turtlebot_rviz_launchers, amcl

## How to use?
1) Clone the package and build the package
2) Run roscore in a terminal.
2) Go to the scripts directory to use "bash $FILE_NAME" to run 

**test_slam.sh** script file is used to manually test SLAM. Use the teleop keys to move the robot for mapping
**test_navigation.sh** script file is used to manually test navigation. You can set the 2D goal on rviz to test.
**add_marker.sh** script file is used to test the visualisation of marker. The marker is published at the pickup zone. It will be hidden after 5 seconds to mimick that robot has collected the object. Then after another 5 seconds it appears at the drop off zone to mimick the dropoff.
**home_service.sh** script file will run all the nodes in this project. Initially marker will be at the pickup zone and it will be hidden once your robot reach the pickup zone. The turtbot waits for 5 seconds to simulate a pickup. Finally, it shows the marker at the drop off zone once your robot reaches it.


## RQT Graph

![enter image description here](https://drive.google.com/file/d/1Wp-WcqUdrb-gK-NyZaV4fW1PjYaDZ_Te/view?usp=sharing)

## Prerequisites

You need to have installed [ROS - Robot Operating System](http://www.ros.org/) in your system along with navigation stack and xterm.


