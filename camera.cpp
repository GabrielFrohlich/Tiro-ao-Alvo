#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	namedWindow("Círculos", WINDOW_AUTOSIZE);
	namedWindow("gray", WINDOW_AUTOSIZE);
	namedWindow("canny", WINDOW_AUTOSIZE);

	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		cerr << "Couldn't open capture." << endl;
		system("pause");
		return -1;
	}

	Mat bgr_frame, gray, canny, circu;
	for (;;)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty()) break;

		//imshow("raw", bgr_frame);

		cvtColor(bgr_frame, gray, COLOR_BGR2GRAY);
		GaussianBlur(gray, gray, Size(9, 9), 2, 2);
		imshow("gray", gray);


		Canny(gray, canny, 10, 100, 3, true);
		imshow("canny", canny);

		circu = bgr_frame;

		//Cria Vetor
		vector<Vec3f> circles;

		//Reconhece circulos
		HoughCircles(canny, circles, CV_HOUGH_GRADIENT, 1, gray.rows / 128, 200, 100, 0, 0);
		//Desenha os circulos

		for (size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// circle center
			circle(circu, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			// circle outline
			circle(circu, center, radius, Scalar(0, 0, 255), 3, 8, 0);
		}

		//mostra círculo
		imshow("Círculos", circu);
		char c = waitKey(10);
		if (c == 27) break;
	}
	cap.release();
	return 0;
}
