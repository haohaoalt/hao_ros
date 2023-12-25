/**
 * 该例程将发布turtle1/cmd_vel话题，消息类型geometry_msgs::Twist
 */
 
#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "turtle_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

    // 设置循环的频率
    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok())
    {
        // 初始化消息
        geometry_msgs::Twist msg;
        msg.linear.x=1.0;
        msg.linear.y=0.0;
        msg.linear.z=0.0;
        msg.angular.x=0.0;
        msg.angular.y=0.0;
        msg.angular.z=0.5;

        // 发布消息
        cmd_vel_pub.publish(msg);

        // 按照循环频率延时
        loop_rate.sleep();
        ++count;
    }

    return 0;
}
