#include"ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

void callback(const turtlesim::Pose::ConstPtr& pose)
{
	setlocale(LC_ALL,"");
	ROS_INFO("坐标x:%f",pose->x);
	ROS_INFO("坐标y:%f",pose->y);
	ROS_INFO("角度theta:%f",pose->theta);
	ROS_INFO("线速度linear_vel:%f",pose->linear_velocity);
	ROS_INFO("角速度angular_vel:%f",pose->angular_velocity);
	ROS_INFO("-------------------------------------------");
}
int main(int argc,char **argv)
{
	ros::init(argc,argv,"pose_subscriber");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);
	ros::Subscriber sub = n.subscribe("turtle1/pose",1000,callback);
	ros::Rate loop_rate(10);
	while(ros::ok())
	{
		geometry_msgs::Twist msg;
		msg.linear.x=0.3;
		msg.angular.z=0.3;
		pub.publish(msg);
		loop_rate.sleep();
		ros::spinOnce();
	}
	return 0;
}


