#include <opencv2/opencv.hpp>
using namespace cv;
void display(Mat &im, Mat &bbox)
{
  int n = bbox.rows;
  for(int i = 0 ; i < n ; i++)
  {
    line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
  }
  
  imshow("result", im);
}

int main(int argc, char* argv[])
{
    // Read image
    Mat inputImage;
    if(argc>1)
        inputImage = imread(argv[1]);
    else
        inputImage = imread("encode_data.jpg");

    QRCodeDetector qrDecoder;

    Mat bbox, rectifiedImage;

    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if(data.length()>0)
    {
        std::cout << "Decoded Data : " << data << std::endl;

        display(inputImage, bbox);
        rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
        namedWindow("Rectified QRCode", WINDOW_NORMAL); // could be resized window
        imshow("Rectified QRCode", rectifiedImage);

        waitKey(0);
    }
    else
        std::cout << "QR Code not detected" << std::endl;
}