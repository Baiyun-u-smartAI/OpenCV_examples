#include "OpenCV_example.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
int run901()
{
	string text = "Text and rectangle demostration";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;

	Mat img(300, 900, CV_8UC3, Scalar::all(0));

	int baseline = 0;
	// Calculates the width and height of a text string.
	// 返回的Size里面textSize.width和textSize.height
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	// center the text
	Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);

	// draw the box
	rectangle(img, textOrg + Point(0, baseline),
		textOrg + Point(textSize.width, -textSize.height),
		Scalar(0, 0, 255));
	// ... and the baseline first
	line(img, textOrg + Point(0, thickness),
		textOrg + Point(textSize.width, thickness),
		Scalar(0, 0, 255));

	// then put the text itself
	// Scalar::all(255)就是Scalar(255, 255, 255)
	putText(img, text, textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);

	//namedWindow("getText", );
	imshow("getText", img);

	waitKey();
	return 0;
}

int(*run_getTextSize)()=run901;
