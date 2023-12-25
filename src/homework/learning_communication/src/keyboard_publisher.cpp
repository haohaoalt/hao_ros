/**
 * 该例程将发布turtle1/cmd_vel话题，消息类型geometry_msgs::Twist
 */
 
#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>

#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h" 
#include <boost/thread/thread.hpp>
#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
class SmartCarKeyboardTeleopNode
{
    private:
        double walk_vel_;

        geometry_msgs::Twist cmdvel_;
        ros::NodeHandle n_;
        ros::Publisher pub_;
 
    public:
        SmartCarKeyboardTeleopNode()
        {
            pub_ = n_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
            
            ros::NodeHandle n_private("~");
            n_private.param("walk_vel", walk_vel_, 0.5); 
        }
        
        ~SmartCarKeyboardTeleopNode() { }
        void keyboardLoop();
        
        void stopRobot()
        {
            cmdvel_.linear.x = 0.0;
            cmdvel_.angular.z = 0.0;
            pub_.publish(cmdvel_);
        }
};
int kfd = 0;
struct termios cooked, raw;
bool done;
void SmartCarKeyboardTeleopNode::keyboardLoop()
{
    char c;
    double max_tv = walk_vel_;
    bool dirty = false;
    int speed = 1;
    double turn = 0;
    
    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
    
    puts("Reading from keyboard");
    puts("Use WASD keys to control the turtle");
    puts("Press Shift to move faster");
    
    struct pollfd ufd;
    ufd.fd = kfd;
    ufd.events = POLLIN;
    
    for(;;)
    {
        boost::this_thread::interruption_point();
        
        // get the next event from the keyboard
        int num;
        
        if ((num = poll(&ufd, 1, 250)) < 0)
        {
            perror("poll():");
            return;
        }
        else if(num > 0)
        {
            if(read(kfd, &c, 1) < 0)
            {
                perror("read():");
                return;
            }
        }
        else
        {
        }
        
        switch(c)
        {
            case KEYCODE_W:
                max_tv = walk_vel_;
                speed = 3;
                turn = 0.5;
                dirty = true;
                break;
            case KEYCODE_S:
                max_tv = walk_vel_;
                speed = 1;
                turn = 0.5;
                dirty = true;
                break;
            case KEYCODE_A:
                max_tv = walk_vel_;
                speed = 2.0;
                turn = 0.5;
                dirty = true;
                break;
            case KEYCODE_D:
                max_tv = walk_vel_;
                speed = 0;
                turn = 0;
                dirty = true;
                break;  
            default:
                max_tv = walk_vel_;
                speed = 0;
                turn = 0;
                dirty = false;
        }
        cmdvel_.linear.x = speed*walk_vel_;
        cmdvel_.angular.z = turn;
        pub_.publish(cmdvel_);
    }
}

SmartCarKeyboardTeleopNode* tbk;
int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc,argv,"keyboard_publisher", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler);
    // 创建节点句柄    创建一个Publisher
    SmartCarKeyboardTeleopNode tbk;
    
    boost::thread t = boost::thread(boost::bind(&SmartCarKeyboardTeleopNode::keyboardLoop, &tbk));
    
    ros::spin();
    
    t.interrupt();
    t.join();
    tbk.stopRobot();
    tcsetattr(kfd, TCSANOW, &cooked);
    
    return(0);
}
