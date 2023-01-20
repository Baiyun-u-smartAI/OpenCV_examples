#include <opencv2/opencv.hpp>
using namespace cv;
int main(void)
{
    FileStorage fs("./VID5.xml", FileStorage::READ);
    vector<string> img_list;
    fs["images"] >> img_list;
    for_each(img_list.begin(), img_list.end(), [](const string& path) {
        cout << path << endl;
    });
    fs.release();
    
    return 0;
}
    
