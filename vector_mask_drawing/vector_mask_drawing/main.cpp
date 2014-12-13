#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

std::vector<cv::Point> points;
cv::Mat img;

void OnMouseCallback(int event, int x, int y, int flags, void* param)
{
     if  ( event == cv::EVENT_LBUTTONDOWN )
     {
         std::vector<cv::Point>* ptPtr = (std::vector<cv::Point>*)param;
         ptPtr->push_back(cv::Point(x,y));

         cv::circle(img, cv::Point(x, y), 2, cv::Scalar(255, 255, 255), CV_FILLED, 8, 0);
         cv::imshow("Orignial", img);
         std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == cv::EVENT_RBUTTONDOWN )
     {
         //cv::line(img, points[0], cv::Point(x, y), cv::Scalar(0,0,200), 3, 4);

         // create a pointer to the data as an array of points (via a conversion to a Mat() object)
         const cv::Point *pts = (const cv::Point*) cv::Mat(points).data;
         int npts = cv::Mat(points).rows;
         /*
         cv::polylines(img, &pts,&npts, 1,
                         true,                  // draw closed contour (i.e. joint end to start)
                         cv::Scalar(0,255,0),   // colour RGB ordering (here = green)
                         3,                     // line thickness
                         CV_AA, 0);
         */
         cv::fillPoly(img, &pts, &npts, 1,
                      cv::Scalar(255,255,255),
                      8,
                      0);
         cv::imshow("Orignial", img);
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
    img = cv::Mat::zeros(cv::Size(200,200), CV_8UC3);

    cv::namedWindow("Orignial", cv::WINDOW_NORMAL);
    cv::setMouseCallback("Orignial", OnMouseCallback, (void*)&points);

    cv::imshow("Orignial", img);

    return a.exec();
}
