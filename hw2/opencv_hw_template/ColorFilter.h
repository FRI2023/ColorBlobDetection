#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;
    cv::Mat _blueSubMatrix;
    cv::Mat _blueThresh;
    cv::Mat _blueMask;
    cv::Mat _blueFinal;
    cv::Mat _greenSubMatrix;
    cv::Mat _greenThresh;
    cv::Mat _greenMask;
    cv::Mat _greenFinal;
    cv::Mat _redSubMatrix;
    cv::Mat _redThresh;
    cv::Mat _redMask;
    cv::Mat _redFinal;
    cv::Mat _bgrMask;
    cv::Mat _bgrFinal;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    void showResult();
};

#endif