#include <QApplication>

#include <QTime>
#include "mainwindow.h"
#include "choosebar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    ChooseBar bar;
    if(bar.exec() != QDialog::Accepted){
        return 0;
    }


    MainWindow game(bar._selectid);
    game.show();

    return a.exec();
}
