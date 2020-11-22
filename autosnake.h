#ifndef AUTOSNAKE_H
#define AUTOSNAKE_H

#include "snake.h"
#include "rasterwindow.h"

class autoSnake: public RasterWindow, public QWidget
{
public:
    autoSnake();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
    void gameover();
    void handleCollisions();
    void restart();
    int nextStep(int hx, int hy, int fx, int fy);


private:
    int m_timerId;
    int distance[4]={0,0,0,0};//记录蛇头周围四个方向到食物的距离
    int direction = 4;

    QList<QRect> snake;

    int length;//蛇长
    int x;//蛇头横坐标
    int y;//蛇头纵坐标

    struct Food{
        int a;//果实横坐标
        int b;//果实纵坐标
        int kind;//果实种类

        Food(int x=0, int y=0, int k=1){
            a = x;
            b = y;
            kind = k;
        }
    };
    Food food;
};

#endif // AUTOSNAKE_H
