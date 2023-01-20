#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{



    Mat input = imread("Contour.png", IMREAD_GRAYSCALE);
    
    Mat input_c = 255 - input*255; // 求轮廓的补集
    

    imshow("input_c", input_c);

    // 为了后面给图案上色
    cvtColor(input, input, COLOR_GRAY2BGR);
    cvtColor(input_c, input_c, COLOR_GRAY2BGR);


    // 涂色底稿，全黑的图片X
    Mat X = Mat::zeros(input.size(), CV_8UC3);

    // 开始填充颜色的点，（推荐随机取）
    X.at<Vec3b>(0, 250) = Vec3b(255, 100, 100);
    
    X.at<Vec3b>(250, 250) = Vec3b(100, 100, 255);

    // std::cout << input << std::endl;

    // todo 定义形态学算子
    Mat kernel = getStructuringElement(MORPH_CROSS, Size(3,3));

    bool eq = true;
    while(eq) {
        static Mat X_pre = Mat::zeros(X.size(), CV_8UC3);
        dilate(X, X, kernel);
        bitwise_and(X, input_c, X);
        imshow("X", X);
        cv::Mat diff = X_pre != X;
        X.copyTo(X_pre);
        // Equal if no elements disagree
        eq = cv::countNonZero(diff.reshape(1, diff.rows)) != 0;
        if (waitKey(1)=='q') break;
    }
    waitKey();
    
    return 0;

}
