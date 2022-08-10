/*
 * @Author: zhanghao
 * @Date: 2022-08-10 20:51:56
 * @LastEditTime: 2022-08-10 20:59:56
 * @FilePath: /hao_shenlan_ros1/src/hao_common/src/tf.cpp
 * @Description: 
 */
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>
std::string turtle_name;
void poseCallback(const turtlesim::PoseConstPtr& msg)
{
    static tf::TransformBroadcaster br;
    //init tf data
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(msg->x, msg->y, 0.0));
    tf::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    transform.setRotation(q);
    //send tf data
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_broadcaster");
    if(argc != 2)
    {
        ROS_ERROR("Error: need turtle name as argument");
        return 1;
    }
    turtle_name = argv[1];
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe(turtle_name + "/pose", 10, poseCallback);
    ros::spin();
    return 0;
}