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

	string img_path = "Resources/car.jpg";
	Mat img = imread(img_path);
	Mat img_HSV,mask;
	int hmin=0, smin=0, vmin=0;
	int hmax=179, smax=255, vmax=255;

	resize(img, img, Size(), 0.25, 0.25);
	cvtColor(img, img_HSV, COLOR_BGR2HSV);


	namedWindow("Trackbar",(640,480));
	createTrackbar("Hue min", "Trackbar", &hmin, 179);
	createTrackbar("Hue max", "Trackbar", &hmax, 179);
	createTrackbar("Sat min", "Trackbar", &vmin, 255);
	createTrackbar("Sat max", "Trackbar", &vmax, 255);
	createTrackbar("Val min", "Trackbar", &smin, 255);
	createTrackbar("Val max", "Trackbar", &smax, 255);

	imshow("Image", img);
	imshow("HSV", img_HSV);


	while (1)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);

		inRange(img_HSV, lower, upper, mask);

		imshow("Mask", mask);
		waitKey(1);
	}
	
	return 0;
}
