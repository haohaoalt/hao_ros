/**
 * 该例程将订阅turtle1/pose话题，消息类型turtlesim::Pose
 */
 
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
// 接收到订阅的消息后，会进入消息回调函数
void PoseCallback(const turtlesim::Pose::ConstPtr& msg)
{
    // 将接收到的消息打印出来
    ROS_INFO("turtle pos x: [%f], y:[%f]", msg->x,msg->y);
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "turtle_subscriber");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Subscriber，注册回调函数PoseCallback
    ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, PoseCallback);

    // 循环等待回调函数
    ros::spin();

    return 0;
}


