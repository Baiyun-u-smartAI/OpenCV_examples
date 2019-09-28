#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define w 400

using namespace cv;

/// 函数声明
void MyEllipse(Mat img, double angle);
void MyFilledCircle(Mat img, Point center);
void MyPolygon(Mat img);
void MyLine(Mat img, Point start, Point end);

int main(void){

  /// 窗口名称
  char atom_window[] = "Drawing 1: Atom";
  char rook_window[] = "Drawing 2: Rook";

  /// 建立空的黑图
  Mat atom_image = Mat::zeros(w, w, CV_8UC3);
  Mat rook_image = Mat::zeros(w, w, CV_8UC3);

  /// 1. 简单绘图
  /// ----------------------- 

  /// 1.a. 绘椭圆
  MyEllipse(atom_image, 90);
  MyEllipse(atom_image, 0);
  MyEllipse(atom_image, 45);
  MyEllipse(atom_image, -45);

  /// 1.b. 绘圆
  MyFilledCircle(atom_image, Point(w / 2, w / 2));

  /// 2. 绘 rook 
  /// ------------------ 

  /// 2.a. 绘凸面多边型
  MyPolygon(rook_image);

  /// 2.b. 绘长方形 
  rectangle(rook_image,
         Point(0, 7 * w / 8),
         Point(w, w),
         Scalar(0, 255, 255),
         - 1,
         8);

  /// 2.c. 绘直线 
  MyLine(rook_image, Point(0, 15 * w / 16), Point(w, 15 * w / 16));
  MyLine(rook_image, Point(w / 4, 7 * w / 8), Point(w / 4, w));
  MyLine(rook_image, Point(w / 2, 7 * w / 8), Point(w / 2, w));
  MyLine(rook_image, Point(3 * w / 4, 7 * w / 8), Point(3 * w / 4, w));

  // 显示窗口
  imshow(atom_window, atom_image);
  // 移动窗口到指定位置
  moveWindow(atom_window, 0, 200);

  imshow(rook_window, rook_image);
  moveWindow(rook_window, w, 200);

  waitKey(0);

  return(0);
}

// 绘椭圆
void MyEllipse(Mat img, double angle)
{
  int thickness = 2;
  int lineType = 8;

  ellipse(img,
       Point(w / 2, w / 2),
       Size(w / 4, w / 16),
       angle,
       0,
       360,
       Scalar(255, 0, 0),
       thickness,
       lineType);
}

// 绘圆
void MyFilledCircle(Mat img, Point center)
{
  int thickness = -1;
  int lineType = 8;

  circle(img,
      center,
      w / 32,
      Scalar(0, 0, 255),
      thickness,
      lineType);
}

// 绘凸面多边型
void MyPolygon(Mat img)
{
  int lineType = 8;

  /** 先建立点 */
  Point rook_points[1][20];
  rook_points[0][0] = Point(w / 4, 7 * w / 8);
  rook_points[0][1] = Point(3 * w / 4, 7 * w / 8);
  rook_points[0][2] = Point(3 * w / 4, 13 * w / 16);
  rook_points[0][3] = Point(11 * w / 16, 13 * w / 16);
  rook_points[0][4] = Point(19 * w / 32, 3 * w / 8);
  rook_points[0][5] = Point(3 * w / 4, 3 * w / 8);
  rook_points[0][6] = Point(3 * w / 4, w / 8);
  rook_points[0][7] = Point(26 * w / 40, w / 8);
  rook_points[0][8] = Point(26 * w / 40, w / 4);
  rook_points[0][9] = Point(22 * w / 40, w / 4);
  rook_points[0][10] = Point(22 * w / 40, w / 8);
  rook_points[0][11] = Point(18 * w / 40, w / 8);
  rook_points[0][12] = Point(18 * w / 40, w / 4);
  rook_points[0][13] = Point(14 * w / 40, w / 4);
  rook_points[0][14] = Point(14 * w / 40, w / 8);
  rook_points[0][15] = Point(w / 4, w / 8);
  rook_points[0][16] = Point(w / 4, 3 * w / 8);
  rook_points[0][17] = Point(13 * w / 32, 3 * w / 8);
  rook_points[0][18] = Point(5 * w / 16, 13 * w / 16);
  rook_points[0][19] = Point(w / 4, 13 * w / 16);

  const Point* ppt[1] = { rook_points[0] };
  int npt[] = { 20 };

  fillPoly(img,
        ppt,
        npt,
        1,
        Scalar(255, 255, 255),
        lineType);
}

// 绘直线
void MyLine(Mat img, Point start, Point end)
{
  int thickness = 2;
  int lineType = 8;
  line(img,
    start,
    end,
    Scalar(0, 0, 0),
    thickness,
    lineType);
}
