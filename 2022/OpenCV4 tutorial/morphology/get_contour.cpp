#include <opencv2/opencv.hpp>
using namespace cv;

int main(void)
{

    // boxFilter 均值滤波、方框滤波 (模糊、降噪)
    // GaussianBlur 滤波核中间值大，越远离中心位置，权重越小。更好地模糊
    // Sobel 导向滤波器，发现某一个方向的轮廓。
    // 找出轮廓：梯度: sqrt(dx*dx+dy*dy) ，或者Laplacian滤波
    // medianBlur 中值滤波：框选某一个区域，区域内的元素从小到大排序，留下中位数作为区域中心的值
    // bilateralFilter 双边滤波：双边=定义域滤波(线性滤波)+值域滤波(离中心的值越接近、权重越大)，去除噪点、保留轮廓

    // Mat input = imread("merge_split.jpg");
    VideoCapture web_jpg("https://photo.tuchong.com/19902122/f/669124206.jpg");
    Mat input;
    web_jpg >> input;

    // std::cout << input << std::endl;

    // todo 定义形态学算子

    // 1. 手动定义结构单元形状，注意：0是背景，非0代表是图案(一般为1或者255)
    // Mat kernel = (Mat_<uchar>(3, 3, CV_8UC1)<< 0  , 1 ,  0 ,
    //                                            1  , 1 ,  1,
    //                                            0  , 1 ,  0  ) ;

    // 2. 用getStructuringElement生成形态学结构算子(MORPH_RECT矩形 MORPH_CROSS十字形 MORPH_ELLIPSE椭圆)
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    
    // 3. 先绘制形态学结构，再导入到kernel
    // Mat kernel = imread("9.png", IMREAD_GRAYSCALE);
    // resize(kernel, kernel, Size(), 3, 3);
    // std::cout << kernel*5 << std::endl;


    Mat out;
    erode(input, out, kernel);
    // dilate(input, out, kernel);


    // std::cout << out << std::endl;
    imshow("Contour", input - out);
    waitKey();
    return 0;

}
