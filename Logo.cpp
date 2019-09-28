#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>

using namespace cv;

int main()
{
	// 载入图档
	Mat image1 = imread("C:\\images\\lena.jpg");
	Mat logo = imread("C:\\opencv\\build\\doc\\opencv-logo-white.png");

	Mat image = image1, opencvlogo;

	// 缩小圆图成Size(80, 64)
	resize(logo, opencvlogo, Size(80, 64));

	namedWindow("Image 1", CV_WINDOW_AUTOSIZE);

	// 定义图有兴趣的区域(Region Of Interest, ROI)
	Mat imageROI;

	// Rect(x, y, col, row)
	imageROI = image(Rect(420, 420, 80, 64));

	imshow("Image 1", opencvlogo);

	// 加入商标
	addWeighted(imageROI, 1.0, opencvlogo, 0.3, 0., imageROI);

	// 显示结果
	namedWindow("with logo");
	imshow("with logo", image);

	/*
	//Mat mask = imread("C:\\images\\OpenCV 2 Computer Vision\\logo.bmp", 0);
	Mat mask = opencvlogo;

	// logo用遮蔽方式复制给imageROI
	logo.copyTo(imageROI, mask);

	namedWindow("with logo 2");
	imshow("with logo 2", image);

	// 必须再次载入
	logo = imread("C:\\images\\OpenCV 2 Computer Vision\\logo.bmp", 0);
	image1 = imread("C:\\images\\OpenCV 2 Computer Vision\\boldt.jpg");

	// 将图的三屏改成ㄧ屏
	std::vector<Mat> channels;
	split(image1, channels);

	imageROI = channels.at(1);

	addWeighted(imageROI(Rect(385, 270, logo.cols, logo.rows)), 1.0,
		logo, 0.5, 0., imageROI(Rect(385, 270, logo.cols, logo.rows)));

	merge(channels, image1);

	namedWindow("with logo 3");
	imshow("with logo 3", image1);
	*/
	waitKey();

	return 0;
}
