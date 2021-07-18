#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "board.h"
#include "ctrlpanel.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(int gameType, QWidget *parent = nullptr);

    int _gameType;
signals:

};

#endif // MAINWINDOW_H
