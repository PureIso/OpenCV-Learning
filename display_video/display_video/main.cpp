#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>  //Include file for every supported OpenCV function
#include <iostream>                     //cout

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::namedWindow("Display Video", cv::WINDOW_NORMAL);
    cv::VideoCapture videoCapture;

    if (argc <= 1)
    {
        std::cout << "No image path specified." << std::endl;
        return -1;
    }
    videoCapture.open(argv[0]);

    //Alternative
    //videoCapture.open("C:/Users/Ola/Desktop/test.mp4");

    cv::Mat frame;
    while(cv::waitKey(30) == -1)
    {
        videoCapture >> frame;
        if( !frame.data ) break; //Ran out of film
        cv::imshow("Display Video", frame);
    }
    return 0;
}
