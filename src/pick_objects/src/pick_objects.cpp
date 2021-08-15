#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>


// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
bool send_goal(MoveBaseClient &ac_, int id_, double x, double y, double orient);
  ros::Publisher pub_dropoff;
  ros::Publisher pub_collect;

bool send_goal(MoveBaseClient &ac_, int id_, double x, double y, double orient)
{
    move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = orient;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal %d", id_);
  ac_.sendGoal(goal);

  // Wait an infinite time for the results
  ac_.waitForResult();

  // Check if the robot reached its goal
  if(ac_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {
    ROS_INFO("Hooray, the base moved to x: %lf y: %lf orientation: %lf position",x,y,orient);
    // auto msg_pub = std_msgs::Bool();
    std_msgs::Bool msg_pub;
    msg_pub.data = true;
    if(id_ == 1)
    {
      pub_collect.publish(msg_pub);
    }
    else if(id_ == 2)
    {
      pub_dropoff.publish(msg_pub);
    }
    return true;
  }
  else
  {
    ROS_INFO("The base failed to move forward 1 meter for some reason");
    return false;
  }
}

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ros::NodeHandle n;
  pub_dropoff = n.advertise<std_msgs::Bool>("dropoff_check", 1);
  pub_collect = n.advertise<std_msgs::Bool>("collect_check", 1);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

    bool goal_result = send_goal(ac,1,2.0,2.0,1.0);
    if(goal_result)
    {
    //    pub_dropoff.publish()
        ros::Duration(5.0).sleep();
        bool goal_res_2 = send_goal(ac,2,-2.0,-2.0,1.0);
    }


//   move_base_msgs::MoveBaseGoal goal;

//   // set up the frame parameters
//   goal.target_pose.header.frame_id = "map";
//   goal.target_pose.header.stamp = ros::Time::now();

//   // Define a position and orientation for the robot to reach
//   goal.target_pose.pose.position.x = 1.0;
//   goal.target_pose.pose.orientation.w = 1.0;

//    // Send the goal position and orientation for the robot to reach
//   ROS_INFO("Sending goal");
//   ac.sendGoal(goal);

//   // Wait an infinite time for the results
//   ac.waitForResult();

//   // Check if the robot reached its goal
//   if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//   {
//     ROS_INFO("Hooray, the base moved 1 meter forward");
//   }

//   else
//     ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}