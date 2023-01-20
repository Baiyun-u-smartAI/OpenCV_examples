#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv)
{
    // Declare the output variables
    Mat dst, cdst, cdstP;
    
    // Loads an image
    Mat src = imread( "circles.jpg", IMREAD_GRAYSCALE );


    // Edge detection
    Canny(src, dst, 50, 200, 3);
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    // Standard Hough Line Transform
    std::vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }

    struct  Userdata
    {
        Mat dst, cdstP;
        int threshold, minLineLength, maxLineGap;		

    } userdata
    {
        dst:std::move(dst),
        cdstP:std::move(cdstP),
        threshold:10,
        minLineLength:10,
        maxLineGap:2
    };
    
    namedWindow("Detected Lines (in red) - Probabilistic Line Transform");
    createTrackbar("threshold:", "Detected Lines (in red) - Probabilistic Line Transform", &userdata.threshold, 30, [](int threshold, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.threshold = threshold;
        // a modification of the Hough transform.
        std::vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(ud.dst, linesP, 1, CV_PI/180, ud.threshold*5, ud.minLineLength*5, ud.maxLineGap*5 ); // runs the actual detection
        Mat dst = ud.cdstP.clone();
    // Draw the lines
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            Vec4i l = linesP[i];
            line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
        imshow("Detected Lines (in red) - Probabilistic Line Transform", dst);
    }, &userdata);

    createTrackbar("minLineLength:", "Detected Lines (in red) - Probabilistic Line Transform", &userdata.minLineLength, 30, [](int minLineLength, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.minLineLength = minLineLength;
        std::vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(ud.dst, linesP, 1, CV_PI/180, ud.threshold*5, ud.minLineLength*5, ud.maxLineGap*5 ); // runs the actual detection
        Mat dst = ud.cdstP.clone();
    // Draw the lines
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            Vec4i l = linesP[i];
            line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
        imshow("Detected Lines (in red) - Probabilistic Line Transform", dst);
    }, &userdata);


    createTrackbar("maxLineGap:", "Detected Lines (in red) - Probabilistic Line Transform", &userdata.maxLineGap, 30, [](int maxLineGap, void* userdata)->void
    {
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.maxLineGap = maxLineGap;
        std::vector<Vec4i> linesP; // will hold the results of the detection
        HoughLinesP(ud.dst, linesP, 1, CV_PI/180, ud.threshold*5, ud.minLineLength*5, ud.maxLineGap*5 ); // runs the actual detection
        Mat dst = ud.cdstP.clone();
    // Draw the lines
        for( size_t i = 0; i < linesP.size(); i++ )
        {
            Vec4i l = linesP[i];
            line( dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
        }
        imshow("Detected Lines (in red) - Probabilistic Line Transform", dst);
    }, &userdata);




    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    
    // Wait and Exit
    waitKey();
    return 0;
}