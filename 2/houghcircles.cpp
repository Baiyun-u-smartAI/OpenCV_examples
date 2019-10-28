#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "OpenCV_example.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int run783()
{
    Mat img = imread("board.jpg", 0);
    if(img.empty())
    {
        cout << "can not open " << "board.jpg" << endl;
        return -1;
    }

    Mat cimg;
    medianBlur(img, img, 5);
    cvtColor(img, cimg, COLOR_GRAY2BGR);

    vector<Vec3f> circles;
    HoughCircles(img, circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 30);
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( cimg, Point(c[0], c[1]),
			c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( cimg, Point(c[0], c[1]),
			2, Scalar(0,255,0), 3, LINE_AA);
    }

    imshow("detected circles", cimg);
    waitKey();

    return 0;
}
int(*run_houghcircles)()=run783;