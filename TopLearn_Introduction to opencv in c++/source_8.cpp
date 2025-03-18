#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
// include logger
#include <opencv2/core/utils/logger.hpp>


using namespace std;
using namespace cv;



int main()
{

	// set logger to silent mode
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	string img_path = "Resources/face.jpg";
	Mat img = imread(img_path);

	CascadeClassifier face_cascade, eye_cascade;
	face_cascade.load("Resources/haarcascade_frontalface_default.xml");
	eye_cascade.load("Resources/haarcascade_eye.xml");


	if (face_cascade.empty()) cout << "Cascade not loaded!" << endl;
	if (eye_cascade.empty()) cout << "Cascade not loaded!" << endl;

	vector<Rect> faces, eyes;
	face_cascade.detectMultiScale(img, faces, 1.1, 5);
	eye_cascade.detectMultiScale(img, eyes, 1.1, 5);

	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 0), 3);
	}
	for (int i = 0; i < eyes.size(); i++)
	{
		rectangle(img, eyes[i].tl(), eyes[i].br(), Scalar(0, 0, 255), 3);
	}


	imshow("Image", img);

	waitKey(0);


	return 0;
}