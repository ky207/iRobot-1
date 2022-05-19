#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <iostream>


using namespace std;
 
class Teleop
{
public:
    Teleop();
 
private:
    /* data */
    void callback(const sensor_msgs::Joy::ConstPtr& Joy);
    ros::NodeHandle n;
    ros::Subscriber sub ;
    ros::Publisher pub ;
    double vlinear,vangular;
    int axis_ang,axis_lin,ton;

};
 
Teleop::Teleop()
{
    n.param<int>("axis_linear", axis_lin, axis_lin);
    n.param<int>("axis_angular",axis_ang, axis_ang);
    n.param<double>("scale_linear", vlinear, vlinear);
    n.param<double>("scale_angular",vangular,vangular);
    n.param<int>("start_button",ton,ton);
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",1);
    sub = n.subscribe<sensor_msgs::Joy>("joy",10,&Teleop::callback,this);
}
 
void Teleop::callback(const sensor_msgs::Joy::ConstPtr& Joy)
{
    geometry_msgs::Twist v;
 
    if(Joy->buttons[ton])
    {
	v.linear.x =(Joy->axes[axis_lin])*vlinear;
	v.angular.z = (Joy->axes[axis_ang])*vangular;
	ROS_INFO("linear:%.3lf   angular:%.3lf",v.linear.x,v.angular.z);
	pub.publish(v);
    }
}
 
int main(int argc,char** argv)
{
    ros::init(argc, argv, "joy");
    Teleop telelog;
    ros::spin();
    return 0;
}
