#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
// include logger
#include <opencv2/core/utils/logger.hpp>


using namespace std;
using namespace cv;

int main()
{

	// set logger to silent mode
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	//define blank image
	Mat img(512, 512, CV_8UC3, Scalar(0,0,0));

	rectangle(img, Point(100, 100), Point(412, 300), Scalar(0, 100, 200),FILLED);
	circle(img, Point(256, 256), 150, Scalar(200, 150, 50), FILLED);
	line(img, Point(100, 300), Point(412, 300), Scalar(255, 255, 255), 3);

	putText(img, "OpenCV", Point(150, 250), FONT_HERSHEY_COMPLEX, 1.75, Scalar(0, 100, 200),50);

	imshow("Image", img);



	waitKey(0);


	return 0;
}
