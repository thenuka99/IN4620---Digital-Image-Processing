#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int findMedian(int arr[], int n) {
	sort(arr, arr + n);
	if (n % 2 == 0) {
		return (arr[n / 2 - 1] + arr[n / 2]) / 2;
	}
	else {
		return arr[n / 2];
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Usage: exeFileName ImageToLoadAndDisplay kernelSize" << endl;
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
	Mat med = gr.clone();
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
			int median = findMedian(&values[0], size);
			med.at<uchar>(i, j) = static_cast<uchar>(median);
		}
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", med);
	imwrite("output.jpg", med);
	namedWindow("Display Gray", WINDOW_AUTOSIZE);
	imshow("Display Gray", gr);
	waitKey(0);
	image.release();
	gr.release();
	med.release();
	return 0;
}
