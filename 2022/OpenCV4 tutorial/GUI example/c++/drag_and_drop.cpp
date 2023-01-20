#include "drag_and_drop.h"

#include <QTimer>

Drag_and_drop::Drag_and_drop(QWidget *parent) : QWidget(parent)
{
    this->setAcceptDrops(true);//接受拖拽
    this->setAttribute(Qt::WA_StyledBackground, true);//呈现颜色
    timer = new QTimer;
}

void Drag_and_drop::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("text/uri-list")) {

           event->acceptProposedAction();
    }

    timer->setInterval(300);
    timer->start();
    this->setStyleSheet("border: 2px solid rgb(0, 0, 0);\nbackground-color: rgb(238, 0, 255);");

    connect(timer,&QTimer::timeout,[=](){
        this->setStyleSheet("border: 2px solid rgb(0, 0, 0);\nbackground-color: none;");
        timer->stop();

    });
}

void Drag_and_drop::dropEvent(QDropEvent *event)
{
       QList<QUrl> urls = event->mimeData()->urls();
        if (urls.isEmpty()) {

            return;
        }

    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {

        return;
    }
    emit dropFinished(&fileName);
//    qDebug()<<fileName;
}





