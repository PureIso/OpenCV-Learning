#include <QCoreApplication>

#include "opencv2/highgui/highgui.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::Mat frame;
    cv::VideoCapture cap;

    cap.open(0);

    if (!cap.isOpened()) {
        std::cout << "Failed to open video capture device 0\n";
        return -1;
    }

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

    cv::namedWindow("picture window", CV_WINDOW_AUTOSIZE);

    while (cv::waitKey(30) == -1) {
        cap >> frame;
        if(frame.data)
            cv::imshow("picture window", frame);
    }

    return a.exec();
}
