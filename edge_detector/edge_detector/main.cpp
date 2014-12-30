#include <QCoreApplication>
#include <QImage>                       //QImage
#include <opencv2/highgui/highgui.hpp>  //Include file for every supported OpenCV function
#include <opencv2/imgproc/imgproc.hpp>  //CV color members, thresholds etc

cv::Mat image_gray;
int max_corners = 100;
float quality = 0.01;
int min_distance = 40;      //distance between returned corners - jags on image made me increase this

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Load Resource Image
    QImage resourceImage(":/Images/box.png");
    //Convert QImage to Mat
    cv::Mat image(resourceImage.height(),
          resourceImage.width(), CV_8UC4,
          const_cast<uchar*>(resourceImage.bits()),
          resourceImage.bytesPerLine());

    //Convert the image
    cv::cvtColor(image, image_gray, CV_RGB2GRAY);
    cv::namedWindow("Corners");

    if(image_gray.empty()) return -1;

    max_corners = cv::max(1, max_corners);
    cv::vector<cv::Point2d> corners;
    cv::goodFeaturesToTrack(image_gray, corners, max_corners, quality, min_distance);

    // Draw the corners as little circles
    cv::Mat image_corners = image.clone();
    for(unsigned int i = 0; i < corners.size(); i++)
    {
        cv::circle(image_corners, corners[i], 4, CV_RGB(255, 0, 0), -1);
    }
    cv::imshow("Corners", image_corners);

    // Wait until user presses key
    cv::waitKey();
    cv::destroyWindow("Corners");
    return 0;
}
