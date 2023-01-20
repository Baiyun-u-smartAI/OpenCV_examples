#ifndef DRAG_AND_DROP_H
#define DRAG_AND_DROP_H

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QWidget>
#include <QMimeData>
#include <QDebug>
#include <QTimer>
class Drag_and_drop : public QWidget
{
    Q_OBJECT
public:
    explicit Drag_and_drop(QWidget *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void dropFinished(QString*);
private:
    QTimer *timer;
};

#endif // DRAG_AND_DROP_H
