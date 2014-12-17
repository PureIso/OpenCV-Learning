#include <QCoreApplication>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat frame, imgHSV, imgThresholded, imgBaseBlack;
int low_h, low_s, low_v, high_h, high_s, high_v;
int iLastX = -1;
int iLastY = -1;

int convert_mspaint_hue_to_opencv_hue(int x)
{
    return (int)(x * (180/240));
}

int convert_mspaint_others_to_opencv_others(int x)
{
    return (int)((x/240) * 255 );
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cv::VideoCapture cap(0);
    /*
    Lower[17, 15, 100], Higher[50, 56, 200]),Red
    Lower([86, 31, 4], Higher[220, 88, 50]),Blue
    Lower([25, 146, 190], Higher[62, 174, 250]),Yellow
    Lower([103, 86, 65], Higher[145, 133, 128])Grey
    */

    /*
    It should be noted in MS Paint, the hue values range from 0-239, 
    while OpenCV’s hue values range from 0-179. So any hue value you take from MS Paint 
    for use in your code will need to be scaled using the factor 180 / 240. 
    A MS Paint Hue value of 147 for example becomes 147 * (180/240) = 110 in OpenCV.
    */
    low_h = convert_mspaint_hue_to_opencv_hue(219);
    high_h = convert_mspaint_hue_to_opencv_hue(239);
    /*In MS Paint the Saturation and Luminosity are also in the range 0-239 while 
    the OpenCV equivalents are in the range 0..255 (8 bit encoding). 
    A MS Paint saturation of 210, for example, becomes (210/240) * 255 = 223 in OpenCV.
    */
    low_s = convert_mspaint_others_to_opencv_others(240);
    high_s = convert_mspaint_others_to_opencv_others(240);

    low_v = convert_mspaint_others_to_opencv_others(120);
    high_v = convert_mspaint_others_to_opencv_others(240);

    //check if the file was opened properly
    if(!cap.isOpened())
    {
        std::cout << "Capture could not be opened succesfully" << std::endl;
        return -1;
    }
    cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    //Create trackbars in "Control" window
    cv::createTrackbar("LowH", "Control", &low_h, 179); //Hue (0 - 179)
    cv::createTrackbar("HighH", "Control", &high_v, 179);

    cv::createTrackbar("LowS", "Control", &low_s, 255); //Saturation (0 - 255)
    cv::createTrackbar("HighS", "Control", &high_s, 255);

    cv::createTrackbar("LowV", "Control", &low_v, 255);//Value (0 - 255)
    cv::createTrackbar("HighV", "Control", &high_v, 255);

    cv::namedWindow("Video", cv::WINDOW_NORMAL);
    cv::namedWindow("Segmentation", cv::WINDOW_NORMAL);

    cv::Rect bounding_rect;
    std::vector< std::vector<cv::Point> > contours; // Vector for storing contour
    cv::vector<cv::Vec4i> hierarchy;

    while(char(cv::waitKey(1)) != 'q' && cap.isOpened())
    {
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
