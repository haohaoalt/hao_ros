#include "ros/ros.h"
#include "tf/transform_listener.h"
#include "turtlesim/Spawn.h"
#include "geometry_msgs/Twist.h"
#include <string>

//本例程复现教程中的广播坐标信息
using namespace std;

int main(int argc,char** argv)
{
    ros::init(argc,argv,"turtle_listener");
    if(argc!=2)
    {
        ROS_ERROR("Need a turtle name");
    }

    //这里才创建第二只海龟？
    ros::NodeHandle n;
    ros::service::waitForService("/spawn");
    ros::ServiceClient add_turtle = n.serviceClient<turtlesim::Spawn>("/spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);
    //两只海龟通过2个node，不断在发送数据出去，这里只需要查询即可

    //创建tf监听器
    tf::TransformListener listener;

    ros::Rate rate(10);

    while(n.ok())
    {
        //获取turtle1和turtle2之间的tf数据
        tf::StampedTransform transform;
        try
        {
            //根据launch文件当中的节点设置来的
            listener.waitForTransform("/turtle2","/turtle1",ros::Time(0),ros::Duration(3.0));
            //waitForTransform(target_frame, source_frame)
            listener.lookupTransform("/turtle2","/turtle1",ros::Time(0),transform);
            //lookupTransform(target_frame,source_frame,time,&transform)
        }
        catch(tf::TransformException &e)
        {
            ROS_ERROR("%s",e.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        //发布速度指令
        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 4.0 * atan2(transform.getOrigin().y(),    //y2-y1
                                        transform.getOrigin().x());   //x2-x1
        //1/4秒内要调整角度
        vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(),2)   //x2-x1
                                    + pow(transform.getOrigin().y(),2)); //y2-y1

        pub.publish(vel_msg);
        rate.sleep();
    }
    return 0;
}
