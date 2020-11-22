#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMutex>
#include "mainwindow.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void createView();

private slots:
//    void testBtnSlot();

private:
    mainwindow *w;
};

#endif // WIDGET_H
