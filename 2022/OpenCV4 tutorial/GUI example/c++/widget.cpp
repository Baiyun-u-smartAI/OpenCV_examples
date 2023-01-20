#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    graphicsScene = new QGraphicsScene(ui->widget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_widget_dropFinished(QString * fileName)
{
    this->data = cv::imread(fileName->toStdString());
    //ImageProcessing(this->data);
    if (!data.empty()){
        cv::namedWindow(" ", cv::WINDOW_GUI_EXPANDED);
        cv::imshow(" ",this->data);//正常显示
        this->graphicsScene->clear();
        this->graphicsScene->addPixmap(wrapper::convert2QT(this->data));
        ui->graphicsView->setScene(this->graphicsScene);
        ui->graphicsView->update();

        ui->label_2->setNum(0);
        ui->horizontalSlider->setValue(0);

    }
    //    else{
    //        qDebug()<<"!";
    //    }
}

void Widget::ImageProcessing(cv::Mat &InputOuputData)
{
    try{
//        cv::Mat dst;
//        cv::Mat kernel=wrapper::loadFromQrc("://kernel.png",cv::IMREAD_GRAYSCALE);

//        cv::morphologyEx(InputOuputData,dst,cv::MORPH_DILATE,kernel);
        if (InputOuputData.channels()!=1){
            InputOuputData = cv::Scalar(255,255,255)-InputOuputData;
        }
        else{
            InputOuputData = 255 - InputOuputData;
        }
//        InputOuputData.release();
//        InputOuputData = dst.clone();
    }catch(std::exception& ex){
        qDebug()<<ex.what();
    }
}


void Widget::on_horizontalSlider_sliderMoved(int position)
{
    ui->label_2->setNum(position);
    if(!data.empty()) {
        cv::Mat show = data + cv::Scalar(position, position, position);

        cv::imshow("",show);//正常显示
        this->graphicsScene->clear();
        this->graphicsScene->addPixmap(wrapper::convert2QT(show));
        ui->graphicsView->setScene(this->graphicsScene);
        ui->graphicsView->update();


    }
}

