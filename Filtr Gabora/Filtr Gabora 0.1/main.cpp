#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include "GaborFilter.h"
using namespace std;
using namespace cv;

int kernel_size_slider = 31;// do trackbara (wartoœæ suwaka)
int psi_slider=0; // do trackbara (wartoœæ suwaka)
int theta_slider=0; // do trackbara (wartoœæ suwaka)
int sigma_slider=38; // do trackbara (wartoœæ suwaka)
int lm_slider=100; // do trackbara (wartoœæ suwaka)
int gm_slider=20;
int method_slider = 2;

GaborFilter filter;
Mat image;

Mat image_color;
Mat Gx, Gy;	///gradient images
Mat orientation_map; /// matrix containing orientation of (group of) pixels
Mat image_enhanced; /// image after enhancement
Mat orientation_image; /// image with marked orientation of group of pixels
Mat angle_matrix;	///angle matrix for method 3
Mat magnitude_matrix; ///magnitude matrix for method 3

string file_name;

void progowanie_trackbar(int, void *)
{
	//cout << alpha_slider << endl;

	filter.kernel_size = kernel_size_slider;
	filter.psi = psi_slider;
	filter.theta = theta_slider;
	filter.sigma = sigma_slider*0.1;
	filter.lm = sigma_slider*0.1;
	filter.gm = sigma_slider*0.1;
	filter.method = method_slider+1;

	std::string imgDest = "./obrazy/";
	imgDest.append(file_name);

	image = imread("obrazy/" + file_name, 0);
	if (!image.data)                              // Check for invalid input
	{
		cout << endl << "Brak pliku o podanej nazwie." << std::endl;
		system("pause");
		//return -1;
	}

	cout << endl << "Obliczenia..." << std::endl;

	cvtColor(image, image_color, CV_GRAY2BGR);
	filter.gradientImage(image, Gx, Gy);	///gradient computation

	switch (filter.method) ///choosing right computation of orientation method
	{
	case 1:
	{
		filter.getOrientationMap(image_color, Gx, Gy, orientation_map, orientation_image);
		break;
	}
	case 2:
	{
		filter.getOrientationMap(image_color, Gx, Gy, orientation_map, orientation_image);
		break;
	}
	case 3:
	{
		phase(Gx, Gy, angle_matrix, false);
		magnitude(Gx, Gy, magnitude_matrix);

		cvtColor(image, orientation_image, CV_GRAY2BGR);
		normalize(magnitude_matrix, magnitude_matrix, 0, 1, NORM_MINMAX);
		filter.getOrientationMapGradient(angle_matrix, magnitude_matrix, 31, orientation_map, orientation_image);
		break;
	}
	default:
	{
		cout << "Blad. Wybrano nieistniejaca metode tworzenia mapy orientacji. Sprawdz parametr 'method' obiektu klasy GaborFilter" << endl;
		system("pause");
		//return 0;
	}
	}



	filter.enhanceImage(image, image_enhanced, orientation_map, orientation_image);

	//cout << endl << "SPACJA - zmiana widoku" << endl;
	//cout << "ESC - koniec" << endl;
	//int key = 0;
	//while (1)	///displaying results
	//{
		//imshow("Image before/after", image);
		//key = waitKey(0);
		//if (key == 27) break;
		//imshow("Image before/after", orientation_image);
		//key = waitKey(0);
		//if (key == 27) break;
			
		imshow("Image before/after", image_enhanced);
		
		imshow("Image", image);

		//key = waitKey(0);
		//if (key == 27) break;
	//}
}

int main(void)
{
	cout << "Podaj nazwe pliku (z rozszerzeniem): ";
	cin >> file_name;

	
	namedWindow("Image before/after", 0);
	resizeWindow("Image before/after", 300, 800);
	namedWindow("Image", 0);
	


	createTrackbar("kernel_size", "Image before/after", &kernel_size_slider, 100, progowanie_trackbar);
	createTrackbar("psi", "Image before/after", &psi_slider, 360, progowanie_trackbar);
	createTrackbar("theta", "Image before/after", &theta_slider, 360, progowanie_trackbar);
	createTrackbar("sigma", "Image before/after", &sigma_slider, 300, progowanie_trackbar);
	createTrackbar("lm", "Image before/after", &lm_slider, 360, progowanie_trackbar);
	createTrackbar("gm", "Image before/after", &gm_slider, 300, progowanie_trackbar);
	createTrackbar("method (+1)", "Image before/after", &method_slider, 2, progowanie_trackbar);
	

	//int a;
	//cin >> a;
	//return 0;
	waitKey();
}