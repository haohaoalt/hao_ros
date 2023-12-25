/**
 * 该例程产生tf数据，并计算、发布turtle2的速度指令
 */

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "robot_tf_broadcaster");

    // 订阅base_link位姿话题
    ros::NodeHandle node;
	
    // 创建tf的广播器
    static tf::TransformBroadcaster br;

    while(node.ok())
    {
        // 初始化tf数据
        tf::Transform transform;
        transform.setOrigin( tf::Vector3(0.1, 0.0, 0.2) );
        transform.setRotation( tf::Quaternion(0,0,0,1) );

        // 广播base_link与base_laser坐标系之间的tf数据
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "base_laser"));
    }
    return 0;
};


