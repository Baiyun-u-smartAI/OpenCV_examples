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
    //----------�ӵ���ͼ���ҳ����ֺͻ�ɫ�����������ͷ�ɼ���ͼ��---------------------
    int flag = findCard(m);
    if (flag == 0){
        //Mat m = imread("card.jpg", 0);
        int result = splitCard(m, 1, "num", "flag");
        if (result == 0){
            cout << "��ȡ�ɹ��������������Ԥ�⣬ctrl-c �˳�..." <<endl;

            waitKey();
            Mat flag = imread("flag.jpg", 0);
            Mat num = imread("num.jpg", 0);
            suit = predictFlag(flag);
            rank = predictNum(num);
        }
        else{
            cout << "ʶ��ʧ�ܣ������½�ȡͼƬ" ;
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
        NumData.push_back(tmp.reshape(0, 1));  //���л��������������
        NumLabels.push_back(i / trainNum + 1);  //��Ӧ�ı�ע
    }
    NumData.convertTo(NumData, CV_32F); //uchar��ת��Ϊcv_32f
    //ʹ��KNN�㷨
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
        FlagData.push_back(tmp.reshape(0, 1));  //���л��������������
        FlagLabels.push_back(i / trainNum + 1);  //��Ӧ�ı�ע
    }
    FlagData.convertTo(FlagData, CV_32F); //uchar��ת��Ϊcv_32f
    //ʹ��KNN�㷨
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

    threshold(gray, bin, thresh, maxval, THRESH_BINARY);  //---�Թ��պͻ���Ҫ��ϸߣ���ֵ���ú���ֵ-----------------
    imshow("bin",bin);
    //################################################
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(bin, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<vector<Point>>::iterator It;
    //-------------------�ҳ���������������˿��Ƶ�����--------------------------------
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
    card = gray(Range(up + 10, down), Range(left + 2, right)); //�и�����Ͻ�һ������ı��������ڶ�λ���ֺͻ�ɫ
    //----------��ˮ��䣬ȥ���˿�������ĺ�ɫ���أ�ֻ���º�ɫ�����֡���ɫ�Լ���ɫ����------------------
    threshold(card, card, thresh, 255, THRESH_BINARY); //ע����ֵѡȡ
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
    //-------------------------������ȷ�����ֺͻ�ɫ��λ��----------------------------------------------
    threshold(m, m, 150, 255, THRESH_BINARY_INV); //ע����ֵѡȡ������һ���ظ���
    //-------------------------�������Ͻǵ�һ����ͨ���򣬼��˿��Ƶ�����---------------------------------
    vector<vector<Point>> contours_Num;//���findContours���ÿһ������contours_Num[i]��ʾ�����ĵ㼯
    vector<Vec4i> hierarchy_Num;
    findContours(m, contours_Num, hierarchy_Num, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    int up = 1000, down = 1000, right = 1000, left = 1000;//�������ұ߽�����ֵ
    for (auto It_Num = contours_Num.begin(); It_Num < contours_Num.end(); It_Num++){
        Rect rect = boundingRect(*It_Num);//����ĳ�������ĵ㼯������ĳһ����������С���α߽�
        Point TopLeftPoint = rect.tl();//����
        Point BottomRightPoint = rect.br();//����
        if (up > TopLeftPoint.y) up = TopLeftPoint.y;//�����ϱ߽�
        if (down > BottomRightPoint.y) down = BottomRightPoint.y;//�����±߽�
        if (left > TopLeftPoint.x && (BottomRightPoint.x - TopLeftPoint.x > 20)){
            left = TopLeftPoint.x; right = BottomRightPoint.x;
        }//���ҽǵ����Ҫ�������20�����أ��������ұ߽�
    }
    if (down - up < 25 || right - left < 20) return -1; //�ֱ��ʵ���25x20�ж�Ϊ��ȡ����ʧ��
    if (down - up > 50 || right - left > 50) return -1; //�ֱ��ʸ���50x50�ж�Ϊ��ȡ����ʧ��
    Mat num = m(Range(up, down), Range(left, right));
    Mat tmp = m(Range(down, m.rows), Range(left, right+5));
    imshow("num", num);
    //-------------------------��ȥ�������򣬴�����������ͬ��������ȡ��ɫ--------------------------------
    vector<vector<Point>> contours_Flag;
    vector<Vec4i> hierarchy_Flag;
    findContours(tmp, contours_Flag, hierarchy_Flag, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    up = 1000; down = 1000; right = 1000; left = 1000;
    for (auto It_Flag = contours_Flag.begin(); It_Flag < contours_Flag.end(); It_Flag++){
        Rect rect = boundingRect(*It_Flag);//����ĳ�������ĵ㼯������ĳһ����������С���α߽�
        Point TopLeftPoint = rect.tl();//����
        Point BottomRightPoint = rect.br();//����
        if (up > TopLeftPoint.y) up = TopLeftPoint.y;//�����ϱ߽�
        if (down > BottomRightPoint.y) down = BottomRightPoint.y;//�����±߽�
        if (left > TopLeftPoint.x && (BottomRightPoint.x - TopLeftPoint.x > 20)){
            left = TopLeftPoint.x; right = BottomRightPoint.x;
        }//���ҽǵ����Ҫ�������20�����أ��������ұ߽�
    }
    if (down - up < 25) return -1; //�ֱ��ʵ���25x20�ж�Ϊ��ȡ��ɫʧ��
    Mat flag = tmp(Range(up, down), Range(left, right));
    imshow("flag", flag);
    //imwrite(num_path.append(to_string(i)).append(".jpg"), num); //ѵ�����ݱ���
    //imwrite(flag_path.append(to_string(i)).append(".jpg"), flag);
    imwrite(num_path.append(".jpg"), num); //Ԥ�����ݱ���
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
    int r1 = model_pixel->predict(vec1);   //�������н���Ԥ��
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
    int r1 = model_pixel->predict(vec1);   //�������н���Ԥ��
    cout << "ʶ����˿����ǣ�";
    switch (r1){
        case 1:
            cout << "���� "; break;
        case 2:
            cout << "���� "; break;
        case 3:
            cout << "÷�� "; break;
        case 4:
            cout << "���� "; break;
        default:
            break;
    }
    return r1;
}

#endif
