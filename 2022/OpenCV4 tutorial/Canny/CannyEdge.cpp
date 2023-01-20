#include <opencv2/opencv.hpp>

using namespace cv;


int main( int argc, const char** argv )
{
    struct Userdata
    {
        int edgeThresh, edgeThreshScharr;
        Mat image, gray, blurImage, cedge;
    } userdata 
    {
        .edgeThresh = 1,
        .edgeThreshScharr = 1,
        .image = imread("aaa.jpg", IMREAD_COLOR)
    };
      
    userdata.cedge.create(userdata.image.size(), userdata.image.type());
    cvtColor(userdata.image, userdata.gray, COLOR_BGR2GRAY);
    

    // Create a window
    namedWindow("Edge map : Canny default (Sobel gradient)", 1);
    
    // create a toolbar
    createTrackbar("Canny threshold default", "Edge map : Canny default (Sobel gradient)", &userdata.edgeThresh, 100, [](int edgeThresh, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.edgeThresh = edgeThresh;
        static Mat edge1;
        blur(ud.gray, ud.blurImage, Size(3,3));
        // Run the edge detector on grayscale
        Canny(ud.blurImage, edge1, ud.edgeThresh, ud.edgeThresh*3, 3);
        ud.cedge = Scalar::all(0);
        ud.image.copyTo(ud.cedge, edge1);
        imshow("Edge map : Canny default (Sobel gradient)", ud.cedge);
    }, &userdata);


    namedWindow("Edge map : Canny with custom gradient (Scharr)", 1);
    createTrackbar("Canny threshold Scharr", "Edge map : Canny with custom gradient (Scharr)", &userdata.edgeThreshScharr, 400, [](int edgeThreshScharr, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.edgeThreshScharr = edgeThreshScharr;
        static Mat edge2, dx, dy;
        blur(ud.gray, ud.blurImage, Size(3,3));
        Scharr(ud.blurImage, dx, CV_16S, 1, 0);
        Scharr(ud.blurImage, dy, CV_16S, 0, 1);
        Canny( dx,dy, edge2, ud.edgeThreshScharr, ud.edgeThreshScharr*3 );
        ud.cedge = Scalar::all(0);
        ud.image.copyTo(ud.cedge, edge2);
        imshow("Edge map : Canny with custom gradient (Scharr)", ud.cedge);
    }, &userdata);

    
    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    return 0;
}