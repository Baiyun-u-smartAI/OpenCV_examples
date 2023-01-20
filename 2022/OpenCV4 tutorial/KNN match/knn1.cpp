//
// Created by pc004 on 2022/11/13.
//
#include <opencv2/opencv.hpp>
#include <iterator>
#include <opencv2/ml.hpp>
using namespace cv;
using namespace std;
int main() {
    unsigned trainingNums = 0, testingNums = 0;
    map<int, vector<string> > trainingPaths, testingPaths;
    for (int i = 0; i < 10; ++i) {
        // 将所有的文件夹内的图片路径集合(std::string)映射到trainingPaths的i索引上
        glob(std::string(R"(MNIST\training\)") + to_string(i) + R"(\*.png)", trainingPaths[i]);
        trainingNums += trainingPaths[i].size();
        glob(std::string(R"(MNIST\testing\)") + to_string(i) + R"(\*.png)", testingPaths[i]);
        testingNums += testingPaths[i].size();
    }
    cout <<"train:" << trainingNums << ", test:" << testingNums << endl;


    if (false) {
        vector<int> trainLabel;
        Mat trainData = Mat::zeros(Size(28*28, trainingNums), CV_32F);
        // 获取训练集数据
        int i = 0;
        for (auto p: trainingPaths) {
            for(auto name: p.second) {
                trainLabel.push_back(p.first);
                Mat image = imread(name, IMREAD_GRAYSCALE);
                image.convertTo(image, CV_32F);
                image = image.reshape(1, 1);// 展平数据
                image.copyTo(trainData.row(i++));
            }
        }

        auto knn = cv::ml::KNearest::create();
        knn->setIsClassifier(true);
        knn->setDefaultK(5);
        knn->train(Mat_<float>(trainData), cv::ml::ROW_SAMPLE, trainLabel);
        knn->save("mnist_knn.xml");
    }

    // 导入模型
    auto knn_saved = cv::ml::KNearest::load("mnist_knn.xml");

    // 训练集数据
    int correct = 0, err = 0;
    for (auto p: testingPaths) {
        for(auto name: p.second) {

            Mat image = imread(name, IMREAD_GRAYSCALE);
            image.convertTo(image, CV_32F);
            image = image.reshape(1, 1);// 展平数据
            if( int(knn_saved->predict(image)) == p.first) correct++;
            else err++;

        }
    }

    cout << "correct: " << correct << ", error: " << err << endl;
    cout << correct / (correct+err+.0) << endl;


    // test for an image
//    Mat soloTest = imread("MNIST/testing/3/309.png", IMREAD_GRAYSCALE);
//    soloTest.convertTo(soloTest, CV_32F);
//    soloTest = soloTest.reshape(1, 1);// 展平数据
//
//    cout << knn_saved->predict(soloTest) << endl;


}

