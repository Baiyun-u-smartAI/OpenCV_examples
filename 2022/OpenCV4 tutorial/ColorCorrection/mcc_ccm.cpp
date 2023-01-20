#include <opencv2/opencv.hpp>
#include <opencv2/mcc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
using namespace mcc;
using namespace ccm;
int main(int argc, char *argv[])
{
    Mat image, imageCopy, out_img;
    image = imread("20210407213305115 (1).png");
    imageCopy = image.clone();
    imshow("original", imageCopy);
    Ptr<CCheckerDetector> detector = CCheckerDetector::create();
    // Marker type to detect
    if (!detector->process(image, MCC24, 1))
    {
        printf("ChartColor not detected \n");
    }
    else
    {
        printf("ok!\n");
        std::vector<Ptr<mcc::CChecker>> checkers = detector->getListColorChecker();

        for (const Ptr<mcc::CChecker>& checker : checkers)
        {
            // current checker
            Ptr<CCheckerDraw> cdraw = CCheckerDraw::create(checker);
            cdraw->draw(image);

            Mat chartsRGB = checker->getChartsRGB();
            Mat src = chartsRGB.col(1).clone().reshape(3, chartsRGB.rows/3);
            //cout << src <<endl;
            src /= 255.0;
            // [get_ccm_Matrix]：对于每个ColorChecker，都可以计算一个ccm矩阵以进行颜色校正。Model1是ColorCorrectionModel类的对象，可以根据需要来修改参数以获得最佳色彩校正效果。

            ColorCorrectionModel model1(src, cv::ccm::COLORCHECKER_Macbeth);
//            model1.setLinear(LINEARIZATION_GAMMA);
//            model1.setLinearGamma(2.5);
//            model1.setLinearDegree(3);
//            model1.setSaturatedThreshold(0, 1);
            model1.run();
            Mat ccm = model1.getCCM();
            std::cout<<"ccm "<<ccm<<std::endl;
            double loss = model1.getLoss();
            std::cout<<"loss "<<loss<<std::endl;
            Mat img_;
            cvtColor(imageCopy, img_, COLOR_BGR2RGB);
            img_.convertTo(img_, CV_64F);
            const int inp_size = 255;
            const int out_size = 255;
            img_ = img_ / inp_size;
            Mat calibratedImage= model1.infer(img_);
            Mat out_ = calibratedImage * out_size;
            // [Save_calibrated_image]：保存已校准的图像。
            out_.convertTo(out_, CV_8UC3);
            Mat img_out = min(max(out_, 0), out_size);

            cvtColor(img_out, out_img, COLOR_RGB2BGR);
        }
    }
    //imshow("image result", image);

    imshow("out_img", out_img);
    imwrite("MacBethColorChecker.jpg", out_img);
    waitKey();


    return 0;
}