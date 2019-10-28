#include <iostream>
#include <list>
#include "OpenCV_example.hpp"


using namespace std;


class ny{
    int i=0;
public:
    int* a=&i;


    int* operator()();

};

int* ny::operator()(){
    return a;
};




int main()
{

//    int i=0;
//    int *p=&i;
//    *p=2;
//    ny dd;
//    *(dd())=7;
//    cout<<*(dd.a);
<<<<<<< HEAD
//    run_BasicLinearTransformsTrackbar();
    char* a="ÎÒ";
    cout<<a;
=======
    run_Remap_Demo();

>>>>>>> ca0d3ebe4382b41cc75d8337edea85a9d34b1470
    return 0;


}