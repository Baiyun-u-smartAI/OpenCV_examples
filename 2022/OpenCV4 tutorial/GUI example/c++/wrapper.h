#ifndef WRAPPER_H
#define WRAPPER_H
#include <QThread>
#include <QFile>
#include <QPixmap>

#include <opencv2/opencv.hpp>



class wrapper
{
public:
//    wrapper();
    static QPixmap convert2QT(const cv::Mat &src);

    static cv::Mat loadFromQrc(QString qrc, int flag = cv::IMREAD_COLOR);

};

#endif // WRAPPER_H
