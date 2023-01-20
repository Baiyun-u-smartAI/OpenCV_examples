#include "widget.h"

#include "myapplication.h"
int main(int argc, char *argv[])
{
    MyApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
