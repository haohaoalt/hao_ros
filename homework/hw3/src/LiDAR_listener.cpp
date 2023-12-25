#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "ros/param.h"
#include <iostream>
#include <functional>
using namespace std;

//本节点负责转换

void transformPoint(const tf::TransformListener &listener)
{
    geometry_msgs::PointStamped laser_point;
	laser_point.header.frame_id = "base_laser";
	laser_point.header.stamp = ros::Time();
	laser_point.point.x = 0.3;
    laser_point.point.y = 0.0;
    laser_point.point.z = 0.0;

    while(ros::ok())
    {
        tf::StampedTransform transform;
        try
        {
            //这里是2个坐标系
            geometry_msgs::PointStamped base_point;
            listener.transformPoint("base_link",laser_point,base_point);
            ROS_INFO("The point in base_link is [%2f,%2f,%2f].",
                 base_point.point.x,base_point.point.y,base_point.point.z);
        }
        catch(tf::TransformException &e)
        {
            ROS_ERROR("%s",e.what());
            ros::Duration(1.0).sleep();
        }
    }
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"LiDAR_listener");
    ros::NodeHandle node;
    tf::TransformListener listener;
    ros::Timer timer = node.createTimer(
        ros::Duration(1.0),bind(&transformPoint,std::ref(listener)));
    ros::spin(); //循环等待
    return 0;
}
