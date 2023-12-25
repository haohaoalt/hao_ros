/**
 * 该例程将请求spawn服务，turtlesim::Spawn
 */
 
#include "ros/ros.h"
#include "turtlesim/Spawn.h"

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "newTurtle_client");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个client，service消息类型是turtlesim::Spawn
    ros::service::waitForService("/spawn");
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("/spawn");

    // 创建turtlesim::Spawn类型的service消息
    turtlesim::Spawn srv;
    srv.request.x = 2.0;
    srv.request.y = 2.0;
    srv.request.name = "turtle3";

    // 发布service请求，等待应答结果
    if (client.call(srv))
    {
        ROS_INFO("Spawn turtle successfully [name:%s]", srv.response.name.c_str());
    }
    else
    {
        ROS_ERROR("Failed to Spawn turtle");
        return 1;
    }

    return 0;
}

