#include "opencv_hw/ROSInterface.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "color_blob_detection");
    ColorFilter cf;
    ROSInterface ri(cf);
    ros::spin();
    return 0;
}