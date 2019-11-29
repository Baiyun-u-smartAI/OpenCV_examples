//PredictCard.h
//Author: fengqi
#ifndef PREDICT_CARD
#define PREDICT_CARD

#include <iostream>
#include <string>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv::ml;

extern int thresh;
extern int maxval;
extern Mat m_;

void train_pixel(); //train the knn model for classifying.
int splitCard(Mat &m, int i, string num_, string flag_); //split the card to detect the number and flag.
int findCard(Mat &m); //find the card region which read from camera.
int predictNum(Mat &m); //predict the num of card.
int predictFlag(Mat &m); //predict the flag of card.
void update(int, void*);
/**
reference: this function is the [main-function] to predict the card-picture which sended from the caller.
        - first, findCard() to determine the card region;
        - then, splitCard() to detect the flag and number of the card;
		- last, if split succeed, call predictFlag() and predictNum() to predict the card using knn-model
	      which trained before.
function: scan(Mat &,int &,int &);
parameter: m - the Mat read from outside which includes the card.
           suit - the flag of card, return to the caller if detected the flag correctly.
		   rank - the number of card, return to the caller if detected the number correctly.
return: void
*/
void scan(Mat &m,int &suit, int &rank){
    //----------从单张图像找出数字和花色，比如从摄像头采集的图像---------------------
    int flag = findCard(m);
    if (flag == 0){
        //Mat m = imread("card.jpg", 0);
        int result = splitCard(m, 1, "num", "flag");
        if (result == 0){
            cout << "截取成功，按任意键进行预测，ctrl-c 退出..." <<endl;

            waitKey();
            Mat flag = imread("flag.jpg", 0);
            Mat num = imread("num.jpg", 0);
            suit = predictFlag(flag);
            rank = predictNum(num);
        }
        else{
            cout << "识别失败，请重新截取图片" ;
            cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
            destroyWindow("num");
            destroyWindow("flag");
            suit = -1;
            rank = -1;
            return;
        }
    }
}

void train_pixel()
{
    Mat NumData, NumLabels, FlagData, FlagLabels;
    int trainNum = 40;
    string NumName[] = { "1_", "2_", "3_", "4_", "5_", "6_", "7_", "8_", "9_", "10_", "j_", "q_", "k_" };
    string FlagName[] = { "hongtao_", "fangkuai_", "meihua_", "heitao_" };
    for (int i = 0; i < trainNum * 13; i++){
        Mat img, tmp;
        string path = "TrainSample\\";
        path.append(NumName[i / trainNum]).append(to_string((i%trainNum))).append(".jpg");
        img = imread(path, 0);
        resize(img, tmp, Size(30, 40));
        NumData.push_back(tmp.reshape(0, 1));  //序列化后放入特征矩阵
        NumLabels.push_back(i / trainNum + 1);  //对应的标注
    }
    NumData.convertTo(NumData, CV_32F); //uchar型转换为cv_32f
    //使用KNN算法
    int K = 5;
    Ptr<TrainData> tData = TrainData::create(NumData, ROW_SAMPLE, NumLabels);
    Ptr<KNearest> NumModel = KNearest::create();
    NumModel->setDefaultK(K);
    NumModel->setIsClassifier(true);
    NumModel->train(tData);
    NumModel->save("./num_knn_pixel.yml");
    //-----------------------------------------------------------------------------------------------
    trainNum = 60;
    for (int i = 0; i < trainNum * 4; i++){
        Mat img, tmp;
        string path = "TrainSample\\";
        path.append(FlagName[i / trainNum]).append(to_string((i%trainNum))).append(".jpg");
        img = imread(path, 0);
        resize(img, tmp, Size(30, 30));
        FlagData.push_back(tmp.reshape(0, 1));  //序列化后放入特征矩阵
        FlagLabels.push_back(i / trainNum + 1);  //对应的标注
    }
    FlagData.convertTo(FlagData, CV_32F); //uchar型转换为cv_32f
    //使用KNN算法
    int L = 5;
    Ptr<TrainData> tFlag = TrainData::create(FlagData, ROW_SAMPLE, FlagLabels);
    Ptr<KNearest> FlagModel = KNearest::create();
    FlagModel->setDefaultK(L);
    FlagModel->setIsClassifier(true);
    FlagModel->train(tFlag);
    FlagModel->save("./flag_knn_pixel.yml");
}

void update(int, void*){
    Mat gray, bin;
    cvtColor(m_, gray, COLOR_BGR2GRAY);
    threshold(gray, bin, thresh, maxval, THRESH_BINARY);
    imshow("bin",bin);

}

int findCard(Mat &m){
    Mat gray, bin;
    cvtColor(m, gray, COLOR_BGR2GRAY);
    //imshow("gray", gray);

    //################################################

    threshold(gray, bin, thresh, maxval, THRESH_BINARY);  //---对光照和环境要求较高，阈值设置合适值-----------------
    imshow("bin",bin);
    //################################################
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<vector<Point>>::iterator It;
    //-------------------找出最外层轮廓，即扑克牌的轮廓--------------------------------
    int up = 2000, down = 0, right = 0, left = 2000;
    for (It = contours.begin(); It < contours.end(); It++){
        Rect rect = boundingRect(*It);
        Point tl = rect.tl();
        Point br = rect.br();
        if (up>tl.y) up = tl.y;
        if (down < br.y) down = br.y;
        if (left>tl.x) left = tl.x;
        if (right < br.x) right = br.x;
    }
    if (up == 2000 || left == 2000) return -1;
    Mat& card=m;
    card = gray(Range(up + 10, down), Range(left + 2, right)); //切割掉左上角一定区域的背景，便于定位数字和花色
    //----------漫水填充，去掉扑克牌外面的黑色像素，只留下黑色的数字、花色以及白色背景------------------
    threshold(card, card, thresh, 255, THRESH_BINARY); //注意阈值选取
    floodFill(card, Point(0, 0), Scalar(255, 255, 255));
    floodFill(card, Point(0, card.rows - 1), Scalar(255, 255, 255));
    floodFill(card, Point(card.cols - 1, 0), Scalar(255, 255, 255));
    floodFill(card, Point(card.cols - 1, card.rows - 1), Scalar(255, 255, 255));
    imwrite("card.jpg", card);
    imshow("card",card);
    return 0;
}

