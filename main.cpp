#include <QApplication>

#include "singlegame.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    SingleGame sg;
    sg.show();

    return a.exec();
}
