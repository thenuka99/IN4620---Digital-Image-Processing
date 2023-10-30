#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "Usage: exeFileName ImageToLoadAndDisplay Threshold" <<endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], IMREAD_COLOR);
	int T = atoi(argv[2]);
	if (!image.data)
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat gr;
	cvtColor(image, gr, COLOR_BGR2GRAY);
	int h = gr.rows;
	int w = gr.cols;
	cout << "Width: " << w << endl;
	cout << "Height: " << h << endl;
	Mat med = gr.clone();
	int Gx = 0;
	int Gy = 0;
	int G = 0;

	for (int i = 0; i < h - 1; i++)
	{
		for (int j = 0; j < w - 1; j++)
		{
			Gx = gr.at<uchar>(i, j) - gr.at<uchar>(i, j + 1);
			Gy = gr.at<uchar>(i, j) - gr.at<uchar>(i + 1, j);
			G = abs(Gx) + abs(Gy);
			if (G >= T)
				med.at<uchar>(i, j) = 0;
			else
				med.at<uchar>(i, j) = 255;
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