#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

/// ����ȫ�����
const int NUMBER = 100;
const int DELAY = 5;

const int window_width = 900;
const int window_height = 600;
int x_1 = -window_width/2;
int x_2 = window_width*3/2;
int y_1 = -window_width/2;
int y_2 = window_width*3/2;

/// ���溯��
static Scalar randomColor( RNG& rng );
int Drawing_Random_Lines( Mat image, char* window_name, RNG rng );
int Drawing_Random_Rectangles( Mat image, char* window_name, RNG rng );
int Drawing_Random_Ellipses( Mat image, char* window_name, RNG rng );
int Drawing_Random_Polylines( Mat image, char* window_name, RNG rng );
int Drawing_Random_Filled_Polygons( Mat image, char* window_name, RNG rng );
int Drawing_Random_Circles( Mat image, char* window_name, RNG rng );
int Displaying_Random_Text( Mat image, char* window_name, RNG rng );
int Displaying_Big_End( Mat image, char* window_name, RNG rng );

int run8923()
{
  int c;

  /// ��������
  char window_name[] = "Drawing_2 Tutorial";

  /// ����������� (RNG)��������ʼ?
  RNG rng( 0xFFFFFFFF );

  /// ��������Ϊ 0 �ľ���
  Mat image = Mat::zeros( window_height, window_width, CV_8UC3 );

  /// ��ʾ����
  imshow( window_name, image );
  waitKey( DELAY );

  /// ��ֱ��
  c = Drawing_Random_Lines(image, window_name, rng);
  if( c != 0 ) return 0;
  waitKey(0);

  /// �泤����
  c = Drawing_Random_Rectangles(image, window_name, rng);
  if( c != 0 ) return 0;

  /// ����Բ
  c = Drawing_Random_Ellipses( image, window_name, rng );
  if( c != 0 ) return 0;

  /// ��������(polylines)
  c = Drawing_Random_Polylines( image, window_name, rng );
  if( c != 0 ) return 0;

  /// ������
  c = Drawing_Random_Filled_Polygons( image, window_name, rng );
  if( c != 0 ) return 0;

  /// ��Բ
  c = Drawing_Random_Circles( image, window_name, rng );
  if( c != 0 ) return 0;

  /// ������
  c = Displaying_Random_Text( image, window_name, rng );
  if( c != 0 ) return 0;

  /// ���
  c = Displaying_Big_End( image, window_name, rng );
  if( c != 0 ) return 0;

  waitKey(0);
  return 0;
}

/// ��������

// ���������ɫ
static Scalar randomColor( RNG& rng )
{
  int icolor = (unsigned) rng;
  // �� 255 �� bit �� & ����
  return Scalar( icolor&255, (icolor>>8)&255, (icolor>>16)&255 );
}


// ��ֱ��
int Drawing_Random_Lines( Mat image, char* window_name, RNG rng )
{
  Point pt1, pt2;

  for( int i = 0; i < NUMBER; i++ )
  {
    pt1.x = rng.uniform( x_1, x_2 );
    pt1.y = rng.uniform( y_1, y_2 );
    pt2.x = rng.uniform( x_1, x_2 );
    pt2.y = rng.uniform( y_1, y_2 );

	line(image, pt1, pt2, randomColor(rng), rng.uniform(1, 10), LINE_AA);
    imshow( window_name, image );
    if( waitKey( DELAY ) >= 0 )
      { return -1; }
  }

  return 0;
}

// �泤����
int Drawing_Random_Rectangles( Mat image, char* window_name, RNG rng )
{
  Point pt1, pt2;
  int lineType = 8;
  int thickness = rng.uniform( -3, 10 );

  for( int i = 0; i < NUMBER; i++ )
  {
    pt1.x = rng.uniform( x_1, x_2 );
    pt1.y = rng.uniform( y_1, y_2 );
    pt2.x = rng.uniform( x_1, x_2 );
    pt2.y = rng.uniform( y_1, y_2 );

    rectangle( image, pt1, pt2, randomColor(rng), MAX( thickness, -1 ), lineType );

    imshow( window_name, image );
    if( waitKey( DELAY ) >= 0 )
      { return -1; }
  }

  return 0;
}

// ����Բ
int Drawing_Random_Ellipses( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;

  for ( int i = 0; i < NUMBER; i++ )
  {
    Point center;
    center.x = rng.uniform(x_1, x_2);
    center.y = rng.uniform(y_1, y_2);

    Size axes;
    axes.width = rng.uniform(0, 200);
    axes.height = rng.uniform(0, 200);

    double angle = rng.uniform(0, 180);

    ellipse( image, center, axes, angle, angle - 100, angle + 200,
             randomColor(rng), rng.uniform(-1,9), lineType );

    imshow( window_name, image );

    if( waitKey(DELAY) >= 0 )
      { return -1; }
  }

  return 0;
}

