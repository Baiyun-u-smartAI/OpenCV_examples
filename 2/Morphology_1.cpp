#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCV_example.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// ����ȫ�ֱ���
static Mat src, erosion_dst, dilation_dst;

static char text[] = "Element: 0:Rect 1:Cross 2:Ellipse";

static int erosion_elem = 0;
static int erosion_size = 0;
static int dilation_elem = 0;
static int dilation_size = 0;
static int const max_elem = 2;
static int const max_kernel_size = 21;

/** �������� */
void Erosion(int, void*);
void Dilation(int, void*);

int run3281()
{
	/// ����ͼ���ļ�
	src = imread("opencv-logo.png");
	if (!src.data)
		return -1;

	/// ��������
	namedWindow("ԭͼ", WINDOW_AUTOSIZE);
	namedWindow("��ʴ", WINDOW_AUTOSIZE);
	namedWindow("����", WINDOW_AUTOSIZE);

	moveWindow("����", src.cols, 0);

	/// ������ʴ(Erosion)����
	createTrackbar("Element:", "��ʴ",
		&erosion_elem, max_elem, Erosion);

	createTrackbar("Kernel:", "��ʴ",
		&erosion_size, max_kernel_size,	Erosion);

	/// ��������(Dilation)����
	createTrackbar("Element:", "����",
		&dilation_elem, max_elem, Dilation);

	createTrackbar("Kernel:", "����",
		&dilation_size, max_kernel_size, Dilation);

	imshow("ԭͼ", src);

	/// �����㿪ʼ
	Erosion(0, 0);

	Dilation(0, 0);

	waitKey(0);
	return 0;
}

void Erosion(int, void*)
{
	int erosion_type = 0;
	if (erosion_elem == 0) {
		erosion_type = MORPH_RECT;
	} else if (erosion_elem == 1) {
		erosion_type = MORPH_CROSS;
	} else if (erosion_elem == 2) {
		erosion_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(erosion_type,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	/// ʹ�ý�ʴ(erosion)����
	erode(src, erosion_dst, element);

	// ȡ���������ĵ�
	Point textOrg(10, 25);
	putText(erosion_dst, text, textOrg, FONT_HERSHEY_SIMPLEX, 1, 3);

	imshow("��ʴ", erosion_dst);
}

void Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilation_elem == 0) {
		dilation_type = MORPH_RECT;
	} else if (dilation_elem == 1) {
		dilation_type = MORPH_CROSS;
	} else if (dilation_elem == 2) {
		dilation_type = MORPH_ELLIPSE;
	}

	Mat element = getStructuringElement(dilation_type,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	/// ʹ������(dilation)����
	dilate(src, dilation_dst, element);

	// ȡ���������ĵ�
	Point textOrg(10, 25);
	putText(dilation_dst, text, textOrg, FONT_HERSHEY_SIMPLEX, 1, 3);

	imshow("����", dilation_dst);
}

int (*run_Morphology1)()=run3281;