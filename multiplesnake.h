#ifndef MUTIPLESNAKE_H
#define MUTIPLESNAKE_H

#include "snake.h"

class multipleSnake: public Snakegame
{
public:
    multipleSnake(int n=1);

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
    void keyPressEvent(QKeyEvent *e) override;
    void gameover(int n);
    void handleCollisions();
    bool foodhideinwall();
    void restart();

private:
    int numOfPlayer;
    int m_timerId;
    int score[4];

    QList<QRect> snake[4];

    int length[4];//蛇长
    int x[4];//蛇头横坐标
    int y[4];//蛇头纵坐标

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
    Food food[4];

    Food extrafood[50];
    int numofExtraFood;

    int deadPlayer;//死亡玩家数

    int direction[4]={4, 4, 4, 4};//方向标记物

};

#endif // MUTIPLESNAKE_H
