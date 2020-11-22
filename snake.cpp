#include <QApplication>
#include <QtGui>
#include <cstdlib>
#include <ctime>
#include <list>
#include <algorithm>
#include <QtWidgets>
#include "rasterwindow.h"
#include <QGraphicsItem>
#include <QRectF>
#include <QMessageBox>
#include <QPushButton>
#include <QObject>

#include "snake.h"

void Snakegame::keyPressEvent(QKeyEvent *e)//按键控制蛇的走向，上下右左依次对应0123
{
    if(e->key() == Qt::Key_Up && (direction != 1 || length == 0)){
        direction = 0;
    }
    if(e->key() == Qt::Key_Down && (direction != 0 || length == 0)){
        direction = 1;
    }
    if(e->key() == Qt::Key_Right && (direction != 3 || length == 0)){
        direction = 2;
    }
    if(e->key() == Qt::Key_Left && (direction != 2 || length == 0)){
        direction = 3;
    }
    if(e->key() == Qt::Key_Shift){
        do{//随机出现果实的位置
            food.a = rand()%24*50;
            food.b = rand()%16*50;
        }while(snake.contains(QRect(food.a, food.b, 25, 25)) || foodhideinwall());
        food.kind = rand()%12;
        score -= 3;
    }//按下Shift可以重新刷新果实，但是会失去30分
    if(e->key() == Qt::Key_Space){
        direction = 4;;
    }
}

Snakegame::Snakegame()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setTitle("QSnake Game");
    RasterWindow::resize(1200, 800);//窗口大小

    x = 600;
    y = 400;//蛇的初始位置

    length = 0;//初始蛇长，0表示还没有吃果实
    score = 0;

    snake.append(QRect(x, y, 25, 25));

    n = rand()%3+3;

    for(int i=0; i<n; i++){
        do{
            Wall[i].Wx = rand()%24*50;
            Wall[i].Wy = rand()%16*50;
            Wall[i].len = rand()%10+10;
        }while(Wall[i].Wx==Wall[i-1].Wx || Wall[i].Wy==Wall[i-1].Wy || (Wall[i].Wx >= 1050 && Wall[i].Wy <= 100));
        Wall[i].bricks.append(QRect(Wall[i].Wx, Wall[i].Wy, 25, 25));

        for(int j=1; j<=Wall[i].len-1; j++){
            QRect NEW;
            int x=0, y=0;
            do{
                Wall[i].D = rand()%2;
                x = (Wall[i].bricks.at(j-1).x()+Wall[i].D*50)%1200;
                y = (Wall[i].bricks.at(j-1).y()+(Wall[i].D+1)%2*50)%800;
                NEW = QRect(x, y, 25, 25);
            }while(Wall[i].bricks.contains(QRect(600, 400, 25, 25)) || (x >= 1050 && y <= 100));
            Wall[i].bricks.append(NEW);
        }
    }
    //生成墙壁

    do{//随机出现果实的位置
        food.a = rand()%24*50;
        food.b = rand()%16*50;
    }while(snake.contains(QRect(food.a, food.b, 25, 25)) || foodhideinwall());
    food.kind = rand()%12;


    m_timerId = RasterWindow::startTimer(250);
}

void Snakegame::timerEvent(QTimerEvent *event)
{
    QApplication::processEvents();

    int p=snake[length].x(), q=snake[length].y();

    if(score % 20 >= 10 && shadowflag < 255)
        shadowflag += 51;
    if(score % 20 < 10 && shadowflag > 0)
        shadowflag -= 51;

    if (event->timerId() == m_timerId){

        switch (direction) {
        case 0: y = (y-50+800)%800; break;
        case 1: y = (y+50+800)%800; break;
        case 2: x = (x+50+1200)%1200; break;
        case 3: x = (x-50+1200)%1200; break;
        case 4: break;
        }//判断目前方向，前进

        if(direction != 4){
            QRect NEW = QRect(x, y, 25, 25);
            snake.append(NEW);
            snake.removeFirst();
        }

        if(x == food.a && y == food.b){

            switch(food.kind){
            case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: {
                QRect NEW = QRect(p, q, 25, 25);
                snake.push_front(NEW);
                length++;
                score++;
                break;
                } //如果吃到蓝色果实，增长
            case 10: {
                int i = 0;
                while(i<3 && length > 0){
                    snake.removeFirst();
                    i++;
                    length--;
                    }
                break;
                }//如果吃到红色果实，变短
            case 11: {
                if(n > 3){
                    Wall[n].bricks.clear();
                    n--;
                }
                score++;
                break;
                }//如果吃到绿色果实，去掉一面墙
            }
            do{
                food.a = rand()%24*50;
                food.b = rand()%16*50;
            }while(snake.contains(QRect(food.a, food.b, 25, 25)) || foodhideinwall());
            food.kind = rand()%12;
        }


    }

    handleCollisions();

    renderLater();
}

