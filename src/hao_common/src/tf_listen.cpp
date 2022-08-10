/*
 * @Author: zhanghao
 * @Date: 2022-08-10 21:01:08
 * @LastEditTime: 2022-08-10 21:08:45
 * @FilePath: /hao_shenlan_ros1/src/hao_common/src/tf_listen.cpp
 * @Description: 
 */
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Pose.h>
#include <turtlesim/Spawn.h>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_listener");
    ros::NodeHandle n;
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    // 创建发布turtle2速度控制指令的发布者
    ros::Publisher turtle_vel = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 10);

    // 创建tf的监听器
    tf::TransformListener listener;

    ros::Rate rate(10.0);
    while (n.ok())
    {
        // 获取turtle1与turtle2坐标系之间的tf数据
        tf::StampedTransform transform;
        try
        {
            listener.waitForTransform("/turtle2", "/turtle1", ros::Time(0), ros::Duration(3.0));
            listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);
        }
        catch (tf::TransformException &ex)
        {
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        // 根据turtle1与turtle2坐标系之间的位置关系，发布turtle2的速度控制指令
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),
                                        transform.getOrigin().x());
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
                                      pow(transform.getOrigin().y(), 2));
        turtle_vel.publish(vel_msg);

        rate.sleep();
    }
    return 0;
}