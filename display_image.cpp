#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	argv[1] = "C:\\images\\lena.jpg";

    Mat image;

	// ����ͼ���ļ�
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	// ����ļ��Ƿ��ȡ�ɹ�
    if(! image.data )
    {
        cout <<  "�޷��򿪻��Ҳ���ͼ���ļ�" << std::endl ;
        return -1;
    }

	// ������ʾͼ���ļ��Ĵ���
	namedWindow("Display window", CV_WINDOW_NORMAL);

	// CV_WINDOW_FREERATIO �� CV_WINDOW_KEEPRATIO
	// CV_GUI_NORMAL �� CV_GUI_EXPANDED

	// �ڴ�����ʾͼ���ļ�
    imshow( "Display window", image );

	// ���ڵȴ�����
    waitKey(0);

    return 0;
}