void Snakegame::render(QPainter *p)
{
    QApplication::processEvents();
    QPen pen;
    pen.setWidth(25);
    pen.setJoinStyle(Qt::RoundJoin);

    pen.setBrush(QColor(255,255,255));
    p->setPen(pen);
    p->drawRect(snake[length]);//画头

    pen.setBrush(Qt::blue);

    p->setPen(pen);

    for(int i = length-1; i >= 1; i--){
        QApplication::processEvents();
        int x = snake.at(i).x();
        int y = snake.at(i).y();
        int x1 = snake.at(i+1).x();
        int y1 = snake.at(i+1).y();
        int x2 = snake.at(i-1).x();
        int y2 = snake.at(i-1).y();
            if(((x==x1 && y==y1-50) && (x==x2+50 && y==y2)) || ((x==x2 && y==y2-50)&&(x==x1+50 && y==y1))){
                p->drawPie(snake.at(i).x()-25, snake.at(i).y(), 50, 50, 0, 90*16);
                continue;
            }
            if(((x==x1 && y==y1-50) && (x==x2-50 && y==y2)) || ((x==x2 && y==y2-50)&&(x==x1-50 && y==y1))){
                p->drawPie(snake.at(i).x(), snake.at(i).y(), 50, 50, 90*16, 90*16);
                continue;
            }
            if(((x==x1 && y==y1+50) && (x==x2+50 && y==y2)) || ((x==x2 && y==y2+50)&&(x==x1+50 && y==y1))){
                p->drawPie(snake.at(i).x()-25, snake.at(i).y()-25, 50, 50, -90*16, 90*16);
                continue;
            }
            if(((x==x1 && y==y1+50) && (x==x2-50 && y==y2)) || ((x==x2 && y==y2+50)&&(x==x1-50 && y==y1))){
                p->drawPie(snake.at(i).x(), snake.at(i).y()-25, 50, 50, -180*16, 90*16);
                continue;
            }
        p->drawRect(snake.at(i));
    }//画身体
    if(length > 0) p->drawRect(snake.at(0));

    switch(food.kind){
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        pen.setBrush(Qt::blue); break;
    case 10: pen.setBrush(Qt::red); break;
    case 11: pen.setBrush(Qt::green); break;
    }

    p->setPen(pen);
    p->drawEllipse(food.a, food.b, 25, 25);//画食物

    pen.setBrush(Qt::black);
    p->setPen(pen);
    for(int i=0; i<n; i++){
        for(int j=0; j<=Wall[i].bricks.size()-1; j++){
            p->drawRect(Wall[i].bricks.at(j));
        }
    }
    p->setPen(Qt::black);
    p->setFont(QFont("Arial",14));
    p->drawText(1050,50,"Score: "+QString::number(score*10));

    if(shadowflag != 0){
        p->save();
        p->setPen(Qt::transparent);
        p->setBrush(QColor(0, 0, 0, shadowflag));

        QPainterPath bigRect;
        bigRect.addRect(0, 0, 1200, 800);

        QPainterPath smallCircle1;
        smallCircle1.addEllipse(snake.at(length).x()-100, snake.at(length).y()-100, 250, 250);
        QPainterPath smallCircle2;
        smallCircle2.addEllipse(food.a-100, food.b-100, 250, 250);

        QPainterPath path = bigRect - smallCircle1 - smallCircle2 - (smallCircle1 & smallCircle2);
        p->drawPath(path);

        p->restore();

        p->setPen(Qt::white);
        p->setFont(QFont("Arial",14));
        p->drawText(1050,50,"Score: "+QString::number(score*10));
    }
    return;
}

void Snakegame::gameover()//判断游戏结束
{
    RasterWindow::killTimer(m_timerId);
    QMessageBox::information(this,"failed","game over!");
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Game Over!", "Do you want to restart?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
        this->restart();
        return;
    }
    else{
        this->RasterWindow::close();
    }
}

void Snakegame::handleCollisions()//处理碰撞
{
    for(int i=length-3; i>=0; i--){
        if(snake[i].x()==snake[length].x() && snake[i].y()==snake[length].y()){
            gameover();
            return;
        }//蛇吃到自己
    }

    for(int i=0; i<n; i++){
        if(Wall[i].bricks.contains(snake[length]) && Wall[i].bricks.contains(snake[length])){
            gameover();
            return;
        }
    }//蛇撞到墙

    return;
}

bool Snakegame::foodhideinwall(){
    for(int i=0; i<n; i++){
        if(Wall[i].bricks.contains(QRect(food.a, food.b, 25, 25)))
            return true;
    }
    return false;
}//判断食物是否被墙壁遮挡

void Snakegame::restart(){
    x = 600;
    y = 400;//蛇的初始位置

    length = 0;
    score = 0;//初始蛇长，0表示还没有吃果实

    snake.clear();
    snake.append(QRect(x, y, 25, 25));

    for(int i=0; i<n; i++){
        Wall[i].bricks.clear();
    }

    n = rand()%3+3;

    for(int i=0; i<n; i++){
        do{
            Wall[i].Wx = rand()%24*50;
            Wall[i].Wy = rand()%16*50;
            Wall[i].len = rand()%10+10;
        }while(Wall[i].Wx==Wall[i-1].Wx || Wall[i].Wy==Wall[i-1].Wy || (Wall[i].Wx >= 1050 && Wall[i].Wy <= 100));
        Wall[i].bricks.append(QRect(Wall[i].Wx, Wall[i].Wy, 25, 25));

        for(int j=1; j<=Wall[i].len-1; j++){
            QRect NEW;
            int x=0, y=0;
            do{
                Wall[i].D = rand()%2;
                x = (Wall[i].bricks.at(j-1).x()+Wall[i].D*50)%1200;
                y = (Wall[i].bricks.at(j-1).y()+(Wall[i].D+1)%2*50)%800;
                NEW = QRect(x, y, 25, 25);
            }while(Wall[i].bricks.contains(QRect(600, 400, 25, 25)) || (x >= 1050 && y <= 100));
            Wall[i].bricks.append(NEW);
        }
    }

    do{//随机出现果实的位置
        food.a = rand()%24*50;
        food.b = rand()%16*50;
    }while(snake.contains(QRect(food.a, food.b, 25, 25)) || foodhideinwall());
    food.kind = rand()%12;

    direction = 4;
    m_timerId = RasterWindow::startTimer(250);

    return;
}//死亡后重新开始或退出

