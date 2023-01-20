#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	imshow("the title", Mat::zeros(100, 100, CV_8UC3));
           
	waitKey(); // 按任意键结束显示
	
	return 0;
}