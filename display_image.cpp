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
    // image ��cv::Mat ���ͣ������ͼʧ�ܣ���cv::Mat::data=nullptr
    // ����ʽ��(!nullptr) ���Ϊtrue
    if(! image.data )
    {
        cout <<  "�޷��򿪻��Ҳ���ͼ���ļ�" << std::endl ;
        return -1;
    }

	// ������ʾͼ���ļ��Ĵ���
	namedWindow("Display window", WINDOW_NORMAL);



	// �ڴ�����ʾͼ���ļ�
    imshow( "Display window", image );

	// ���ڵȴ�����
    waitKey(0);

    return 0;
}

int (*run_display_image)() =&run5332;
