#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;


int main( int argc, char** argv )
{
    struct Userdata
    {
        Mat img, gray;
        int minRadius, maxRadius;
    } userdata{ img:imread( "circles.jpg" ),
                minRadius:0,
                maxRadius:100};
    
    cvtColor(userdata.img, userdata.gray, COLOR_BGR2GRAY);
    
    //GaussianBlur( 255 - userdata.gray, userdata.gray, Size(5, 5), 2, 2 );
    
    namedWindow( "circles");
    

    createTrackbar( "minRadius: ", "circles", &userdata.minRadius, 100,
    [](int minR, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.minRadius = minR;
        static std::vector<Vec3f> circles;
        HoughCircles(ud.gray, circles, HOUGH_GRADIENT,
                 2, ud.gray.rows/4, 200, 100, ud.minRadius*4, ud.maxRadius*4 );
        Mat img = ud.img.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // draw the circle center
            circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // draw the circle outline
            circle( img, center, radius, Scalar(255,0,0), 3, 8, 0 );
        }
        imshow("circles", img);
    }
    , &userdata );

    createTrackbar( "maxRadius: ", "circles", &userdata.maxRadius, 100,
    [](int maxR, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.maxRadius = maxR;
        static std::vector<Vec3f> circles;
        HoughCircles(ud.gray, circles, HOUGH_GRADIENT,
                 2, ud.gray.rows/4, 200, 100, ud.minRadius*4, ud.maxRadius*4 );
        Mat img = ud.img.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // draw the circle center
            circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // draw the circle outline
            circle( img, center, radius, Scalar(255,0,0), 3, 8, 0 );
        }
        imshow("circles", img);
    }
    , &userdata );

    waitKey();
    return 0;
}
