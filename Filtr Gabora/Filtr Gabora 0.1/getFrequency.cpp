#include"getFreqency.h"
//#define PRINT_STEPS 1

double getFrequency(Mat s_img, double rotationDegrees){
	//
	const int kernel_size = 31;
	const int safe_kernel = 50;
	//const int kernel_size = s_img.cols;
	Mat rotImg;
	cv::Point2f pc((float)s_img.cols / 2., (float)s_img.rows / 2.);
	cv::Mat r = cv::getRotationMatrix2D(pc, rotationDegrees, 1.0);
	cv::warpAffine(s_img, rotImg, r, s_img.size());

#if defined(PRINT_STEPS)
	cv::namedWindow("rot", WINDOW_NORMAL);
	//cv::resizeWindow("source", 400, 400);
	imshow("rot", rotImg);
#endif

	cv::Rect myROI(10,10, kernel_size, kernel_size);
	Mat crop_img = rotImg(myROI);

#if defined(PRINT_STEPS)
		cv::namedWindow("crop", WINDOW_NORMAL);
		cv::resizeWindow("crop", 400, 400);
		imshow("crop", crop_img);
#endif

	Mat procImg;
	if (crop_img.type() == CV_8UC3) cvtColor(crop_img, crop_img, CV_BGR2GRAY);
	cv::reduce(crop_img, procImg, 0, CV_REDUCE_SUM, CV_32S);

#if defined(PRINT_STEPS)
	cv::namedWindow("proc", WINDOW_NORMAL);
	cv::resizeWindow("proc", 300, 300);
	imshow("proc", procImg);
#endif

	double average = getAvgExtremaDistance(procImg);
//	cout << "Average of differences = " << average;
	return average;
}