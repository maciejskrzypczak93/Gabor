#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <numeric>

using namespace cv;
using namespace std;

//Input: image segment and rotation angle
double getFrequency(Mat, double);

//Input: 1D Mat with n columns.
double getAvgExtremaDistance(Mat);