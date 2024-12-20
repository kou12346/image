#include "iamgeprocessor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IamgeProcessor w;
    w.show();
    return a.exec();
}
