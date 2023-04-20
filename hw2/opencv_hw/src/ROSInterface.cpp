#include "opencv_hw/ROSInterface.h"
#include <cv_bridge/cv_bridge.h>

using namespace std;

ROSInterface::ROSInterface(ColorFilter &cf) : _colorFilter(cf), _imageTransport(_nodeHandle) {

    _sub = _imageTransport.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::handleImage, this);

    _bluePub = _imageTransport.advertise("blue_cup_topic", 1);
    _greenPub = _imageTransport.advertise("green_cup_topic", 1);
    _redPub = _imageTransport.advertise("red_cup_topic", 1);
    _bgrPub = _imageTransport.advertise("bgr_cups_topic", 1);
}

void ROSInterface::handleImage(const sensor_msgs::ImageConstPtr& img) {
    _colorFilter.processImage(cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8)->image);

    sensor_msgs::ImagePtr blueMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _colorFilter.getBlueImage()).toImageMsg();
    sensor_msgs::ImagePtr greenMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _colorFilter.getGreenImage()).toImageMsg();
    sensor_msgs::ImagePtr redMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _colorFilter.getRedImage()).toImageMsg();
    sensor_msgs::ImagePtr bgrMsg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _colorFilter.getBGRImage()).toImageMsg();

    _bluePub.publish(blueMsg);
    _greenPub.publish(greenMsg);
    _redPub.publish(redMsg);
    _bgrPub.publish(bgrMsg);

}