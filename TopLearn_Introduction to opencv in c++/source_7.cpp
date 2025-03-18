#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
// include logger
#include <opencv2/core/utils/logger.hpp>


using namespace std;
using namespace cv;


void get_contours(Mat, Mat);


int main()
{
	
	// set logger to silent mode
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

	string img_path = "Resources/shapes.png";
	Mat img = imread(img_path);
	resize(img, img, Size(), 0.75, 0.75);

	//preprocess
	Mat img_gray, img_blur, img_canny, img_dil;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_blur, Size(3, 3), 5, 5);
	Canny(img_blur, img_canny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(img_canny, img_dil, kernel);

	get_contours(img,img_dil);
	
	imshow("Image", img);
	//imshow("Gray", img_gray);
	//imshow("Blur", img_blur);
	//imshow("Canny", img_canny);
	//imshow("Dilate", img_dil);
	

	waitKey(0);
	

	return 0;
}
//******************************//
void get_contours(Mat img, Mat img_dil)
{

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img_dil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//drawContours(img, contours, -1, Scalar(255, 50, 0), 2);

	vector<vector<Point>> ap_contours(contours.size());
	vector<Rect> bound_rect(contours.size());
	string obj_type;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		//cout << area<<endl;
		if (area > 500)
		{
			
			approxPolyDP(contours[i], ap_contours[i], 0.02 * arcLength(contours[i],true), true);
			drawContours(img, ap_contours, i, Scalar(255, 50, 0), 2);
			//cout << i << "\t" << ap_contours[i].size() << endl;

			bound_rect[i] = boundingRect(ap_contours[i]);
			//rectangle(img, bound_rect[i].tl(), bound_rect[i].br(), Scalar(50, 255, 0), 4);


			int n_corners = (int)ap_contours[i].size();
			float asp;

			if (n_corners == 3) obj_type = "Triangle";
			else if (n_corners == 4) {
			
				asp = (float)bound_rect[i].width / (float)bound_rect[i].height;
				if (asp < 1.05 && asp>0.95)
					obj_type = "Square";
				else
					obj_type = "Rectangle";
			}
			else if (n_corners == 5) obj_type = "Pentagon";
			else if (n_corners == 6) obj_type = "Hexagon";
			else if (n_corners > 6) obj_type = "Circle";



			putText(img, obj_type, { bound_rect[i].x,bound_rect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 100, 250), 2);
		}
	}


}