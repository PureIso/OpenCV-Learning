#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>
#include<iostream>
#include<vector>

const int nmixtures =3;
const bool bShadowDetection = false;
const int history = 5;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::Mat frame;
    cv::Mat back;
    cv::Mat fore;
    cv::VideoCapture cap(0);
    cv::BackgroundSubtractorMOG2 bg(history,nmixtures,bShadowDetection);

    cv::Rect bounding_rect;
    std::vector< std::vector<cv::Point> > contours; // Vector for storing contour
    cv::vector<cv::Vec4i> hierarchy;

    cv::namedWindow("Frame");
    cv::namedWindow("Background");

    for(;;)
    {
        cap >> frame;
        if(cv::waitKey(30) >= 0) break;
        if(frame.empty()) continue;

        bg.operator ()(frame,fore);
        bg.getBackgroundImage(back);


        //morphological opening (remove small objects from the foreground)
        cv::erode(fore, fore, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::dilate(fore, fore, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        //morphological closing (fill small holes in the foreground)
        cv::dilate(fore, fore, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::erode(fore, fore, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        cv::findContours(fore, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

        if(contours.size() > 0)
        {
            bounding_rect = cv::boundingRect(contours[0]);
            cv::rectangle(frame, bounding_rect,  cv::Scalar(00,0,255),2, 8,0);
        }

        cv::drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
        cv::imshow("Frame",frame);
        cv::imshow("Background",back);

    }

    return a.exec();
}
