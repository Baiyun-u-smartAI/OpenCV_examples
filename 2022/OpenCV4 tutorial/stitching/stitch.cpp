#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    Stitcher::Mode mode = Stitcher::PANORAMA;
    vector<Mat> imgs;
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode);
    imgs.push_back(imread("1403636579763555584cam0.png"));
    imgs.push_back(imread("1403636579763555584cam1.png"));
    Stitcher::Status status = stitcher->stitch(imgs, pano);
    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << int(status) << endl;
        return EXIT_FAILURE;
    }
    imshow("result", pano);
    waitKey();
    return 0;
}