int splitCard(Mat &m, int i, string num_path, string flag_path){
    //static int id=17;
    //-------------------------找轮廓确定数字和花色的位置----------------------------------------------
    threshold(m, m, 150, 255, THRESH_BINARY_INV); //注意阈值选取，与上一步重复了
    //-------------------------找最左上角的一块联通区域，即扑克牌的数字---------------------------------
    vector<vector<Point>> contours_Num;//存放findContours后的每一条轮廓contours_Num[i]表示轮廓的点集
    vector<Vec4i> hierarchy_Num;
    findContours(m, contours_Num, hierarchy_Num, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    int up = 1000, down = 1000, right = 1000, left = 1000;//上下左右边界的最大值
    for (auto It_Num = contours_Num.begin(); It_Num < contours_Num.end(); It_Num++){
        Rect rect = boundingRect(*It_Num);//输入某条轮廓的点集，计算某一个轮廓的最小矩形边界
        Point TopLeftPoint = rect.tl();//左上
        Point BottomRightPoint = rect.br();//右下
        if (up > TopLeftPoint.y) up = TopLeftPoint.y;//更新上边界
        if (down > BottomRightPoint.y) down = BottomRightPoint.y;//更新下边界
        if (left > TopLeftPoint.x && (BottomRightPoint.x - TopLeftPoint.x > 20)){
            left = TopLeftPoint.x; right = BottomRightPoint.x;
        }//左右角点距离要至少相差20个像素，更新左右边界
    }
    if (down - up < 25 || right - left < 20) return -1; //分辨率低于25x20判断为提取数字失败
    if (down - up > 50 || right - left > 50) return -1; //分辨率高于50x50判断为提取数字失败
    Mat num = m(Range(up, down), Range(left, right));
    Mat tmp = m(Range(down, m.rows), Range(left, right+5));
    imshow("num", num);
    //-------------------------截去数字区域，从余下区域用同样方法提取花色--------------------------------
    vector<vector<Point>> contours_Flag;
    vector<Vec4i> hierarchy_Flag;
    findContours(tmp, contours_Flag, hierarchy_Flag, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    up = 1000; down = 1000; right = 1000; left = 1000;
    for (auto It_Flag = contours_Flag.begin(); It_Flag < contours_Flag.end(); It_Flag++){
        Rect rect = boundingRect(*It_Flag);//输入某条轮廓的点集，计算某一个轮廓的最小矩形边界
        Point TopLeftPoint = rect.tl();//左上
        Point BottomRightPoint = rect.br();//右下
        if (up > TopLeftPoint.y) up = TopLeftPoint.y;//更新上边界
        if (down > BottomRightPoint.y) down = BottomRightPoint.y;//更新下边界
        if (left > TopLeftPoint.x && (BottomRightPoint.x - TopLeftPoint.x > 20)){
            left = TopLeftPoint.x; right = BottomRightPoint.x;
        }//左右角点距离要至少相差20个像素，更新左右边界
    }
    if (down - up < 25) return -1; //分辨率低于25x20判断为提取花色失败
    Mat flag = tmp(Range(up, down), Range(left, right));
    imshow("flag", flag);
    //imwrite(num_path.append(to_string(i)).append(".jpg"), num); //训练数据保存
    //imwrite(flag_path.append(to_string(i)).append(".jpg"), flag);
    imwrite(num_path.append(".jpg"), num); //预测数据保存
    imwrite(flag_path.append(".jpg"), flag);
    return 0;
}

int predictNum(Mat &m){
    Ptr<KNearest> model_pixel = Algorithm::load<KNearest>("num_knn_pixel.yml");
    Mat temp;
    resize(m, temp, Size(30, 40));
    Mat vec1;
    vec1.push_back(temp.reshape(0, 1));
    vec1.convertTo(vec1, CV_32F);
    int r1 = model_pixel->predict(vec1);   //对所有行进行预测
    switch (r1){
        case 1:
            cout << "A"; break;
        case 11:
            cout << "J"; break;
        case 12:
            cout << "Q"; break;
        case 13:
            cout << "K"; break;
        default:
            cout << r1; break;
    }
    cout << endl;
    return r1;
}

int predictFlag(Mat &m){
    Ptr<KNearest> model_pixel = Algorithm::load<KNearest>("flag_knn_pixel.yml");
    Mat temp;
    resize(m, temp, Size(30, 30));
    Mat vec1;
    vec1.push_back(temp.reshape(0, 1));
    vec1.convertTo(vec1, CV_32F);
    int r1 = model_pixel->predict(vec1);   //对所有行进行预测
    cout << "识别的扑克牌是：";
    switch (r1){
        case 1:
            cout << "红桃 "; break;
        case 2:
            cout << "方块 "; break;
        case 3:
            cout << "梅花 "; break;
        case 4:
            cout << "黑桃 "; break;
        default:
            break;
    }
    return r1;
}

#endif
