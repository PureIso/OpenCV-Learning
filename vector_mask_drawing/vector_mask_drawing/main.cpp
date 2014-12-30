#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

std::vector<cv::Point> points;
cv::Mat backgroundImage;

//Function prototype so I can declare the function after the main
void OnMouseCallback(int event, int x, int y, int flags, void* param);

//Main Function
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Set a black background
    backgroundImage = cv::Mat::zeros(cv::Size(500,500), CV_8UC3);

    cv::namedWindow("Orignial", cv::WINDOW_NORMAL);
    cv::setMouseCallback("Orignial", OnMouseCallback, (void*)&points);

    cv::imshow("Orignial", backgroundImage);

    cv::waitKey(0);
    return 0;
}

//Get and Set mouse point in the window
void OnMouseCallback(int event, int x, int y, int flags, void* param)
{
    (void)flags; //unused

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::vector<cv::Point>* pointPtr = (std::vector<cv::Point>*)param;
        pointPtr->push_back(cv::Point(x,y));

        //draw a dot on the image
        cv::circle(backgroundImage, cv::Point(x, y), 2, cv::Scalar(255, 255, 255), CV_FILLED, 8, 0);
        //display new image
        cv::imshow("Orignial", backgroundImage);
        //output coordinate
        std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if (event == cv::EVENT_RBUTTONDOWN)
     {
        //create a pointer to the data as an array of points (via a conversion to a Mat() object)
        const cv::Point *allPoints = (const cv::Point*) cv::Mat(points).data;
        int numberOfPoints = cv::Mat(points).rows;

        //Create line
        //cv::line(img, points[0], cv::Point(x, y), cv::Scalar(0,0,200), 3, 4);

        /*
        * Create Polyline
        cv::polylines(img, &allPoints,&numberOfPoints, 1,
                     true,                  // draw closed contour (i.e. joint end to start)
                     cv::Scalar(0,255,0),   // colour RGB ordering (here = green)
                     3,                     // line thickness
                     CV_AA, 0);
        */

        //Create Polyline
        cv::fillPoly(backgroundImage, &allPoints, &numberOfPoints, 1,
                  cv::Scalar(255,255,255),
                  8,
                  0);
        cv::imshow("Orignial", backgroundImage);
        std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
    }
}
