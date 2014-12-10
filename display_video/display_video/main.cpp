#include <QCoreApplication>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cv::namedWindow( "Example3", cv::WINDOW_NORMAL );
    cv::VideoCapture cap;
    cap.open("C:/Users/Ola/Desktop/860OKMZO/VID-20141103-WA0000.mp4");
    cv::Mat frame;
    while( 1 ) {
    cap >> frame;
    if( !frame.data ) break; // Ran out of film
    cv::imshow( "Example3", frame );
    if( cv::waitKey(33) >= 0 ) break;
    }
    return 0;

    return a.exec();
}
