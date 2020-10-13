#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;

static Mat image,new_image;
static double alpha_; /**< Simple contrast control */
static int alpha=0;
static const int alpha_max=30;
static const int beta_max=15;
static int beta; /**< Simple brightness control */

void Brightness_Operation(int,void*);

int run913()
{
	// 分别生成两个矩阵，存放原图片和亮度变换后图片new_image
	image = imread("1.jpg");

	new_image = Mat::zeros(image.size(), image.type());
	//imshow("zero", new_image);
	// α控制对比度，β控制亮度
	/// Initialize values (Basic Linear Transform)
	std::cout << " 基本线性转换" << std::endl;
	std::cout << "-------------------------" << std::endl;
//	std::cout << "* 输入 alpha 值 [1.0-3.0]: "; std::cin >> alpha;
//	std::cout << "* 输入 beta 值 [0-100]: "; std::cin >> beta;

	/// 转换公式 new_image(i,j) = alpha*image(i,j) + beta
//	for (int y = 0; y < image.rows; y++)
//	{
//		for (int x = 0; x < image.cols; x++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				// 针对像素的每个色屏做转换
//				//saturate_cast函数防止溢出（运算后值<0或>255）
//				// 低于0 输出0，高于255 输出255，其余值不变
//				new_image.at<Vec3b>(y, x)[c] =
//					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
//			}
//		}
//	}
//    new_image= image*alpha+Scalar(beta,beta,beta);
    namedWindow("Original Image", 1);
	namedWindow("New Image", 1);
    namedWindow("operator", WINDOW_AUTOSIZE);
    createTrackbar("对比度0~30","operator",&alpha,alpha_max,Brightness_Operation,NULL);
    createTrackbar("亮度0~15","operator",&beta,beta_max,Brightness_Operation,NULL);
    Brightness_Operation(0,0);
    imshow("Original Image", image);


	waitKey();

	return 0;
}

void Brightness_Operation(int,void*){
    alpha_= static_cast<double>(alpha)/10;
    new_image= image*alpha_+Scalar(10*beta,10*beta,10*beta);
    imshow("New Image", new_image);
}

int(*run_brightness)()=run913;
