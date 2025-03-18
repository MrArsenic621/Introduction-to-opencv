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
	Mat img_resize,img_crop;

	cout << img.size() << endl;
	resize(img, img_resize,Size(),0.5,0.5);


	Rect roi(250, 350, 350, 200);
	img_crop = img(roi);



	imshow("Original", img);
	imshow("Resize", img_resize);
	imshow("Crop", img_crop);

	


	waitKey(0);


	return 0;
}
