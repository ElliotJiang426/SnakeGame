#include <QApplication>
#include <QWidget>
#include <QPushButton>

#include "snake.h"
#include "autosnake.h"
#include "mainwindow.h"

mainwindow::mainwindow(QWindow *parent)
    : QWindow(parent)
    , m_backingStore(new QBackingStore(this))
{

}

void mainwindow::on_pushButton_clicked()
{
    snake = new Snakegame;
    snake->RasterWindow::show();
}

void mainwindow::on_pushButton_2_clicked()
{

    rules.resize(785, 598);

    text.setParent(&rules);
    text.setGeometry(50, 80, 681, 351);
    text.setText("<font size=6>贪吃蛇游戏规则</font><br/><font size=4>↑↓←→控制贪吃蛇前进方向<br/>黑色表示墙壁<br/>四周若无墙壁表示连通（例如右边界与左边界连通）<br/>当蛇吃到自己或者撞到墙壁时死亡<br/></font><br/><font size=6>果实与功能：</font><br/><font size=4>蓝色：增长1个单位<br/>红色：缩短3个单位（不少于1个单位）<br/>绿色：除去一堵墙（不少于最少数量）<br/><br/>按下Shift键可以失去30分来刷新当前果实<br/>按下Space键可以暂停，重按方向键可以继续<br/><br/>分数达到150的倍数时会触发黑夜与白天的切换</font><br/><br/><font size=6>多人游戏规则：</font><br/><font size=4>↑↓←→/WSAD/8546/UJHK<br/>分别对应不同玩家的蛇前进<br/>每条蛇只能吃与自己颜色相同的果实<br/>撞到其他蛇或者吃到自己的蛇将死亡<br/>其分数将转变成所有蛇均可吃的白色果实</font>");
    text.setAlignment(Qt::AlignCenter);

    bo.setParent(&rules);
    bo.setText("I GOT IT!");
    bo.setGeometry(330, 470, 93, 28);
    QObject::connect(&bo, SIGNAL(clicked()), &rules, SLOT(close()));

    rules.show();
}

void mainwindow::on_pushButton_3_clicked()
{
    new_win2 = new campaign;
}

void mainwindow::on_pushButton_4_clicked()
{
    AI = new autoSnake;
    AI->RasterWindow::show();
}



