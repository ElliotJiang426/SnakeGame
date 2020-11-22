#include "campaign.h"
#include "multiplesnake.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>

campaign::campaign(QWindow *parent) :
    QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{
    w.resize(306, 388);

    b1.setParent(&w);
    b2.setParent(&w);
    b3.setParent(&w);
    b4.setParent(&w);

    b1.setText("2 PLAYERS");
    b2.setText("3 PLAYERS");
    b3.setText("4 PLAYERS");
    b4.setText("QUIT");

    b1.setGeometry(80, 40, 121, 41);
    b2.setGeometry(80, 110, 121, 41);
    b3.setGeometry(80, 180, 121, 41);
    b4.setGeometry(80, 250, 121, 41);

    QObject::connect(&b1, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    QObject::connect(&b2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    QObject::connect(&b3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));
    QObject::connect(&b4, SIGNAL(clicked()), &w, SLOT(close()));

    w.show();
}

void campaign::on_pushButton_clicked()
{
    m = new multipleSnake(2);
    m->RasterWindow::show();
}

void campaign::on_pushButton_2_clicked()
{
    m = new multipleSnake(3);
    m->RasterWindow::show();
}

void campaign::on_pushButton_3_clicked()
{
    m = new multipleSnake(4);
    m->RasterWindow::show();
}

