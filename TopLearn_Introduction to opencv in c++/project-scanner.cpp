#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

// include logger
#include <opencv2/core/utils/logger.hpp>


using namespace std;
using namespace cv;


Mat preprocess_img(Mat);
vector<Point> get_contours(Mat);
void draw(Mat, vector<Point>, Scalar);
vector<Point> reorder_points(vector<Point>);
vector<Point> reorder_pro(vector<Point>);
Point get_center(vector<Point>);
Mat get_warp(Mat, vector<Point>, float, float);


int main()
{
	// set logger to silent mode
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);


	string img_path = "Resources/book.jpg";
	Mat img = imread(img_path);
	Mat img_preprocessed,img_warp,img_crop;
	vector<Point> initial_points,reordered_points;
	float w = 420, h = 596;

	// preprocess
	img_preprocessed = preprocess_img(img);
	// get contours
	initial_points = get_contours(img_preprocessed);
	
	if (initial_points.size() == 4)
	{
		//draw(img, initial_points, Scalar(255, 0, 0));
		reordered_points = reorder_pro(initial_points);
		//draw(img, reordered_points, Scalar(0,255, 0));
		
		// warp
		img_warp = get_warp(img, reordered_points, w, h);

		// postprocess

		int crop_size = 20;
		Rect roi(crop_size, crop_size, w - (2 * crop_size), h - (2 * crop_size));
		img_crop = img_warp(roi);




		imshow("image", img);
		imshow("preprocess", img_preprocessed);
		imshow("warp", img_warp);
		imshow("crop", img_crop);

		waitKey(0);
	}
	else
	{
		cout << "Nothing detected to scan!";
	}
	return 0;
}
//*****************************************//
// preprocess image for next step
Mat preprocess_img(Mat img)
{
	Mat img_gray, img_blur, img_canny, img_dil;
	Mat  kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_blur, Size(3, 3), 0, 0);
	Canny(img_blur, img_canny, 50, 100);
	//dilate(img_canny, img_dil, kernel);

	return img_canny;
}
//*****************************************//
// find the biggst contour with 4 points
vector<Point> get_contours(Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hiearchy;

	findContours(img, contours, hiearchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> ap_contours(contours.size());

	vector<Point> contour;
	int max_area = 0;


	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		if (area > 500)
		{
			approxPolyDP(contours[i], ap_contours[i], 0.01 * arcLength(contours[i], true), true);
			if (area > max_area && ap_contours[i].size() == 4)
			{
				max_area = area;
				contour = { ap_contours[i][0],ap_contours[i][1], ap_contours[i][2], ap_contours[i][3] };
			}
		}
	}
	return contour;
}
//*****************************************//
// draw contour
void draw(Mat img, vector<Point> points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(img, points[i], 7, color, FILLED);
		putText(img, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 2);
	}
}
//*****************************************//
vector<Point> reorder_points(vector<Point> points)
{
	vector<Point> reordered_points;
	vector<int> co_sum, co_sub;
	for (int i = 0; i < points.size(); i++)
	{
		co_sum.push_back(points[i].x + points[i].y);
		co_sub.push_back(points[i].x - points[i].y);
	}
	reordered_points.push_back(points[min_element(co_sum.begin(), co_sum.end()) - co_sum.begin()]);// 0
	reordered_points.push_back(points[max_element(co_sub.begin(), co_sub.end()) - co_sub.begin()]);// 1
	reordered_points.push_back(points[min_element(co_sub.begin(), co_sub.end()) - co_sub.begin()]);// 2
	reordered_points.push_back(points[max_element(co_sum.begin(), co_sum.end()) - co_sum.begin()]);// 3


	return reordered_points;
}
//*****************************************//
vector<Point> reorder_pro(vector<Point> points)
{
	vector<Point> reordered_points;
	Point center = get_center(points);
	Point t;
	int order_index[4]{};
	for (int i = 0; i < 4; i++)
	{
		t = points[i] - center;
		bool x = t.x > 0, y = t.y > 0;

		if (x && y)			order_index[3] = i;
		else if(x && !y)	order_index[1] = i;
		else if(!x && y)	order_index[2] = i;
		else				order_index[0] = i;
	}
	for (int i = 0; i < 4; i++)
		reordered_points.push_back(points[order_index[i]]);

	return reordered_points;
}
//*****************************************//
Point get_center(vector<Point> points)
{
	double md1, md2, x, y;
	md1 = ((double)points[0].y - (double)points[2].y) / ((double)points[0].x - (double)points[2].x);
	md2 = ((double)points[1].y - (double)points[3].y) / ((double)points[1].x - (double)points[3].x);

	x = ((md1 * (double)points[0].x) - (double)points[0].y - (md2 * (double)points[1].x) + (double)points[1].y) / (md1 - md2);
	y = md1 * (x - (double)points[0].x) + (double)points[0].y;


	return Point(x, y);
}
//*****************************************//
Mat get_warp(Mat img, vector<Point> corners, float w, float h)
{
	Mat img_warp;
	Point2f src[4] = { corners[0],corners[1] ,corners[2] ,corners[3]};
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h}};
	
	Mat transform = getPerspectiveTransform(src, dst);
	warpPerspective(img, img_warp, transform, Point(w, h));

	return img_warp;
}
