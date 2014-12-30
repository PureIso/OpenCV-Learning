#include <QCoreApplication>
#include <QImage>                       //QImage
#include <opencv2/highgui/highgui.hpp>  //Include file for every supported OpenCV function
#include <iostream>                     //cout

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Load Resource Image
    QImage resourceImage(":/Images/cat.jpg");
    //Convert QImage to Mat
    cv::Mat img(resourceImage.height(),
                resourceImage.width(), CV_8UC4,
                const_cast<uchar*>(resourceImage.bits()),
                resourceImage.bytesPerLine());

    //Alternatively
    //cv::Mat img = cv::imread(imagePath,-1);

    //or from command line
    /*
    if (argc <= 1)
    {
        std::cout << "No image path specified.";
        return -1;
    }
    cv::Mat img = cv::imread(argv[0],-1);
    */

    //Image Image is empty return
    if(img.empty())
    {
        std::cout << "Empty Image";
        return -1;
    }
    else
    {
        cv::namedWindow( "Display Image", cv::WINDOW_NORMAL);
        cv::imshow("Display Image", img);
        cv::waitKey(0);
        cv::destroyWindow("Display Image");
        return 0;
    }
}
