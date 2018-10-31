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

using namespace std;

std::string name_rgb = "/home/jh/data/rgb/";
std::string name_depth = "/home/jh/data/depth/";
std::string namer_txt = "/home/jh/data/name_r.txt";
std::string named_txt = "/home/jh/data/name_d.txt";

ofstream f1;
ofstream f2;

void img_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
//    cv_bridge::CvImagePtr image_ptr=cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::RGB8);

    cv_bridge::CvImageConstPtr cv_ptrRGB;
    try
    {
        cv_ptrRGB = cv_bridge::toCvShare(img_msg,sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }



    cv::Mat image = cv_ptrRGB->image;
    double timestamp = cv_ptrRGB->header.stamp.toSec();

    char s[50];
    sprintf(s,"%.6f",timestamp);
    std::string m=s;

    std::string name = name_rgb + m + ".png";

    cv::imshow("image",image);

    cv::imwrite(name,image);

    f1<< m <<endl;

    cv::waitKey(10);
    std::cout<<"save:"<<name<<std::endl;

}
void depth_callback(const sensor_msgs::ImageConstPtr &img_msg)
{
//    cv_bridge::CvImagePtr image_ptr=cv_bridge::toCvCopy(img_msg,sensor_msgs::image_encodings::MONO8);
    cv_bridge::CvImageConstPtr cv_ptrD;
    try
    {
        cv_ptrD = cv_bridge::toCvShare(img_msg);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat image=cv_ptrD->image;
    double timestamp=cv_ptrD->header.stamp.toSec();

    char s[50];
    sprintf(s,"%.6f",timestamp);
    std::string m=s;

    std::string name = name_depth+m+".png";

    f2<< m <<endl;

    cv::imwrite(name,image);
}

int main(int argc, char *argv[])
{

    f1.open(namer_txt.c_str());
    f2.open(named_txt.c_str());
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
