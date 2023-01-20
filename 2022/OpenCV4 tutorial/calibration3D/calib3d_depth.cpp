
#include <iostream>
#include <opencv2/opencv.hpp>
void disp2Depth(const cv::Mat& disp,cv::Mat &depth, double fb, int scale)
{
    depth.create(disp.rows,disp.cols,CV_8UC1);
    cv::Mat depth1 = cv::Mat(disp.rows,disp.cols,CV_16S);
    for (int i = 0;i < disp.rows;i++)
    {
        for (int j = 0;j < disp.cols;j++)
        {
            if (!disp.ptr<ushort>(i)[j])//防止除0中断
                continue;
            depth1.ptr<short>(i)[j] =scale * fb / disp.ptr<short>(i)[j];
        }
    }
//    double max1, min1;
//    cv::minMaxLoc(depth1, &min1, &max1);
//    std::cout<<min1 << "," <<max1 << std::endl;
//    depth = (depth1+min1)/

    cv::normalize(depth1, depth1, 0, 255, cv::NORM_MINMAX);
    depth1.convertTo(depth,CV_8U);//转8位
//    cv::Mat color;
    applyColorMap(depth,depth,cv::COLORMAP_JET);//转彩色图
//    cv::imshow("color", color);


//
//    double max1, min1;
//    cv::minMaxLoc(depth, &min1, &max1);
//    std::cout <<max1 << "  " << min1 << std::endl;
//
//    cv::imwrite("depth.jpg", depth);

}
void stereoSGBM(const cv::Mat& lpng,const cv::Mat& rpng,const std::string& filename,cv::Mat &disp)
{
    disp.create(lpng.rows,lpng.cols,CV_16S);
    cv::Mat disp1 = cv::Mat(lpng.rows,lpng.cols,CV_8UC1);
    cv::Size imgSize = lpng.size();
    cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create();

    int nmDisparities = ((imgSize.width / 8) + 15) & -16;//视差搜索范围
    int pngChannels = lpng.channels();//获取左视图通道数
    int winSize = 5;

    sgbm->setPreFilterCap(31);//预处理滤波器截断值
    sgbm->setBlockSize(winSize);//SAD窗口大小
    sgbm->setP1(8*pngChannels*winSize*winSize);//控制视差平滑度第一参数
    sgbm->setP2(32*pngChannels*winSize*winSize);//控制视差平滑度第二参数
    sgbm->setMinDisparity(0);//最小视差
    sgbm->setNumDisparities(nmDisparities);//视差搜索范围
    sgbm->setUniquenessRatio(5);//视差唯一性百分比
    sgbm->setSpeckleWindowSize(300);//检查视差连通区域变化度的窗口大小
    sgbm->setSpeckleRange(32);//视差变化阈值
    sgbm->setDisp12MaxDiff(1);//左右视差图最大容许差异
    sgbm->setMode(cv::StereoSGBM::MODE_SGBM);//采用全尺寸双通道动态编程算法
    sgbm->compute(lpng,rpng,disp);


    disp.convertTo(disp1,CV_8U,255 / (nmDisparities*16.));//转8位
    cv::imshow(filename, disp1);

}


