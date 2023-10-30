#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int findMode(int arr[], int n) {

	int maxCount = 0;
	int mode = 0;

	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (arr[j] == arr[i])
				count++;
		}
		if (count > maxCount) {
			maxCount = count;
			mode = arr[i];
		}
	}
	return mode;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Usage: exeFileName ImageToLoadAndDisplay Threshold" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], 1);
	if (!image.data) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat gr;
	cvtColor(image, gr, COLOR_BGR2GRAY);
	int h = gr.rows;
	int w = gr.cols;
	Mat mode = gr.clone();
	int ksize = atoi(argv[2]);
	int adj = ksize / 2;
	int size = ksize * ksize;
	int val = 0;
	vector<int> values(size);

	for (int i = adj; i < h - adj; i++) {
		for (int j = adj; j < w - adj; j++) {
			int r = 0;
			for (int t1 = -adj; t1 <= adj; t1++) {
				for (int t2 = -adj; t2 <= adj; t2++) {
					val = gr.at<uchar>(i + t1, j + t2);
					values[r] = val;
					r++;
				}
			}
			int mode_value = findMode(&values[0], size);
			mode.at<uchar>(i, j) = static_cast<uchar>(mode_value);
		}
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", mode);
	imwrite("output.jpg", mode);
	namedWindow("Display Gray", WINDOW_AUTOSIZE);
	imshow("Display Gray", gr);
	waitKey(0);
	image.release();
	gr.release();
	mode.release();
	return 0;
}
