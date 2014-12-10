#include <QCoreApplication>
#include <QDebug>
#include <opencv2/highgui/highgui.hpp> //Include file for every supported OpenCV function

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::Mat img = cv::imread("C:/Users/Ola/Desktop/860OKMZO/IMG_0008.JPG",-1);
    if( img.empty() ) {
        qDebug() << "Empty Image";
        return -1;
    }

    cv::namedWindow( "Example1", cv::WINDOW_NORMAL );
    cv::imshow( "Example1", img );
    cv::waitKey( 0 );
    cv::destroyWindow( "Example1" );

    return a.exec();
}
