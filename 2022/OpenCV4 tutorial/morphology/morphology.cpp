#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;



int main( int argc, char** argv )
{
    auto x = MORPH_BLACKHAT;
    struct Userdata{
        Mat src;
        int morph_elem;
        int morph_size;
        int morph_operator;
    } userdata{.src = imread( "binary-icon-30.bmp", IMREAD_GRAYSCALE ),
               .morph_elem = 0,
               .morph_size=0,
               .morph_operator = 0} ;
    

    namedWindow( "Morphology Transformations Demo"); // Create window
    createTrackbar("Operator", "Morphology Transformations Demo", &userdata.morph_operator, 7, [](int Operator, void* userdata)->void{
        
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.morph_operator = Operator;
        static Mat dst;
        Mat element = getStructuringElement( ud.morph_elem, Size( 2*ud.morph_size + 1, 2*ud.morph_size+1 ), Point( ud.morph_size, ud.morph_size ) );
        morphologyEx( ud.src, dst, ud.morph_operator, element );
        imshow( "Morphology Transformations Demo", dst );


    }, &userdata); //创建滑杆

    createTrackbar( "Element", "Morphology Transformations Demo", &userdata.morph_elem, 2, [](int elem_T, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.morph_elem = elem_T;
        static Mat dst;
        Mat element = getStructuringElement( ud.morph_elem, Size( 2*ud.morph_size + 1, 2*ud.morph_size+1 ), Point( ud.morph_size, ud.morph_size ) );
        morphologyEx( ud.src, dst, ud.morph_operator, element );
        imshow( "Morphology Transformations Demo", dst );      
                        
    }, &userdata);
    createTrackbar( "Kernel size:(2n+1)", "Morphology Transformations Demo", &userdata.morph_size, 21, [](int morph_size, void* userdata)->void{
        auto &ud = *static_cast<Userdata*>(userdata);
        ud.morph_size = morph_size;
        static Mat dst;
        Mat element = getStructuringElement( ud.morph_elem, Size( 2*ud.morph_size + 1, 2*ud.morph_size+1 ), Point( ud.morph_size, ud.morph_size ) );
        morphologyEx( ud.src, dst, ud.morph_operator, element );
        imshow( "Morphology Transformations Demo", dst );   

    }, &userdata); //创建滑杆

    waitKey(0);
    return 0;
}
