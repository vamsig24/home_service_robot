#!/bin/sh
xterm  -e  " pkill gzserver; pkill gzclient; exit " & 
xterm  -e  " cd ..; source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch " & 
sleep 10
xterm  -e  " cd ..; source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 15
xterm  -e  " cd ..; source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
xterm  -e  " cd ..; source devel/setup.bash; rosrun pick_objects pick_object_node " 
