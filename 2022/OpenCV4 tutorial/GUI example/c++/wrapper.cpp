#include "wrapper.h"



QPixmap wrapper::convert2QT(const cv::Mat &src)
{
    //cv::cvtColor(src,src,cv::COLOR_BGR2RGB);
    QImage imdisplay((uchar*)src.data, src.cols, src.rows, src.step, QImage::Format_RGB888);
    return QPixmap::fromImage(imdisplay.rgbSwapped());
}

cv::Mat wrapper::loadFromQrc(QString qrc, int flag)
{
    //double tic = double(getTickCount());

    QFile file(qrc);
    cv::Mat m;
    if(file.open(QIODevice::ReadOnly))
    {
        qint64 sz = file.size();
        std::vector<uchar> buf(sz);
        file.read((char*)buf.data(), sz);
        m = cv::imdecode(buf, flag);
    }

    //double toc = (double(getTickCount()) - tic) * 1000.0 / getTickFrequency();
    //qDebug() << "OpenCV loading time: " << toc;

    return m;
}
