#include<ros/ros.h>
#include<string>
#include<iostream>
#include<geometry_msgs/Pose.h>
#include<nav_msgs/Odometry.h>
#include<sensor_msgs/Joy.h>
#include<geometry_msgs/Twist.h>
#include<time.h>
#include <sensor_msgs/JointState.h>
#include <robot_state_publisher/robot_state_publisher.h>

double vlinear,vangular;
int axis_ang,axis_lin,ton;
double vx, vtheta_z;
double arm1,arm2,arm3,wheel;
int btn1,btn2,btn3;

void callback(const sensor_msgs::Joy::ConstPtr& Joy)
{
    static int i = -69;
    const double degree = M_PI/180;

    if(Joy->buttons[ton])
    {
	vx =(Joy->axes[axis_lin])*vlinear;
	vtheta_z = (Joy->axes[axis_ang])*vangular;
        ROS_INFO("linear:%.3lf   angular:%.3lf",vx,vtheta_z);
    }
    if(Joy->buttons[btn1])
    {
        arm1 = i*degree;
        arm2 = i*degree;
	arm3 = i*degree;
	wheel = 0 - i*degree;
        if(i<=70)
            i++;
        else
            i=-69; 
	ROS_INFO("joint[arm1:%.3lf, arm2:%.3lf, arm3:%.3lf,wheel:%.3lf]",arm1,arm2,arm3, wheel);
    }
}
 
int main(int argc,char** argv)
{
    ros::init(argc, argv, "joy_contorller");

    ros::NodeHandle n;
    ros::Subscriber sub ;
    ros::Publisher pub ;
    ros::Publisher joint_pub ;

    ros::Rate r(20);

    n.param<int>("axis_linear", axis_lin, axis_lin);
    n.param<int>("axis_angular",axis_ang, axis_ang);
    n.param<double>("scale_linear", vlinear, vlinear);
    n.param<double>("scale_angular",vangular,vangular);
    n.param<int>("start_button",ton,ton);
    n.param<int>("arm1_button",btn1,btn1);
    n.param<int>("arm2_button",btn2,btn2);
    n.param<int>("arm3_button",btn3,btn3);

    sub = n.subscribe<sensor_msgs::Joy>("joy",10,callback);
    pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",1);
    joint_pub = n.advertise<sensor_msgs::JointState>("/joint_states", 10);  

    while(n.ok()){
        geometry_msgs::Twist v;
        sensor_msgs::JointState joint_state;

        v.linear.x =vx;
        //v.linear.y =vy;
        v.angular.z = vtheta_z;
        pub.publish(v);

        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(7);
        joint_state.position.resize(7);
	joint_state.name[0]="joint_base_arm1";
        joint_state.position[0] = arm1;
	joint_state.name[1] ="joint_base_arm2";
        joint_state.position[1] = arm2;
	joint_state.name[2] ="joint_base_arm3";
        joint_state.position[2] = arm3;
        joint_state.name[3] ="joint_base_front_right";
        joint_state.position[3] = wheel;
	joint_state.name[4] ="joint_base_front_left";
        joint_state.position[4] = wheel;
        joint_state.name[5] ="joint_base_back_right";
        joint_state.position[5] = wheel;
	joint_state.name[6] ="joint_base_back_left";
        joint_state.position[6] = wheel;
        //send the joint state and transform
        joint_pub.publish(joint_state);

        ros::spinOnce();
        r.sleep();
    }
    return 0;
}