int main(int argc, char **argv) {
    int width = 752;
    int height = 480;
    cv::Size image_size(width, height);

    // 左位姿矩阵
    cv::Mat T_bc1 = (cv::Mat_<double>(4, 4) << 0.0148655429818, -0.999880929698, 0.00414029679422, -0.0216401454975,
                                               0.999557249008, 0.0149672133247, 0.025715529948, -0.064676986768,
                                               -0.0257744366974, 0.00375618835797, 0.999660727178, 0.00981073058949,
                                               0.0, 0.0, 0.0, 1.0);
    // 右位姿矩阵
    cv::Mat T_bc2 = (cv::Mat_<double>(4, 4) << 0.0125552670891, -0.999755099723, 0.0182237714554, -0.0198435579556,
                                               0.999598781151, 0.0130119051815, 0.0251588363115, 0.0453689425024,
                                               -0.0253898008918, 0.0179005838253, 0.999517347078, 0.00786212447038,
                                               0.0, 0.0, 0.0, 1.0);
    cv::Mat T_c2c1 = T_bc2.inv() * T_bc1;
    cv::Mat R_c2c1 = T_c2c1.rowRange(0,3).colRange(0,3);
    cv::Mat t_c2c1 = T_c2c1.rowRange(0,3).col(3);
    std::cout << "t_c2c1:" << std::endl << t_c2c1.t() << std::endl; // 两个摄像头的相对位置(x, y, z) 单位是m


    // 左摄像头的内参矩阵
    cv::Mat left_k = (cv::Mat_<double>(3, 3) << 458.654, 0.000000, 367.215,
                                                0.000000, 457.296, 248.375,
                                                0.000000, 0.000000, 1.000000);
    // 左畸变矩阵
    cv::Mat left_d = (cv::Mat_<double>(5, 1) << -0.28340811, 0.07395907, 0.00019359, 1.76187114e-05, 0);

    // 右摄像头的内参矩阵
    cv::Mat right_k = (cv::Mat_<double>(3, 3) << 457.587, 0.000000, 379.999,
                                                 0.000000, 456.134, 255.238,
                                                 0.000000, 0.000000, 1.000000);
    // 右畸变矩阵
    cv::Mat right_d = (cv::Mat_<double>(5, 1) << -0.28368365,  0.07451284, -0.00010473, -3.55590700e-05, 0);

    cv::Mat canvas(image_size.height, image_size.width * 2, CV_8UC3);// 创建一个宽度为两倍图像大小的矩阵

    // 将左右两张图片分别放在canvas的左右两侧canvas_left, canvas_right
    // canvas 和 canvas_left、canvas_right关联
    cv::Mat canvas_left = canvas(cv::Rect(0, 0, image_size.width, image_size.height));
    cv::Mat canvas_right = canvas(cv::Rect(image_size.width, 0, image_size.width, image_size.height));
    // color_left拷贝到canvas左侧，color_right拷贝到canvas右侧，
    cv::Mat color_left = cv::imread("1403636579763555584cam0.png", cv::IMREAD_COLOR);
    cv::Mat color_right = cv::imread("1403636579763555584cam1.png", cv::IMREAD_COLOR);
    color_left.copyTo(canvas_left);
    color_right.copyTo(canvas_right);

    // 显示合并的图片
    cv::namedWindow("canvas", cv::WINDOW_AUTOSIZE);
    cv::imshow("canvas", canvas);
    cv::waitKey(0);


    std::cout << "stereo rectify..." << std::endl;
    cv::Mat R1, R2, P1, P2, Q;
    cv::Rect validROIL; // 图像校正之后，会对图像进行裁剪，这里的validROI就是指裁剪之后的区域, 其内部的所有像素都有效
    cv::Rect validROIR;
    /**
     * R,tvec: 是由相机1变换到相机2的变换矩阵，按照视觉这边的习惯，一般世界坐标系下的点变换到相机坐标系下的点
     * R1,R2:对两个相机进行旋转矫正的旋转变换矩阵，为世界系到两个相机的变换
     * P1,P2:两个矫正畸变后的相机投影矩阵，相对的坐标系还是原来的相机1所在坐标系
     * flags: 一般CALIB_ZERO_DISPARITY
     * alpha: -1或者不设置则使用自动剪切，0的时候没有黑边，1的时候保留所有原图像素，会有黑边
     * newImageSize: 默认与原图相同，所以会有剪切，该参数需要跟initUndistortRectifyMap相同,设置大一些会在大畸变的时候保留更多细节.
     * validROIL validROIR 可选的输出矩形，在矫正后的图像中，所有的像素都是有效的。如果alpha=0，ROI就会覆盖整个图像。否则，它们可能会更小
     */
    cv::stereoRectify(left_k, left_d, right_k, right_d, image_size, R_c2c1, t_c2c1, R1, R2, P1, P2, Q,
            cv::CALIB_ZERO_DISPARITY, 0, image_size, &validROIL, &validROIR);
    double fb = P2.at<double>(0,3);


    std::cout << "R1:" << std::endl << R1 << std::endl;
    std::cout << "P1:" << std::endl << P1 << std::endl;
    std::cout << "R2:" << std::endl << R2 << std::endl;
    std::cout << "P2:" << std::endl << P2 << std::endl;
    std::cout << "fb:" << std::endl << fb << std::endl;
    std::cout << "Q:" << std::endl << Q << std::endl;

    cv::Mat mapLx, mapLy, mapRx, mapRy;

    // 计算失真和矫正变换矩阵。
    cv::initUndistortRectifyMap(left_k, left_d, R1, P1.rowRange(0,3).colRange(0,3), image_size, CV_32F, mapLx, mapLy); // CV_16SC2
    cv::initUndistortRectifyMap(right_k, right_d, R2, P2.rowRange(0,3).colRange(0,3), image_size, CV_32F, mapRx, mapRy);


    //rectifyImageL 和 rectifyImageR是三维标定后的矫正的图像
    cv::Mat rectifyImageL, rectifyImageR;
    cv::remap(color_left, rectifyImageL, mapLx, mapLy, cv::INTER_LINEAR);
    cv::remap(color_right, rectifyImageR, mapRx, mapRy, cv::INTER_LINEAR);

    rectifyImageL.copyTo(canvas_left);
    rectifyImageR.copyTo(canvas_right);

//    cv::rectangle(canvas_left, validROIL, cv::Scalar(255, 0, 0), 3, 8);
//    cv::rectangle(canvas_right, validROIR, cv::Scalar(255, 0, 0), 3, 8);

//    for (int i = 0; i <= canvas.rows; i += 10) {
//        float b = 255 * float(rand()) / RAND_MAX;
//        float g = 255 * float(rand()) / RAND_MAX;
//        float r = 255 * float(rand()) / RAND_MAX;
//        cv::line(canvas, cv::Point(0, i), cv::Point(canvas.cols, i), cv::Scalar(b, g, r), 1, 8);
//    }
    std::cout << "stereo rectify done" << std::endl;
    cv::imshow("canvas", canvas);
    cv::waitKey(0);
    cv::Mat disp;
    cv::cvtColor(canvas_left, canvas_left, cv::COLOR_BGR2GRAY);
    cv::cvtColor(canvas_right, canvas_right, cv::COLOR_BGR2GRAY);
    stereoSGBM(canvas_left, canvas_right, "disp.jpg", disp);

    struct Depth_info{
        cv::Mat disp;
        double fb;
        cv::Mat depth;
    } userdata{.disp=disp, .fb=fb};
    cv::createTrackbar("scale", "canvas", NULL, 500,[](int scale, void* userdata)->void {
        Depth_info* data = (Depth_info*) userdata;
        disp2Depth(data->disp, data->depth, -data->fb, scale);
        cv::imshow("color", data->depth);
    }, (void*) &userdata);
    //disp2Depth(disp, depth, -fb, 480);
    cv::setTrackbarPos("scale", "canvas", 480);

    cv::waitKey();
    cv::imwrite("depth.jpg", userdata.depth);
    return 0;
}