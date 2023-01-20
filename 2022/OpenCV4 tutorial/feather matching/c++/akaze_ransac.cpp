#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    Mat object = imread("box.png")/*, blur_obj*/;

//    GaussianBlur(object, blur_obj, Size(11, 11), 5);
//    addWeighted(object, 2, blur_obj, -1, 0, object);
    Mat scene = imread("box_in_scene.png");

    Ptr<AKAZE> akaze = AKAZE::create(); // 创建描述符对象detector
    Mat descriptors_object, descriptors_scene;
    vector<KeyPoint> keyPoint_object, keyPoint_scene;
    // 计算描述符
    akaze->detectAndCompute(scene, Mat(), keyPoint_scene, descriptors_scene, false);
    akaze->detectAndCompute(object, Mat(), keyPoint_object, descriptors_object, false);
//    Mat out_obj;
//    drawKeypoints(object, keyPoint_object, out_obj, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
//    imshow("key", out_obj);
//    waitKey();


    if(descriptors_object.empty() || descriptors_scene.empty()){
        cout << "findSamePoint_akaze is no find Point!!!" << endl;
        return -1;
    }

    vector<DMatch> matches;  // 存放暴力匹配结果
    vector<DMatch> goodMatches; // 存放筛选后的匹配结果
    BFMatcher matcher(NORM_HAMMING);  // 暴力匹配对象matcher，用汉明距匹配
    matcher.match(descriptors_object, descriptors_scene,matches); // 特征点匹配
    if(matches.empty()){
        cout << " findSamePoint_AKAZE is no find matches!!!" << endl;
        return -1;
    }


    // if(matches.empty()){
    //     cout << " findSamePoint_AKAZE is no find Point!!!" << endl;
    //     return -1;
    // }

    float maxdist = matches[0].distance; // 获取最大值
    for (auto & match : matches)
    {
        if (maxdist < match.distance)
        {
            maxdist = match.distance;
        }
    }

    float thresh = 0.5;  // 设置距离 // 可以调整精度
    for (auto & matche : matches)
    {
        if (matche.distance < thresh * maxdist)
        {
            goodMatches.push_back(matche);
        }
    }

    if (goodMatches.size() < 2){
        cout << "findSamePoint_AKAZE is no find good Point!!!" << endl;
        return -1;
    }




    Mat result1;
    //  画出匹配结果图
    drawMatches(object, keyPoint_object, scene, keyPoint_scene, goodMatches, result1,
                Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::DEFAULT);

    imshow("AKAZE match",result1);
    waitKey();

    // RANSAC优化

    vector<DMatch> matches_ransac; // 存放RANSAC优化后的结果
    if(goodMatches.size() < 3){
        return -1;
    }
    // 定义保存匹配点对坐标
    //vector<Point2f> modulePoints(goodMatches.size()),imagePoints(goodMatches.size());
    vector<Point2f> objectPoints, scenePoints;
    // 保存从关键点中提取到的匹配点对的坐标
    for(auto & goodMatche : goodMatches)
    {
        objectPoints.push_back(keyPoint_object[goodMatche.queryIdx].pt);
        scenePoints.push_back(keyPoint_scene[goodMatche.trainIdx].pt);
    }

    if(objectPoints.size() < 4 ||  scenePoints.size() < 4 ){ // 匹配点数过少
        return -1;
    }
    if(objectPoints.size() + scenePoints.size() < 9 ){  // 匹配点数过少
        return -1;
    }
    // 匹配点对进行RANSAC过滤
    vector<int> inliersMask(objectPoints.size()); // inliersMask代表findHomography运算的输入点有效性
    Mat H = cv::findHomography(objectPoints, scenePoints, RANSAC, 4, inliersMask);//RANSAC

    // 手动保留 RANSAC 过滤后的匹配点对
    for(int i = 0;i < inliersMask.size();i++)
    {
        if(inliersMask[i])
        {
            matches_ransac.push_back(goodMatches[i]);
        }
    }
    drawMatches(object, keyPoint_object, scene, keyPoint_scene, matches_ransac, result1,
                Scalar::all(-1), Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    imshow("AKAZE match ransac",result1);
    waitKey();


    // 在scene上绘制匹配区域
    std::vector<Point2f> points{Point2f(0, 0), Point2f(object.cols-1, 0), Point2f(object.cols-1, object.rows-1), Point2f(0, object.rows-1) }; // 这是object图的四个点（按照顺时针、逆时针顺序）
    std::vector<Point2i> points0;
    perspectiveTransform(points, points, H);
    // 转化Point2f -> Point2i
    for (const auto& i : points) {
        points0.emplace_back(i);
    }
    // 绘制四边形
    polylines(scene, points0, true, Scalar(255, 0, 0), 2);

    imshow("out",scene);
    waitKey();

    return 0;
}