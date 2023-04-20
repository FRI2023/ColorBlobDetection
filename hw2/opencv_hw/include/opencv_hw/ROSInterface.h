#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include "opencv_hw/ColorFilter.h"

class ROSInterface {
protected:
    ros::NodeHandle _nodeHandle;
    image_transport::ImageTransport _imageTransport;
    image_transport::Publisher _bluePub;
    image_transport::Publisher _greenPub;
    image_transport::Publisher _redPub;
    image_transport::Publisher _bgrPub;
    image_transport::Subscriber _sub;
    ColorFilter &_colorFilter;

public:
    ROSInterface(ColorFilter &cf);
    void handleImage(const sensor_msgs::ImageConstPtr &img);
};

#endif