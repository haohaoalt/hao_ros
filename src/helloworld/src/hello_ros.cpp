#include "ros/ros.h"
int main(int argc, char *argv[]){
    setlocale(LC_CTYPE, "zh_CN.utf8");
    setlocale(LC_ALL, "");

    //init
    ros::init(argc,argv,"hello");
    //node handle
    ros::NodeHandle n;
    ROS_INFO("hello world");
    ROS_INFO("Hello VSCode!!!哈哈哈哈哈哈哈哈哈哈");
    return 0;
}
