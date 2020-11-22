#include "autosnake.h"
#include "snake.h"
#include "rasterwindow.h"

autoSnake::autoSnake()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setTitle("QSnake Game");
    RasterWindow::resize(1200, 800);//窗口大小

    x = 600;
    y = 400;//蛇的初始位置

    length = 0;//初始蛇长，0表示还没有吃果实

    snake.append(QRect(x, y, 25, 25));

    do{//随机出现果实的位置
        food.a = rand()%24*50;
        food.b = rand()%16*50;
    }while(snake.contains(QRect(food.a, food.b, 25, 25)));

    m_timerId = RasterWindow::startTimer(200);
}

void autoSnake::timerEvent(QTimerEvent *event)
{
    int p=snake[length].x(), q=snake[length].y();

    if (event->timerId() == m_timerId){

        direction = nextStep(snake[length].x(),snake[length].y(),food.a,food.b);
        switch (direction) {
        case 0: y = y-50; break;
        case 1: y = y+50; break;
        case 2: x = x+50; break;
        case 3: x = x-50; break;
        case 4: break;
        }//判断目前方向，前进

        QRect NEW = QRect(x, y, 25, 25);
        snake.append(NEW);
        snake.removeFirst();

        if(x == food.a && y == food.b){
                QRect NEW = QRect(p, q, 25, 25);
                snake.push_front(NEW);
                length++;
            do{
                food.a = rand()%24*50;
                food.b = rand()%16*50;
            }while(snake.contains(QRect(food.a, food.b, 25, 25)));
        }
    }

    handleCollisions();

    renderLater();
}

int autoSnake::nextStep(int hx, int hy, int fx, int fy)
{
    int nextdir = 4;
    int mindis = 9999;

    distance[0]=abs(fx-hx)+abs(fy-(hy-50));
    for(int i=length-1; i>=0; i--){
        if((snake[i].x()==hx && snake[i].y()==(hy-50)) || (hy-50)<0){
            distance[0] = 9999;
        }//蛇吃到自己
    }

    distance[1]=abs(fx-hx)+abs(fy-(hy+50));
    for(int i=length-1; i>=0; i--){
        if((snake[i].x()==hx && snake[i].y()==(hy+50)) || (hy+50)>800){
            distance[1] = 9999;
        }//蛇吃到自己
    }

    distance[2]=abs(fx-(hx+50))+abs(fy-hy);
    for(int i=length-1; i>=0; i--){
        if((snake[i].x()==(hx+50) && snake[i].y()==hy) || (hx+50)>1200){
            distance[2] = 9999;
        }//蛇吃到自己
    }

    distance[3]=abs(fx-(hx-50))+abs(fy-hy);
    for(int i=length-1; i>=0; i--){
        if((snake[i].x()==(hx-50) && snake[i].y()==hy) || (hx-50)<0){
            distance[3] = 9999;
        }//蛇吃到自己
    }

    for(int i=0; i<4; i++){
        if(distance[i]<mindis){
            mindis = distance[i];
            nextdir = i;
        }
    }
    return nextdir;
}

void autoSnake::gameover()//判断游戏结束
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

void autoSnake::handleCollisions()//处理碰撞
{
    for(int i=length-3; i>=0; i--){
        if(snake[i].x()==snake[length].x() && snake[i].y()==snake[length].y()){
            gameover();
            return;
        }//蛇吃到自己
    }
    return;
}

void autoSnake::restart(){
    x = 600;
    y = 400;//蛇的初始位置

    length = 0;

    snake.clear();
    snake.append(QRect(x, y, 25, 25));

    do{//随机出现果实的位置
        food.a = rand()%24*50;
        food.b = rand()%16*50;
    }while(snake.contains(QRect(food.a, food.b, 25, 25)));

    direction = 4;
    m_timerId = RasterWindow::startTimer(200);

    return;
}

void autoSnake::render(QPainter *p)
{

    QPen pen;
    pen.setWidth(25);
    pen.setJoinStyle(Qt::RoundJoin);

    pen.setBrush(QColor(255,255,255));
    p->setPen(pen);
    p->drawRect(snake[length]);//画头

    pen.setBrush(Qt::blue);


    p->setPen(pen);

    for(int i = length-1; i >= 0; i--){
        p->drawRect(snake.at(i));
    }//画身体

    pen.setBrush(Qt::blue);

    p->setPen(pen);
    p->drawEllipse(food.a, food.b, 25, 25);//画食物

    return;
}
