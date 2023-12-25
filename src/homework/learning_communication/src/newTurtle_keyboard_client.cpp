/**
 * 该例程将请求spawn服务，turtlesim::Spawn
 */
 
#include "ros/ros.h"
#include "turtlesim/Spawn.h"
#include "std_msgs/String.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <math.h>
using namespace std;
int turtle_count=1;
int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "newTurtle_client");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个client，service消息类型是turtlesim::Spawn
    ros::service::waitForService("/spawn");
    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>("/spawn");

    std::string turtleName;
    std::cout << "What is the turtle's name? ";
    std::cin >> turtleName;

    //隨機生成位置信息
    const int MAX_VALUE = 10;

    time_t t;
    srand((unsigned) time(&t));

    vector<int> xvector;
    vector<int> yvector;   

    for (int i = 0; i < 10; ++i)
    {
        xvector.push_back(i + 1);
        yvector.push_back(i + 1);
    }
 
    random_shuffle(xvector.begin(), xvector.end());
    random_shuffle(yvector.begin(), yvector.end());
    // 创建turtlesim::Spawn类型的service消息
    turtlesim::Spawn srv;
    srv.request.x = xvector[turtle_count-1];
    srv.request.y = xvector[turtle_count-1];
    srv.request.name = turtleName;
    turtle_count++;
    // 发布service请求，等待应答结果
    if (client.call(srv)&&turtle_count<=10)
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

