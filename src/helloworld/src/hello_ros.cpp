#include "ros/ros.h"
int main(int argc, char *argv[]){
    //init
    ros::init(argc,argv,"hello");
    //node handle
    ros::NodeHandle n;
    ROS_INFO("hello world");
    return 0;
}