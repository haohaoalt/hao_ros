#! /usr/bin/env python
import rospy
from turtlesim.msg import Pose

def doPose(data):
    rospy.loginfo("turtle pose: x=%.2f, y=%.2f, theta=%.2f",data.x,data.y,data.theta)

if __name__ == "__main__":
    rospy.init_node("node_sub")

    sub = rospy.Subscriber("/turtle1/pose",Pose,doPose,queue_size=1000)
    rospy.spin()