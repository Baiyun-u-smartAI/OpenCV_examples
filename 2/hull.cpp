#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <fstream>
#include <iostream>
#include "OpenCV_example.hpp"
using namespace cv;
using namespace std;
int run007()
{
	Mat img(500, 500, CV_8UC3);
	RNG& rng = theRNG();
	for (;;)
	{
		char key;
		int i, count = (unsigned)rng % 100 + 1;
		vector<Point> points;
		for (i = 0; i < count; i++)
		{
			Point pt;
			pt.x = rng.uniform(img.cols / 4, img.cols * 3 / 4);
			pt.y = rng.uniform(img.rows / 4, img.rows * 3 / 4);
			points.push_back(pt);
		}
		vector<int> hull;
		convexHull(Mat(points), hull, true);
		img = Scalar::all(0);
		for (i = 0; i < count; i++)
			circle(img, points[i], 3,
			Scalar(0, 0, 255), FILLED, LINE_AA);
		int hullcount = (int)hull.size();
		Point pt0 = points[hull[hullcount - 1]];
		for (i = 0; i < hullcount; i++)
		{
			Point pt = points[hull[i]];
			line(img, pt0, pt,
				Scalar(0, 255, 0), 1, LINE_AA);
			pt0 = pt;
		}
		imshow("hull", img);
		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q') // 'ESC'
			break;
	}
	return 0;
}
int(*run_hull)()=run007;