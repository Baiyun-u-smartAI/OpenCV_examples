#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iterator>

using namespace cv;


int main(int argc, const char* argv[])
{
    Mat img = imread("./aruco.jpg");
    std::vector< int > markerIds;
    std::vector< std::vector<Point2f> > markerCorners;
    aruco::detectMarkers(img, aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_100), markerCorners, markerIds);
    for (int i = 0; i < markerIds.size(); i++) {
        Point2f topLeft = markerCorners.at(i).at(0);
        Point2f topRight = markerCorners.at(i).at(1);
        Point2f bottomRight = markerCorners.at(i).at(2);
        Point2f bottomLeft = markerCorners.at(i).at(3);
        line(img, topLeft, topRight, Scalar(0, 255, 0), 5);
        line(img, topRight, bottomRight, Scalar(0, 255, 0), 5);
        line(img, bottomRight, bottomLeft, Scalar(0, 255, 0), 5);
        line(img, bottomLeft, topLeft, Scalar(0, 255, 0), 5);
        Point2f c((topLeft.x + bottomRight.x) / 2.0,
            (topLeft.y + bottomRight.y) / 2.0);

        circle(img, c, 4, Scalar(0, 0, 255), -1);


        putText(img, std::to_string(markerIds.at(i)),
                Point2f(topLeft.x, topLeft.y - 15),
                   FONT_HERSHEY_SIMPLEX,
                   2, Scalar(0, 0, 255), 5);

    }


    namedWindow("aruco", WINDOW_NORMAL);
    imshow("aruco", img);
    waitKey();
    return 0;
}
