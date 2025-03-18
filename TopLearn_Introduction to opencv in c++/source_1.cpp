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
	/*string img_path = "Resources/img.png";
	Mat img = imread(img_path);
	imshow("Image", img);
	waitKey(0);*/

	// read video
	/*string vid_path = "Resources/movie.mp4";
	VideoCapture cap(vid_path);
	Mat frame;

	while (true)
	{
		cap.read(frame);
		if (frame.empty())
			break;

		imshow("Video", frame);
		waitKey(20);
	}
	waitKey(0);*/


	//read webcam
	VideoCapture cap(0);
	Mat frame;

	while (true)
	{
		cap.read(frame);
		if (frame.empty())
			break;

		imshow("Webcam", frame);
		waitKey(20);
	}
	waitKey(0);


	return 0;
}
