#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;


int main( int argc, char** argv )
{
    struct Userdata
    {
        Mat src, src_gray;
        int thresh;
        BorderTypes border_t;
        int blockSize;
    } userdata{ src:imread( "CantonTower.png" ),
                thresh:200,
                border_t:BORDER_DEFAULT,
                blockSize:2};


    cvtColor( userdata.src, userdata.src_gray, COLOR_BGR2GRAY );
    namedWindow( "Source image" );
    createTrackbar( "Threshold: ", "Source image", &userdata.thresh, 255,
    [](int thresh, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        if (ud.border_t == 3 || ud.border_t == 5) 
        {
            std::cerr << "border type cannot be BORDER_WRAP(3) or BORDER_TRANSPARENT(5)" << std::endl;
            return;
        }
        ud.thresh = thresh;
        cornerHarris( ud.src_gray, dst, ud.blockSize, 3, .04, ud.border_t );
        static Mat dst_norm, dst_norm_scaled;
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );
        cvtColor(dst_norm_scaled, dst_norm_scaled, COLOR_GRAY2BGR);
        dst_norm_scaled.convertTo(dst_norm_scaled, CV_8UC3);
        for( int i = 0; i < dst_norm.rows ; i++ )
        {
            for( int j = 0; j < dst_norm.cols; j++ )
            {
                if( (int) dst_norm.at<float>(i,j) > ud.thresh )
                {
                    circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0, 0, 255), 2, 8, 0 );
                }
            }
        }
        namedWindow( "Corners detected" );
        imshow( "Corners detected", dst_norm_scaled );

    }
    , &userdata );

    createTrackbar( "border: ", "Source image", (int*)&userdata.border_t, 6,
    [](int border, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        if (border ==6 ) ud.border_t = BORDER_ISOLATED;
        else if (border == 3 || border == 5) 
        {
            std::cerr << "border type cannot be BORDER_WRAP(3) or BORDER_TRANSPARENT(5)" << std::endl;
            return;
        }
        else ud.border_t = (BorderTypes) border;
        cornerHarris( ud.src_gray, dst, ud.blockSize, 3, .04, ud.border_t );
        static Mat dst_norm, dst_norm_scaled;
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );
        cvtColor(dst_norm_scaled, dst_norm_scaled, COLOR_GRAY2BGR);
        dst_norm_scaled.convertTo(dst_norm_scaled, CV_8UC3);
        for( int i = 0; i < dst_norm.rows ; i++ )
        {
            for( int j = 0; j < dst_norm.cols; j++ )
            {
                if( (int) dst_norm.at<float>(i,j) > ud.thresh )
                {
                    circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0, 0, 255), 1, LINE_AA, 0 );
                }
            }
        }
        namedWindow( "Corners detected" );
        imshow( "Corners detected", dst_norm_scaled );

    }
    , &userdata );

    createTrackbar( "blockSize: ", "Source image", &userdata.blockSize, 12,
    [](int blockSize, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        static Mat dst;
        if (ud.border_t == 3 || ud.border_t == 5) 
        {
            std::cerr << "border type cannot be BORDER_WRAP(3) or BORDER_TRANSPARENT(5)" << std::endl;
            return;
        }
        ud.blockSize = blockSize;
        cornerHarris( ud.src_gray, dst, ud.blockSize, 3, .04, ud.border_t );
        static Mat dst_norm, dst_norm_scaled;
        normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
        convertScaleAbs( dst_norm, dst_norm_scaled );
        cvtColor(dst_norm_scaled, dst_norm_scaled, COLOR_GRAY2BGR);
        dst_norm_scaled.convertTo(dst_norm_scaled, CV_8UC3);
        for( int i = 0; i < dst_norm.rows ; i++ )
        {
            for( int j = 0; j < dst_norm.cols; j++ )
            {
                if( (int) dst_norm.at<float>(i,j) > ud.thresh )
                {
                    circle( dst_norm_scaled, Point(j,i), 5,  Scalar(0, 0, 255), 1, LINE_AA, 0 );
                }
            }
        }
        namedWindow( "Corners detected" );
        imshow( "Corners detected", dst_norm_scaled );

    }
    , &userdata );




    imshow( "Source image", userdata.src );
    waitKey();
    return 0;
}
