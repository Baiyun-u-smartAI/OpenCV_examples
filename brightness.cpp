#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;

double alpha; /**< Simple contrast control */
int beta; /**< Simple brightness control */
int run913()
{
	// 分别生成两个矩阵，存放原图片和亮度变换后图片new_image
	Mat image = imread("1.jpg");

	Mat new_image = Mat::zeros(image.size(), image.type());
	imshow("zero", new_image);

	/// Initialize values (Basic Linear Transform)
	std::cout << " 基本线性转换" << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "* 输入 alpha 值 [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "* 输入 beta 值 [0-100]: "; std::cin >> beta;

	/// 转换公式 new_image(i,j) = alpha*image(i,j) + beta
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				// 针对像素的每个色屏做转换
				//saturate_cast函数防止溢出（运算后值<0或>255）
				// 低于0 输出0，高于255 输出255，其余值不变
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	imshow("Original Image", image);
	imshow("New Image", new_image);

	waitKey();

	return 0;
}

int(*run_brightness)()=run913;
