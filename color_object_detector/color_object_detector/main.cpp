#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat frame, imgHSV, imgThresholded, imgBaseBlack;
int low_h = 174, low_s = 130, low_v = 254;
int high_h = 181, high_s = 250, high_v = 254;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::VideoCapture cap(0);

    //check if the file was opened properly
    if(!cap.isOpened())
    {
        std::cout << "Capture could not be opened succesfully" << std::endl;
        return -1;
    }

    cv::namedWindow("Video", cv::WINDOW_NORMAL);
    cv::namedWindow("Segmentation", cv::WINDOW_NORMAL);

    cv::Rect bounding_rect;
    std::vector< std::vector<cv::Point> > contours; // Vector for storing contour
    cv::vector<cv::Vec4i> hierarchy;

    while(char(cv::waitKey(1)) != 'q')
    {
        if(!cap.isOpened()) break;

        cap >> frame;
        //Create a black image with the size as the camera output
        imgBaseBlack = cv::Mat::zeros(frame.size(), CV_8UC3);

        // Check if we have frame some cameras are slow to start
        if(frame.empty()) continue;

        /*
        Converts an image from one color space to another. 
        Convert the captured frame from BGR to HSV
        Parameters: src – input image: 8-bit unsigned, 16-bit unsigned ( CV_16UC... ), or single-precision floating-point.
                    dst – output image of the same size and depth as src.
                    code – color space conversion code (see the description below).
                    dstCn – number of channels in the destination image; if the parameter is 0, the number of the channels is derived automatically from src and code .
        */
        cv::cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV); 

        /*
        Checks if array elements lie between the elements of two other arrays.
        Parameters: src – first input array.
                    lowerb – inclusive lower boundary array or a scalar.
                    upperb – inclusive upper boundary array or a scalar.
                    dst – output array of the same size as src and CV_8U type.
        */
        cv::inRange(imgHSV, cv::Scalar(low_h, low_s, low_v), cv::Scalar(high_h, high_s, high_v), imgThresholded);

        //morphological opening (remove small objects from the foreground)
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        //morphological closing (fill small holes in the foreground)
        cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
        cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

        cv::findContours(imgThresholded, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
        if(contours.size() > 0)
        {
            bounding_rect = cv::boundingRect(contours[0]);
            cv::rectangle(frame, bounding_rect,  cv::Scalar(00,0,255),2, 8,0);
        }

        frame = frame + imgBaseBlack;
        cv::imshow("Video", frame);
        cv::imshow("Segmentation", imgThresholded);
    }

    return a.exec();
}
