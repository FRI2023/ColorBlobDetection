#include "ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {
    // PROBLEM 1
    // imshow("color", _frame);

    // PROBLEM 2: B
    // imshow("blue", _chans[0]);
    // PROBLEM 2: G
    // imshow("green", _chans[1]);
    // PROBLEM 2: R
    // imshow("red", _chans[2]);

    // PROBLEM 3: Blue Subtraction
    // imshow("blue - red", _blueSubMatrix);

    // PROBLEM 3: Blue Threshold
    // imshow("blue threshold", _blueThresh);

    // PROBLEM 3: Largest Blue Blob
    // imshow("largest blue blob", _blueMask);

    // PROBLEM 3: Blue Cup Only
    // imshow("largest blue blob", _blueFinal);

    // PROBLEM 4: Green Subtraction
    // imshow("green - blue", _greenSubMatrix);

    // PROBLEM 4: Green Threshold
    // imshow("green threshold", _greenThresh);

    // PROBLEM 4: Largest Green Blob
    // imshow("largest green blob", _greenMask);

    // PROBLEM 4: Green Cup Only
    // imshow("largest green blob", _greenFinal);

    // PROBLEM 5: Red Subtraction
    // imshow("red - green", _redSubMatrix);

    // PROBLEM 5: Red Threshold
    // imshow("red threshold", _redThresh);

    // PROBLEM 5: Largest Red Blob
    // imshow("largest red blob", _redMask);

    // PROBLEM 5: Red Cup Only
    // imshow("largest red blob", _redFinal);

    // PROBLEM 6: ALL THREE
    imshow("all three cups", _bgrFinal);
    waitKey(50);
}

void ColorFilter::findBlue() {
    // calculates blue - red
    subtract(_chans[0], _chans[2], _blueSubMatrix);

    // thresholds the subtracted matrix
    threshold(_blueSubMatrix, _blueThresh, 50, 255, cv::THRESH_BINARY);

    // finds all contours in the image
    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_blueThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // find size and index of largest contour in the image
    int maxSize = 0;
    int maxIndex = 0;
    for(int i = 0; i < contours.size(); i++) {
        int currSize = cv::contourArea(contours[i]);
        if(currSize > maxSize) {
            maxSize = currSize;
            maxIndex = i;
        }
    }

    // create mask with largest blue image contour
    _blueMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_blueMask, contours, maxIndex, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    // copy blue cup pixels from original image using the mask
    _blueFinal = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_blueFinal, _blueMask);
}

void ColorFilter::findGreen() {
    // calculates green - blue
    subtract(_chans[1], _chans[0], _greenSubMatrix);

    // thresholds the subtracted matrix
    threshold(_greenSubMatrix, _greenThresh, 50, 255, cv::THRESH_BINARY);

    // finds all contours in the image
    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_greenThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // find size and index of largest contour in the image
    int maxSize = 0;
    int maxIndex = 0;
    for(int i = 0; i < contours.size(); i++) {
        int currSize = cv::contourArea(contours[i]);
        if(currSize > maxSize) {
            maxSize = currSize;
            maxIndex = i;
        }
    }

    // create mask with largest green image contour
    _greenMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_greenMask, contours, maxIndex, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    // copy green cup pixels from original image using the mask
    _greenFinal = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_greenFinal, _greenMask);
}

void ColorFilter::findRed() {
    // calculates red - green
    subtract(_chans[2], _chans[1], _redSubMatrix);

    // thresholds the subtracted matrix
    threshold(_redSubMatrix, _redThresh, 50, 255, cv::THRESH_BINARY);

    // finds all contours in the image
    vector<cv::Mat> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_redThresh, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    // find size and index of largest contour in the image
    int maxSize = 0;
    int maxIndex = 0;
    for(int i = 0; i < contours.size(); i++) {
        int currSize = cv::contourArea(contours[i]);
        if(currSize > maxSize) {
            maxSize = currSize;
            maxIndex = i;
        }
    }

    // create mask with largest red image contour
    _redMask = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC1);
    drawContours(_redMask, contours, maxIndex, cv::Scalar(255), cv::LineTypes::FILLED, 8, hierarchy);

    // copy red cup pixels from original image using the mask
    _redFinal = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_redFinal, _redMask);
}

void ColorFilter::findBGR() {
    // take bitwise or of all 3 masks for each color to get the overall mask
    cv::bitwise_or(_blueMask, _greenMask, _bgrMask);
    cv::bitwise_or(_bgrMask, _redMask, _bgrMask);

    // copy red cup pixels from original image using the mask
    _bgrFinal = cv::Mat::zeros(_frame.rows, _frame.cols, CV_8UC3);
    _frame.copyTo(_bgrFinal, _bgrMask);
}