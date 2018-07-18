//
// Created by jh on 18-7-18.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include <ros/ros.h>
#include <std_msgs/Header.h>
#include <std_msgs/Float32.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/opencv.hpp>

std::string name_rgb="/home/jh/data/rgb/";
std::string name_depth="/home/jh/data/depth/";


void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    cv_bridge::CvImagePtr image_ptr=cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::RGB8);
    cv::Mat image=image_ptr->image;
    double timestamp=image_ptr->header.stamp.toSec();

    char s[50];
    sprintf(s,"%.6f",timestamp);
    std::string m=s;

    std::string name=name_rgb+m+".png";
    cv::imwrite(name,image);
    std::cout<<"save:"<<name<<std::endl;

}
void depth_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
    cv_bridge::CvImagePtr image_ptr=cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::MONO8);
    cv::Mat image=image_ptr->image;
    double timestamp=image_ptr->header.stamp.toSec();

    char s[50];
    sprintf(s,"%.6f",timestamp);
    std::string m=s;

    std::string name=name_rgb+m+".png";
    cv::imwrite(name,image);
}

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"save_image");
    ros::NodeHandle n("~");

    std::string config_file;
    std::string image_topic="/camera/rgb/image_raw";
    std::string depth_topic="/camera/depth_registered/image_raw";
    ros::Subscriber sub_image = n.subscribe(image_topic,1,img_callback);
    ros::Subscriber sub_depth = n.subscribe(depth_topic,1,depth_callback);
    ros::spin();

    return 0;
}
