#include <QCoreApplication>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::Mat frame;
    cv::VideoCapture videoCapture;

    videoCapture.open(0);

    if (!videoCapture.isOpened()) {
        std::cout << "Failed to open video capture device 0\n";
        return -1;
    }

    //Define width and height optional
    //videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    //videoCapture.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    cv::namedWindow("Display Webcam", CV_WINDOW_AUTOSIZE);

    while (cv::waitKey(30) == -1)
    {
        videoCapture >> frame;
        if(frame.data) cv::imshow("Display Webcam", frame);
    }
    return 0;
}
