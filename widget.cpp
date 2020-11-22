#include "widget.h"
#include <QDebug>
#include <windows.h>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    createView();
}

void Widget::createView()
{
    w = new mainwindow;
    this->setWindowTitle("SnakeGame");

        // QT里面 控件 都是继承了 QWidget
        QPushButton *b1 = new QPushButton("START");       //创建一个名为hello的按钮

        QPushButton *b2 = new QPushButton("RULES...", this);  //将按钮b2绑定到w上
        QPushButton *b3 = new QPushButton("CAMPAIGN", this);  //将按钮b3绑定到w上
        QPushButton *b4 = new QPushButton("AUTO", this);  //将按钮b4绑定到w上
        QPushButton *b5 = new QPushButton("EXIT", this);  //将按钮b5绑定到w上
        QTextEdit *t1 = new QTextEdit;

        t1->setGeometry(80, 30, 211, 111);
        t1->setAlignment(Qt::AlignCenter);
        t1->append("<font size=7>🐍</font><font color=black font size=7>ELCOME</font><font color=black font size=5> To</font> <br/> <font color=green font size=7>SNAKEGAME !</font>");

        // 父子对象设置  窗口在进行展示的时候，会将它的所有子对象一起显示
        b1->setParent(this);
        t1->setParent(this);

        b1->setGeometry(110, 180, 151, 51);     //将按钮b1移动到点（50，50）的位置
        b2->setGeometry(110, 250, 151, 51);
        b3->setGeometry(110, 320, 151, 51);   //既设置大小，又设置位置
        b4->setGeometry(110, 390, 151, 51);
        b5->setGeometry(110, 460, 151, 51);


        QObject::connect(b5, SIGNAL(clicked()), this, SLOT(close()));
        QObject::connect(b1, SIGNAL(clicked()), w, SLOT(on_pushButton_clicked()));
        QObject::connect(b2, SIGNAL(clicked()), w, SLOT(on_pushButton_2_clicked()));
        QObject::connect(b3, SIGNAL(clicked()), w, SLOT(on_pushButton_3_clicked()));
        QObject::connect(b4, SIGNAL(clicked()), w, SLOT(on_pushButton_4_clicked()));

}

Widget::~Widget()
{
}
