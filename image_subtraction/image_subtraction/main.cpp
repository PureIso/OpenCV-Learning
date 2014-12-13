#include <QCoreApplication>
#include <QtDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == cv::EVENT_LBUTTONDOWN )
     {
          std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == cv::EVENT_RBUTTONDOWN )
     {
          std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == cv::EVENT_MBUTTONDOWN )
     {
          std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if ( event == cv::EVENT_MOUSEMOVE )
     {
          std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
     }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::Mat frame_1 = cv::imread("C:\\Users\\Ola\\Desktop\\860OKMZO\\IMG_0009.jpg");
    cv::Mat frame_2 = cv::imread("C:\\Users\\Ola\\Desktop\\860OKMZO\\IMG_0010.jpg");

    cv::Mat frame_1_grey, frame_2_grey;

    cv::Mat difference;
    //create GUI windows
    cv::namedWindow("Orignial", cv::WINDOW_NORMAL);
    cv::namedWindow("Second", cv::WINDOW_NORMAL);
    cv::namedWindow("Difference", cv::WINDOW_NORMAL);

    cv::setMouseCallback("Orignial", CallBackFunc, NULL);

    // Convert the image to Gray
    cv::cvtColor( frame_1, frame_1_grey, CV_RGB2GRAY);
    cv::cvtColor( frame_2, frame_2_grey, CV_RGB2GRAY);

    cv::resizeWindow("Orignial", 500,500);
    cv::resizeWindow("Second", 500,500);
    cv::resizeWindow("Difference", 500,500);

    // background subtraction
    cv::absdiff(frame_1_grey, frame_2_grey, difference);
    cv::threshold(difference, difference, 50, 255, CV_THRESH_BINARY); // grayscale needed
    // Show image in window
    cv::imshow("Orignial", frame_1_grey);
    cv::imshow("Second", frame_2_grey);
    cv::imshow("Difference", difference);

    // Wait until user presses key
    cv::waitKey();

    //destroy GUI windows
    cv::destroyAllWindows();

    return a.exec();
}
