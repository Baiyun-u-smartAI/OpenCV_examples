#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int run5332()
{


    Mat image;

	// ����ͼ���ļ�
    image = imread("1.jpg", IMREAD_COLOR);

	// ����ļ��Ƿ��ȡ�ɹ�
    if(! image.data )
    {
        cout <<  "�޷��򿪻��Ҳ���ͼ���ļ�" << std::endl ;
        return -1;
    }

	// ������ʾͼ���ļ��Ĵ���
	namedWindow("Display window", WINDOW_NORMAL);

	// CV_WINDOW_FREERATIO �� CV_WINDOW_KEEPRATIO
	// CV_GUI_NORMAL �� CV_GUI_EXPANDED

	// �ڴ�����ʾͼ���ļ�
    imshow( "Display window", image );

	// ���ڵȴ�����
    waitKey(0);

    return 0;
}

int (*run_display_image)() =&run5332;