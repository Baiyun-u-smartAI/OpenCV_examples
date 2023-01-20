#include <opencv2/opencv.hpp>
using namespace cv;
int main(void)
{
    // 搜索目录下所有的jpg文件=>jpgpath
    vector<String> jpgPath; 
    glob("*.jpg", jpgPath);

    // 将jpgpath写入VID5.xml文件中
    FileStorage fs("VID5.xml", FileStorage::WRITE);
    fs << "images" << jpgPath;
    fs.release();
    
    return 0;
}
    
