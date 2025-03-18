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

	//read images
	string img_path = "Resources/img2.jpg";
	Mat img = imread(img_path);
	Mat img_gray,img_blur,img_canny,img_dilate,img_erode;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_blur, Size(3, 3), 0, 0);
	Canny(img_blur, img_canny, 25, 75);


	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dilate, kernel);
	erode(img_dilate, img_erode, kernel);


	imshow("Original", img);
	imshow("Gray", img_gray);
	imshow("Blur", img_blur);
	imshow("Canny", img_canny);
	imshow("Dilate", img_dilate);
	imshow("Erode", img_erode);


	waitKey(0);


	return 0;
}
