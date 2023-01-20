#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void draw(Mat& img, Mat corners, Mat imgpts) {
    auto BasePoint = Point2i(corners.at<Vec2f>(0)[0], corners.at<Vec2f>(0)[1]);
    // 蓝色线 - x轴
    line(img, BasePoint, Point2i(imgpts.at<Vec2f>(0)[0], imgpts.at<Vec2f>(0)[1]), Scalar(255,0,0), 5, LINE_AA);
    // 绿色线 - y轴
    line(img, BasePoint, Point2i(imgpts.at<Vec2f>(1)[0], imgpts.at<Vec2f>(1)[1]), Scalar(0,255,0), 5, LINE_AA);
    // 红色线 - z轴
    line(img, BasePoint, Point2i(imgpts.at<Vec2f>(2)[0], imgpts.at<Vec2f>(2)[1]), Scalar(0,0,255), 5, LINE_AA);
}

void drawBox(Mat& img, Mat corners, Mat imgpts) {
    auto BasePoint = Point2i(corners.at<Vec2f>(0)[0], corners.at<Vec2f>(0)[1]);

    // 前四个点组成了底面
    vector< vector<Point2i> > groundEdges;
    vector<Point2i> one_edge;
    for (int i = 0; i < 4; ++i) {
        one_edge.emplace_back(Point2i(imgpts.at<float>(i, 0), imgpts.at<float>(i, 1)));
    }
    groundEdges.push_back(std::move(one_edge));
    // drawContours是绘制多条轮廓，groundEdges是存放多条轮廓的集合，每条轮廓又是点的集合，所以类型为vector< vector<Point2i> >，每条轮廓类型vector<Point2i>


    // 正方体的蓝色的四条楞显示
    drawContours(img, groundEdges, -1,Scalar(0, 255, 0), -3);

    for (int i = 0; i < 4; ++i) {
        line(img, Point2i(imgpts.at<Vec2f>(i)[0], imgpts.at<Vec2f>(i)[1]), Point2i(imgpts.at<Vec2f>(i+4)[0], imgpts.at<Vec2f>(i+4)[1]), Scalar(255,0,0), 5, LINE_AA);
    }

    // 绘制顶层轮廓
    vector< vector<Point2i> > topEdges;
    for (int i = 0; i < 4; ++i) {
        one_edge.emplace_back(Point2i(imgpts.at<float>(i+4, 0), imgpts.at<float>(i+4, 1)));
    }
    topEdges.push_back(one_edge);

    drawContours(img, topEdges, -1,Scalar(0, 0, 255), 3);
}


int main() {
    // 标准化棋盘的世界坐标
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
    Mat cameraMatrix = (Mat_<float>(3, 3)<< 2.8125299882607928e+03, 0., 1.8235e+03,
                                            0., 2.8125299882607928e+03, 1.3675e+03,
                                            0., 0., 1. );
    // 摄像头畸变参数
    Mat distCoeffs = (Mat_<float>(5, 1)<< 4.5645665323650574e-02, -9.4368813116504080e-02, 0., 0., 8.7550271042410616e-02);

    // 轴
    Mat axis = (Mat_<float>(3, 3)<< 3., 0.,  0.,
                                    0., 3.,  0.,
                                    0., 0., -3.);

    Mat edges = (Mat_<float>(8, 3)<< 0, 0, 0,
                                     0, 3, 0,
                                     3, 3, 0,
                                     3, 0, 0,
                                     0, 0, -3,
                                     0, 3, -3,
                                     3, 3, -3,
                                     3, 0, -3);

    // cornerSubPix算法的迭代参数
    TermCriteria criteria = TermCriteria(
            TermCriteria::Type::EPS + TermCriteria::Type::MAX_ITER,
            60, //maxCount=60
            0.001);    //epsilon=0.001

    // 取xml文件里面的images标签存进img_list
    FileStorage fs("./VID5.xml", FileStorage::READ);
    vector<string> img_list;
    fs["images"] >> img_list;



    for (const auto& imgName: img_list) {
        Mat img = imread(imgName);
        Mat gray, corners, rvec, tvec, imagePoints;

        cvtColor(img, gray, COLOR_BGR2GRAY);
        bool ret = findChessboardCorners(img, Size(9, 6), corners);// 获取角点corners
        if (ret) {// 找到棋盘点
            // 角点检测中精确化角点位置
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), criteria);//
            solvePnP(objectPoints, corners, cameraMatrix, distCoeffs, rvec, tvec);

            // 找到axis找到图中的投影坐标imagePoints
//            projectPoints(axis, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);
            projectPoints(edges, rvec, tvec, cameraMatrix, distCoeffs, imagePoints);


            //cout << imagePoints << endl;
            // draw(img, corners, imagePoints);
            drawBox(img, corners, imagePoints);
            resize(img, img, Size(), .3, .3);
            imshow("", img);
            waitKey();
        }
    }

    return 0;
}