// 从图像坐标系转换到世界坐标系

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// void draw(Mat& img, Mat corners, Mat imgpts) {
//     auto BasePoint = Point2i(corners.at<Vec2f>(0)[0], corners.at<Vec2f>(0)[1]);
//     // 蓝色线 - x轴
//     line(img, BasePoint, Point2i(imgpts.at<Vec2f>(0)[0], imgpts.at<Vec2f>(0)[1]), Scalar(255,0,0), 5, LINE_AA);
//     // 绿色线 - y轴
//     line(img, BasePoint, Point2i(imgpts.at<Vec2f>(1)[0], imgpts.at<Vec2f>(1)[1]), Scalar(0,255,0), 5, LINE_AA);
//     // 红色线 - z轴
//     line(img, BasePoint, Point2i(imgpts.at<Vec2f>(2)[0], imgpts.at<Vec2f>(2)[1]), Scalar(0,0,255), 5, LINE_AA);
// }

/*
 * 
 * @rvec 坐标点从世界坐标系旋转到相机坐标系的旋转向量
 * @zConst 坐标点离世界坐标系xOy平面的距离
 * @cameraMatrix: 摄像头内参矩阵
 * @tvec 坐标点从世界坐标系平移到相机坐标系的平移向量
 * @rotationMatrix(out): 坐标点从世界坐标系旋转到相机坐标系的旋转矩阵
 * @ret 目标点在相机坐标系Z方向的值s(深度)
 *  
 */
double calcParameters(const Mat& rvec, const Mat& tvec, double zConst, const Mat& cameraMatrix, Mat& rotationMatrix)
{
//计算旋转和平移矩阵

    cv::Rodrigues(rvec, rotationMatrix);
    cv::Mat imagePoint = cv::Mat::ones(3, 1, cv::DataType<double>::type); //u,v,1=1,1,1

//计算参数s
    cv::Mat tempMat, tempMat2;
    tempMat = rotationMatrix.inv() * cameraMatrix.inv() * imagePoint;
    tempMat2 = rotationMatrix.inv() * tvec;
    double s = zConst + tempMat2.at<double>(2, 0);
    s /= tempMat.at<double>(2, 0);
    return s;
}
/**
 * 
 * @inPoints
 * @s 目标点在相机坐标系Z方向的值(深度)
 * @tvec 坐标点从世界坐标系平移到相机坐标系的平移向量
 * @rotationMatrix 坐标点从世界坐标系旋转到相机坐标系的旋转矩阵
 * @cameraMatrix: 摄像头内参矩阵
 * @ret 世界坐标系三维点
 */
Point3d getWorldPoints(const Point2d& inPoints, double s, const Mat& tvec, const Mat& rotationMatrix, const Mat& cameraMatrix)
{
    cv::Mat imagePoint = cv::Mat::ones(3, 1, cv::DataType<double>::type); //u,v,1
    imagePoint.at<double>(0, 0) = inPoints.x;
    imagePoint.at<double>(1, 0) = inPoints.y;
    Mat wcPoint = rotationMatrix.inv() * (s * cameraMatrix.inv() * imagePoint - tvec);
    Point3d worldPoint(wcPoint.at<double>(0, 0), wcPoint.at<double>(1, 0), wcPoint.at<double>(2, 0));
    return worldPoint;
}


int main() {
    vector<uchar> ptXYZ(54 * 3);
    std::for_each(ptXYZ.begin(), ptXYZ.end(), [](uchar &each) {
        static int i = 0;
        if (i % 3 == 0) each = (i / 3) % 9;
        else if ((i - 1) % 3 == 0) each = (i - 1) / 27;
        i++;
    });

    // 需要绘制的标准点
    Mat objectPoints(ptXYZ);
    ptXYZ.clear();
    objectPoints = objectPoints.reshape(1, 54);

    objectPoints.convertTo(objectPoints, CV_32F);
    //cout << objectPoints << endl;

    // 摄像头外参
    Mat cameraMatrix = (Mat_<double>(3, 3)<< 2.8125299882607928e+03, 0., 1.8235e+03,
                                            0., 2.8125299882607928e+03, 1.3675e+03,
                                            0., 0., 1. );
    // 摄像头畸变参数
    Mat distCoeffs = (Mat_<double>(5, 1)<< 4.5645665323650574e-02, -9.4368813116504080e-02, 0., 0., 8.7550271042410616e-02);

    // 轴
    Mat axis = (Mat_<float>(3, 3)<< 3.,  0.,  0.,
                                            0.,  3.,  0.,
                                            0.,  0., -3.);

    // cornerSubPix算法的迭代参数
    TermCriteria criteria = TermCriteria(
            TermCriteria::Type::EPS + TermCriteria::Type::MAX_ITER,
            60, //maxCount=60
            0.001);    //epsilon=0.001

    // 取xml文件里面的images标签存进img_list
    FileStorage fs("./VID5.xml", FileStorage::READ);
    vector<string> img_list;
    fs["images"] >> img_list;
    for_each(img_list.begin(), img_list.end(), [](const string& path) {
        cout << path << endl;
    });


    for (const auto& imgName: img_list) {
        Mat img = imread(imgName);
        Mat gray, corners, rvec, tvec, imagePoints, rotationMatrix;

        cvtColor(img, gray, COLOR_BGR2GRAY);
        bool ret = findChessboardCorners(img, Size(9, 6), corners);// 获取角点corners
        if (ret) {// 找到棋盘点
            // 角点检测中精确化角点位置
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), criteria);//
            solvePnP(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

            double s = calcParameters(rvec, tvec, 0., cameraMatrix,  rotationMatrix);
            // 913.9270593253681, 626.3247501680071
            cout << getWorldPoints(Point2d(913.92706, 626.32477), s, tvec, rotationMatrix, cameraMatrix) << endl;

            // 找到axis找到图中的投影坐标imagePoints
            // projectPoints(axis, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);

            // cout << imagePoints << endl;
            // draw(img, corners, imagePoints);

            undistort(img, img, cameraMatrix, distCoeffs); // 矫正图像
            resize(img, img, Size(), .3, .3);
            imshow("", img); // 显示矫正图像
            waitKey();
        }
    }
//    vector<String> jpgPath;
//    glob("*.jpg", jpgPath);
//    for (const auto& i:jpgPath) {
//        cout<< i <<endl;
//    }
//
//    FileStorage fs("data.xml", FileStorage::WRITE);
//    fs << "images" << jpgPath;
//    fs.release();



    return 0;
}