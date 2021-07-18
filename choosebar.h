#ifndef CHOOSEBAR_H
#define CHOOSEBAR_H

#include <QDialog>
#include <QPushButton>

class ChooseBar : public QDialog
{
    Q_OBJECT
public:
    explicit ChooseBar(QWidget *parent = 0);

    QPushButton* _buttons[4];
    int _selectid;

public slots:
    void slotClicked();
};

#endif // CHOOSEBAR_H
