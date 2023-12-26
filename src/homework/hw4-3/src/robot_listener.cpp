/**
 * 该例程监听tf数据，并计算、发布turtle2的速度指令
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv)
{
	// 初始化ROS节点
	ros::init(argc, argv, "robot_tf_listener");
        // 创建节点句柄
	ros::NodeHandle node;

	// 创建tf的监听器
	tf::TransformListener listener;
	ros::Rate rate(10.0);
	while (node.ok())
	{
		//我们将在base_laser帧中创建一个要转换为base_link帧的点
		geometry_msgs::PointStamped laser_point;
                laser_point.header.frame_id = "base_laser";
        
        	//我们将在我们的简单示例中使用最近可用的转换
        	laser_point.header.stamp = ros::Time();
        
        	//laser_point检测点获取
        	laser_point.point.x = 0.3;
        	laser_point.point.y = 0.0;
        	laser_point.point.z = 0.0;     
        	try
		{
            		// 等待获取监听信息base_link和base_laser
            		listener.waitForTransform("base_link", "base_laser", ros::Time(0), ros::Duration(3.0));
            		geometry_msgs::PointStamped base_point;
            		listener.transformPoint("base_link", laser_point, base_point);

            		ROS_INFO("base_laser: (%.2f, %.2f. %.2f) -----> base_link: (%.2f, %.2f, %.2f) at time %.2f",
                		laser_point.point.x, laser_point.point.y, laser_point.point.z,
                		base_point.point.x, base_point.point.y, base_point.point.z, base_point.header.stamp.toSec());
        	}
        	catch(tf::TransformException& ex)
		{
            		ROS_ERROR("Received an exception trying to transform a point from \"base_laser\" to \"base_link\": %s", ex.what());
        	}
		rate.sleep();
	}
	return 0;
};
