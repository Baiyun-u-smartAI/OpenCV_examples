#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <opencv2/opencv.hpp>
#include "wrapper.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    ~Widget();
private slots:
    void on_widget_dropFinished(QString*);
    static void ImageProcessing(cv::Mat& InputOuputData);
    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::Widget *ui;
    cv::Mat data;
    QGraphicsScene *graphicsScene;
};
//QPixmap convert2QT(const cv::Mat& src);
#endif // WIDGET_H
