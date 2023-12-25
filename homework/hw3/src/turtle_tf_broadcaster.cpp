#include "ros/ros.h"
#include "tf/transform_broadcaster.h"
#include "turtlesim/Pose.h"//用的是这个pose！
#include <string>

using namespace std;
using namespace turtlesim;

//本例程复现教程当中的监听坐标变换

string turtle_name; //适配器都不行，只能全局

void poseCallback(const PoseConstPtr &msg)
{
    //必须要有这个常量指针
    //创建tf广播器
    static tf::TransformBroadcaster br;

    //初始化tf数据
    tf::Transform transform;
    tf::Quaternion q;
    q.setRPY(0,0,msg->theta);
    transform.setOrigin(tf::Vector3(msg->x,msg->y,0.0));
    transform.setRotation(q);//只接收q的传入

    //广播这一消息
    br.sendTransform(tf::StampedTransform(transform,ros::Time::now(),"world",turtle_name));
}

int main(int argc,char** argv)
{
    ros::init(argc,argv,"tf_listener");

    if(argc!=2)
    {
        ROS_ERROR("Need a turtle's name!");
    }
    turtle_name = argv[1];
    ros::NodeHandle n;

    //这里和launch文件的关系是，根据argv的不同，复用当前cpp代码，构建2个节点

    //由于所有的广播对外发布的都是相对于世界坐标系的坐标Twx
    //因此来源就是订阅目前的位姿（x,y）
    //转换的关系为Twx: (0,0)|x->(x,y)|w

    //订阅海龟位姿话题作为处理：
    ros::Subscriber sub = n.subscribe(turtle_name+"/pose",10,&poseCallback);
    //subscribe回调函数必须只接收1个参数，且是从相应的里面进来的
    ros::spin();
    return 0;
}
