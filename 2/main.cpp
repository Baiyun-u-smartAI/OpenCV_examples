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
//    run_BasicLinearTransformsTrackbar();
    char* a="ÎÒ";
    cout<<a;
    return 0;


}