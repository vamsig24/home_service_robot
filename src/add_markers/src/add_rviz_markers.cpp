#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <std_msgs/Bool.h>

#include <vector>

static ros::Publisher marker_pub;
void pub_markers( double x, double y, double orient, int operation);
void collect_callback( const std_msgs::Bool &msg);
void dropoff_callback( const std_msgs::Bool &msg);
bool pickup = false;
bool dropoff = false;
 // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;


 void pub_markers(double x, double y, double orient, int operation)
  {
      visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    if( operation == 1)
        marker.action = visualization_msgs::Marker::ADD;
    else if(operation == 0 )
        marker.action = visualization_msgs::Marker::DELETE;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = x;
    marker.pose.position.y = y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = orient;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    marker_pub.publish(marker);
  }
void collect_callback(const std_msgs::Bool &msg)
{
  if(msg.data)
  {
    pickup = true;
    ROS_INFO("Pickup Reached");
    pub_markers(2.0,2.0,1.0,0);
  }
  else
  {
    pickup = false;
  }
  
}

void dropoff_callback(const std_msgs::Bool &msg)
{
  if(msg.data)
  {
    dropoff = true;
    ROS_INFO("Dropoff Reached");
    pub_markers(-2.0,-2.0,1.0,1);
  }
  else
  {
    dropoff = false;
  }
  
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber collect_call = n.subscribe("collect_check",10,collect_callback);
  ros::Subscriber drop_call = n.subscribe("dropoff_check",10,dropoff_callback);


  while (ros::ok())
  {

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    pub_markers(2.0,2.0,1.0,1);
    ROS_INFO("Published 1st time");
    // ros::Duration(5.0).sleep();
    // pub_markers(marker_pub,2.0,2.0,1.0,0);
    // ros::Duration(5.0).sleep();
    // ROS_INFO("Transporting");
    // pub_markers(marker_pub,-2.0,-2.0,1.0,1);
    // ROS_INFO("Published 2nd time");
    // ros::Duration(5.0).sleep();
    ros::spin();


    // r.sleep();
  }
}