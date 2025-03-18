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

	string img_path = "Resources/book.jpg";
	Mat img = imread(img_path);

	float w = 396, h = 420;

	Point2f src[4] = { {73,105},{310,27},{308,429},{582,258}};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};

	Mat transform_matrix,img_warp;
	transform_matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, img_warp, transform_matrix, Point(w, h));


	//for (int i = 0; i < 4; i++)
	//{
	//	circle(img, src[i], 5, Scalar(255, 0, 0), FILLED);
	//}

	imshow("Image", img);
	imshow("Warp", img_warp);

	waitKey(0);


	return 0;
}
