#include <iostream>
#include <opencv2\opencv.hpp>
#include "PredictCard.h"

using namespace std;
using namespace cv;
Mat m_;
int manual=0;
int thresh;
int maxval;

int main(){
    VideoCapture capture(1);
    int suit = 0, rank = 0;
    waitKey(200);
    cout<<"拉动滑杆调节阈值1，使得扑克牌清晰可见后，按ESC退出"<<endl;
    while (1){
        Mat m;

        capture >> m;

        int a=0;

        if(!manual){

            m_=m;
            thresh=50,maxval=255;
            namedWindow("bin",WINDOW_AUTOSIZE);
            createTrackbar("1","bin",&thresh,255,update);
            createTrackbar("2","bin",&maxval,255,update);
            update(0,0);
            do{
                capture >> m_;
            }while(waitKey(10)!=27);
            manual=1;
            destroyWindow("bin");
        }





        imshow("camera",m);
        scan(m,suit, rank);
        //cout << "suit: " << suit << ", rank: " << rank << endl;
        waitKey(100);

    }
    return 0;

}