// ��������(polylines)
int Drawing_Random_Polylines( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;

  for( int i = 0; i< NUMBER; i++ )
  {
    Point pt[2][3];
    pt[0][0].x = rng.uniform(x_1, x_2);
    pt[0][0].y = rng.uniform(y_1, y_2);
    pt[0][1].x = rng.uniform(x_1, x_2);
    pt[0][1].y = rng.uniform(y_1, y_2);
    pt[0][2].x = rng.uniform(x_1, x_2);
    pt[0][2].y = rng.uniform(y_1, y_2);
    pt[1][0].x = rng.uniform(x_1, x_2);
    pt[1][0].y = rng.uniform(y_1, y_2);
    pt[1][1].x = rng.uniform(x_1, x_2);
    pt[1][1].y = rng.uniform(y_1, y_2);
    pt[1][2].x = rng.uniform(x_1, x_2);
    pt[1][2].y = rng.uniform(y_1, y_2);

    const Point* ppt[2] = {pt[0], pt[1]};
    int npt[] = {3, 3};

    polylines(image, ppt, npt, 2, true, randomColor(rng), rng.uniform(1,10), lineType);

    imshow( window_name, image );
    if( waitKey(DELAY) >= 0 )
      { return -1; }
  }
  return 0;
}

// ������
int Drawing_Random_Filled_Polygons( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;

  for ( int i = 0; i < NUMBER; i++ )
  {
    Point pt[2][3];
    pt[0][0].x = rng.uniform(x_1, x_2);
    pt[0][0].y = rng.uniform(y_1, y_2);
    pt[0][1].x = rng.uniform(x_1, x_2);
    pt[0][1].y = rng.uniform(y_1, y_2);
    pt[0][2].x = rng.uniform(x_1, x_2);
    pt[0][2].y = rng.uniform(y_1, y_2);
    pt[1][0].x = rng.uniform(x_1, x_2);
    pt[1][0].y = rng.uniform(y_1, y_2);
    pt[1][1].x = rng.uniform(x_1, x_2);
    pt[1][1].y = rng.uniform(y_1, y_2);
    pt[1][2].x = rng.uniform(x_1, x_2);
    pt[1][2].y = rng.uniform(y_1, y_2);

    const Point* ppt[2] = {pt[0], pt[1]};
    int npt[] = {3, 3};

    fillPoly( image, ppt, npt, 2, randomColor(rng), lineType );

    imshow( window_name, image );
    if( waitKey(DELAY) >= 0 )
       { return -1; }
  }
  return 0;
}

// ��Բ
int Drawing_Random_Circles( Mat image, char* window_name, RNG rng )
{
  int lineType = 8;

  for (int i = 0; i < NUMBER; i++)
  {
    Point center;
    center.x = rng.uniform(x_1, x_2);
    center.y = rng.uniform(y_1, y_2);

    circle( image, center, rng.uniform(0, 300), randomColor(rng),
            rng.uniform(-1, 9), lineType );

    imshow( window_name, image );
    if( waitKey(DELAY) >= 0 )
      { return -1; }
  }

  return 0;
}

// ������
int Displaying_Random_Text( Mat image, char* window_name, RNG rng )
{
	int lineType = 8;

	for ( int i = 1; i < NUMBER; i++ )
	{
		Point org;
		org.x = rng.uniform(x_1, x_2);
		org.y = rng.uniform(y_1, y_2);

		putText( image, "Testing text rendering", org, 
			rng.uniform(0,8), rng.uniform(0,100)*0.05+0.1,
			randomColor(rng), rng.uniform(1, 10), lineType);

		imshow( window_name, image );
		if( waitKey(DELAY) >= 0 )
		{ return -1; }
	}

	return 0;
}

// �����Ƿ����ʾ����
int Displaying_Big_End( Mat image, char* window_name, RNG )
{
	char end_text[] = "�Ұ� OpenCV!";
	// ȡ�����ִ�С
	Size textsize = getTextSize(end_text, FONT_HERSHEY_COMPLEX, 3, 5, 0);
	Point org((window_width - textsize.width)/2, 
		(window_height - textsize.height)/2);

	int lineType = 8;

    Mat image2;

	for( int i = 0; i < 255; i += 2 )
	{
		// ԭͼ�۳�������ɫ,��͸��(saturate)�Ĵ���
		image2 = image - Scalar::all(i);

		// ͼ��
		// ��ʾ������
		// �������½����λ��
		// ���� FONT_HERSHEY_SIMPLEX, FONT_HERSHEY_PLAIN, FONT_HERSHEY_DUPLEX,
		//      FONT_HERSHEY_COMPLEX, FONT_HERSHEY_TRIPLEX, FONT_HERSHEY_COMPLEX_SMALL,
		//      FONT_HERSHEY_SCRIPT_SIMPLEX, or FONT_HERSHEY_SCRIPT_COMPLEX,
		//      ���������FONT_ITALIC���
		// �����С
		// ������ɫ
		// ���ֱʻ���ϸ��
		// ���ֱʻ���̬
		putText(image2, end_text, org,
			FONT_HERSHEY_COMPLEX + FONT_ITALIC,	3,
			Scalar(i, i, 255), 4, lineType);


		imshow( window_name, image2 );

		if( waitKey(DELAY) >= 0 )
		{ return -1; }
	}

	return 0;
}

int(*run_Drawing_2)()=run8923;