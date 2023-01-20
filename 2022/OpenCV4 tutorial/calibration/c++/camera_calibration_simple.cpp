//
// Created by pc004 on 2022/11/13.
//
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
using namespace cv;
using namespace std;
int main() {
    // calib参数flag
    int flag = 0;
    bool ret;
    flag |= CALIB_FIX_PRINCIPAL_POINT;// 固定光轴中心，一般不变焦就是固定
    flag |= CALIB_ZERO_TANGENT_DIST; // 有切向畸变
    flag |= CALIB_FIX_ASPECT_RATIO; // 焦距fx/fy比例固定

    vector<vector<Point2f>> imagePoints;

    vector<Point2f> CornerPoints;

    Size imageSize;
    //const Scalar RED(0, 0, 255), GREEN(0, 255, 0);

    Mat view = imread("IMG_20221028_210438_BURST011.jpg"), viewGray;
    imageSize = view.size();  // 输入图片的大小

    // 是否需要水平翻转图片
    if (false) flip(view, view, 0);
    /**
     * @patternSize 是要获取的棋盘点的多少，这里是9x6个棋盘点
     * @CornerPoints 找到9x6角点在图像中的坐标
     */
    ret = findChessboardCorners(view, Size(9, 6), CornerPoints);
    if (!ret) {
        cerr << "find ChessBoard Pattern failed" << endl;
        return EXIT_FAILURE;
    }
    cvtColor(view, viewGray, COLOR_BGR2GRAY); // 转变成灰度图

    cornerSubPix(viewGray, CornerPoints, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.0001));// 在角点检测中精确化角点位置，CornerPoints是输入角点的初始坐标以及精准化后的坐标用于输出。

    Mat org = view.clone(); // 因为下面的函数会丢失原始图像数据，所以要备份
    drawChessboardCorners(view, Size(9, 6), CornerPoints, ret);// 在view上绘制棋盘角点


    // 显示角点
    Mat showView;
    resize(view, showView, Size(), .6, .6);
    imshow("Chessboard view", showView);




    float squareSize = 5; // 每个棋盘各自边长squareSize
    vector<vector<Point3f> > objectPoints(1);

    // objectPoints[0]制作对应的9*6的三维角点坐标集合，{[1 i 0]~[8 i 0]  i: 0~5} * squareSize
    objectPoints[0].resize(54);

    std::for_each(objectPoints[0].begin(), objectPoints[0].end(), [=](Point3f &each) {
        static int i = 0;
        each.x = i%9 * squareSize;
        each.y = i/9 * squareSize;
        i++;
    });
    imagePoints.emplace_back(CornerPoints);
    auto newObjPoints = objectPoints[0]; // newObjPoints是objectPoints的副本


    int iFixedPoint = -1;
    double rms;
    Mat cameraMatrix, distCoeffs, rotationMatrix;
    Mat rvecs, tvecs;
    // objectPoints和imagePoints里的数据结构是 [图1的世界坐标点集合, 图2的世界坐标点集合,...] [图1的对应图像坐标点集合, 图2的对应图像坐标点集合,...]
    rms = calibrateCameraRO(objectPoints, imagePoints, imageSize, iFixedPoint, cameraMatrix, distCoeffs, rvecs, tvecs, newObjPoints, flag | CALIB_USE_LU);
    cout << "Re-projection error reported by calibrateCamera: " << rms << endl;
    cout << "cameraMatrix: " << cameraMatrix << endl; // 摄像头内参
    cout << "distCoeffs: " << distCoeffs << endl; // 摄像头畸变矩阵
    cout << "rvecs: " << rvecs << endl; // 外参旋转向量
    cv::Rodrigues(rvecs, rotationMatrix); // 求解外参旋转矩阵
    cout << "rotationMatrix: " << rotationMatrix << endl;
    cout << "tvecs: " << tvecs << endl; // 外参平移向量

//    view.release();
//    viewGray.release();

//    for_each(objectPoints[0].begin(), objectPoints[0].end(), [](Point3f& p){
//       cout<< p <<endl;
//
//    });
    Mat undistortView;
    undistort(org, undistortView, cameraMatrix, distCoeffs); // 矫正图像
    resize(undistortView, showView, Size(), .6, .6);
    imshow("undistort View", showView); // 显示矫正后图像
    waitKey();
}

