#include"getFreqency.h"
//#define USE_MINIMA
#define USE_MAXIMA
//#define CMD_PRINT

double getAvgExtremaDistance(Mat procImg){

	const int MY_TRESH = 1000;
	vector<double> extrema;

# if defined(USE_MINIMA)
	for (int row = 1; row < procImg.cols - 1; row++){
		int oldVal = procImg.at<int>(row-1);
		int val = procImg.at<int>(row);
		int nextVal = procImg.at<int>(row + 1);

		//Check if local minimum &&  minimum below treshold
		if (oldVal - val > 0 && nextVal - val > 0 && val < MY_TRESH){
			//extrema.push_back(row);
			cout << "Minimum" << row << endl;
		//	system("pause");
		}
	}
#endif

# if defined(USE_MAXIMA)
	for (int row = 1; row < procImg.cols - 1; row++){
		int oldVal = procImg.at<int>(row - 1);
		int val = procImg.at<int>(row);
		int nextVal = procImg.at<int>(row + 1);

		//Check if local maximum &&  maximum above treshold
		if (oldVal - val < 0 && nextVal - val < 0 && val > MY_TRESH){
			extrema.push_back((double)row);
# if defined(CMD_PRINT)
			cout << "Maximum" << row << endl;
		//	system("pause");
#endif
		}
	}
#endif

	// Distance in which extrema will be merged (2 passes for merging are applied
	const double mergeDist[] = { 2, 5 };
	vector<double> weight(extrema.size(), 1);

# if defined(CMD_PRINT)
	for (int temp = 0; temp < extrema.size(); temp++)
		cout << "Max " << temp << "Pos " << extrema.at(temp) << endl;
#endif

	for (int pass = 0; pass < 2; pass++){
		int removed = 0;
		for (int cnt = 0; (cnt) < (extrema.size() - 1); cnt++){
# if defined(CMD_PRINT)
			cout << " current difference ************** " << extrema.at(cnt + 1) - extrema.at(cnt) << endl;
			cout << " current object ************** " << extrema.at(cnt) << endl << endl;
		//	system("pause");
#endif
			if (extrema.at(cnt + 1) - extrema.at(cnt) <= mergeDist[pass]){
				extrema.at(cnt) = (extrema.at(cnt) * weight.at(cnt) + extrema.at(cnt + 1) * weight.at(cnt + 1)) / (weight.at(cnt) + weight.at(cnt + 1));
				weight.at(cnt) += weight.at(cnt + 1);
				extrema.erase(extrema.begin() + cnt + 1);
				weight.erase(weight.begin() + cnt + 1);
				removed++;
# if defined(CMD_PRINT)
				cout << " extrema pass" << pass << " el " << cnt << " val " << extrema.at(cnt) << " enchancement" << " weight " << weight.at(cnt) << endl;
#endif
			}
		}
# if defined(CMD_PRINT)
		for (int temp = 0; temp < extrema.size(); temp++)
			cout << "Max " << temp << "Pos " << extrema.at(temp) << endl;
#endif
	}

	vector<double> distances;
	for (int iter = 0; iter < extrema.size() - 1; iter++){
		distances.push_back(extrema.at(iter + 1) - extrema.at(iter));
# if defined(CMD_PRINT)
		cout << "Difference beetwen extremum" << iter << " and " << iter + 1 << " = " << distances.at(iter) << endl;
#endif
	}
	double average;
	return average = std::accumulate(distances.begin(), distances.end(), 0.0) / distances.size();
}