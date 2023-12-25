#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "ros/param.h"
#include <string>
#include <iostream>
using namespace std;

//本例程序演示发布LiDAR数据相对于base_link的位置关系
//底盘坐标系和LiDAR坐标系复用这个程序，持续对外发布
//所以，要将他们的坐标平移关系设置成全局参数传进launch文件
//服务器中应该注册2个参数（1）lb之间的参数；（2）bw之间的参数


void broadcastTransform(const string& frame)
{
    ros::NodeHandle node;
    tf::TransformBroadcaster br;
    ros::Rate rate(10);

    //只需要关心，雷达-底盘这个transform即可
    double px, py, pz;
    ros::param::get("delta_x_lb",px);
    ros::param::get("delta_y_lb",py);
    ros::param::get("delta_z_lb",pz);

    tf::Transform transform;
    transform.setRotation(tf::Quaternion(0,0,0,1));
    transform.setOrigin(tf::Vector3(px,py,pz));

    //发布数据
    while(node.ok())
    {
        //坐标系的名字分别是base_link和base_laser
        br.sendTransform(tf::StampedTransform(
            transform,ros::Time::now(),"base_link",frame));
        rate.sleep();
    }
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"broadcaster");
    broadcastTransform("base_laser");
    return 0;
}
