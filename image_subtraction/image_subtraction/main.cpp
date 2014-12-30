#include <QCoreApplication>
#include <QImage>                       //QImage
#include <opencv2/highgui/highgui.hpp>  //Include file for every supported OpenCV function
#include <opencv2/imgproc/imgproc.hpp>  //CV color members, thresholds etc
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::Mat frame_1_grey, frame_2_grey, difference;
    int sensitivityThreshold = 50;

    //Load Resource Image
    QImage resourceImage(":/Images/cat.jpg");
    QImage resourceImage2(":/Images/cat2.jpg");

    //Convert QImage to Mat
    cv::Mat frame_1(resourceImage.height(),
                    resourceImage.width(), CV_8UC4,
                    const_cast<uchar*>(resourceImage.bits()),
                    resourceImage.bytesPerLine());
    cv::Mat frame_2(resourceImage2.height(),
                    resourceImage2.width(), CV_8UC4,
                    const_cast<uchar*>(resourceImage2.bits()),
                    resourceImage2.bytesPerLine());

    //Alternatives
    //cv::Mat frame_1 = cv::imread("C:\\Users\\Ola\\Desktop\\860OKMZO\\IMG_0009.jpg");
    //cv::Mat frame_2 = cv::imread("C:\\Users\\Ola\\Desktop\\860OKMZO\\IMG_0010.jpg");

    //create GUI windows
    cv::namedWindow("Orignial", cv::WINDOW_NORMAL);
    cv::namedWindow("Second", cv::WINDOW_NORMAL);
    cv::namedWindow("Difference", cv::WINDOW_NORMAL);

    // Convert the image to Gray
    cv::cvtColor( frame_1, frame_1_grey, CV_RGB2GRAY);
    cv::cvtColor( frame_2, frame_2_grey, CV_RGB2GRAY);

    //if resize needed optional
    //cv::resizeWindow("Orignial", 500,500);
    //cv::resizeWindow("Second", 500,500);
    //cv::resizeWindow("Difference", 500,500);

    // background subtraction
    cv::absdiff(frame_1_grey, frame_2_grey, difference);
    cv::threshold(difference, difference, sensitivityThreshold, 255, CV_THRESH_BINARY); // grayscale needed

    // Show image in window
    cv::imshow("Orignial", frame_1_grey);
    cv::imshow("Second", frame_2_grey);
    cv::imshow("Difference", difference);

    // Wait until user presses key
    cv::waitKey();

    //destroy GUI windows
    cv::destroyAllWindows();

    return 0;
}
