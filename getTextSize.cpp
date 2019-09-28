#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

int main(void)
{
	string text = "Text and rectangle demostration";
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;

	Mat img(300, 900, CV_8UC3, Scalar::all(0));

	int baseline = 0;
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
	putText(img, text, textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);

	//namedWindow("getText", );
	imshow("getText", img);

	waitKey();
}

