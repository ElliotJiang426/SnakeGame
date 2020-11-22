#include "multiplesnake.h"
#include "snake.h"

void multipleSnake::keyPressEvent(QKeyEvent *e)//按键控制蛇的走向，上下右左依次对应0123
{
    if(e->key() == Qt::Key_Up && (direction[0] != 1 || length[0] == 0)){
        direction[0] = 0;
    }
    if(e->key() == Qt::Key_Down && (direction[0] != 0 || length[0] == 0)){
        direction[0] = 1;
    }
    if(e->key() == Qt::Key_Right && (direction[0] != 3 || length[0] == 0)){
        direction[0] = 2;
    }
    if(e->key() == Qt::Key_Left && (direction[0] != 2 || length[0] == 0)){
        direction[0] = 3;
    }//上下左右对应玩家一的操作

    if(e->key() == Qt::Key_W && (direction[1] != 1 || length[1] == 0)){
        direction[1] = 0;
    }
    if(e->key() == Qt::Key_S && (direction[1] != 0 || length[1] == 0)){
        direction[1] = 1;
    }
    if(e->key() == Qt::Key_D && (direction[1] != 3 || length[1] == 0)){
        direction[1] = 2;
    }
    if(e->key() == Qt::Key_A && (direction[1] != 2 || length[1] == 0)){
        direction[1] = 3;
    }//WASD对应玩家二的操作

    if(e->key() == Qt::Key_8 && (direction[2] != 1 || length[2] == 0)){
        direction[2] = 0;
    }
    if(e->key() == Qt::Key_5 && (direction[2] != 0 || length[2] == 0)){
        direction[2] = 1;
    }
    if(e->key() == Qt::Key_6 && (direction[2] != 3 || length[2] == 0)){
        direction[2] = 2;
    }
    if(e->key() == Qt::Key_4 && (direction[2] != 2 || length[2] == 0)){
        direction[2] = 3;
    }//8546对应玩家三的操作

    if(e->key() == Qt::Key_U && (direction[3] != 1 || length[3] == 0)){
        direction[3] = 0;
    }
    if(e->key() == Qt::Key_J && (direction[3] != 0 || length[3] == 0)){
        direction[3] = 1;
    }
    if(e->key() == Qt::Key_K && (direction[3] != 3 || length[3] == 0)){
        direction[3] = 2;
    }
    if(e->key() == Qt::Key_H && (direction[3] != 2 || length[3] == 0)){
        direction[3] = 3;
    }//UJHK对应玩家四的操作
}

multipleSnake::multipleSnake(int n)
{
    setAttribute(Qt::WA_DeleteOnClose);

    numOfPlayer = n;

    setTitle("QSnake Game");
    RasterWindow::resize(1200, 800);//窗口大小

    for(int i=0; i<numOfPlayer; i++){
        x[i] = rand()%24*50;
        y[i] = rand()%16*50; //随机出现蛇头位置
        length[i] = 0;     //初始蛇长，0表示还没有吃果实
        score[i] = 0;
        snake[i].append(QRect(x[i], y[i], 25, 25));

        do{//随机出现果实的位置
            food[i].a = rand()%24*50;
            food[i].b = rand()%16*50;
        }while(snake[i].contains(QRect(food[i].a, food[i].b, 25, 25)));
        food[i].kind = i;
    }//蛇的初始位置

    numofExtraFood = 0;

    deadPlayer = 0;

    m_timerId = RasterWindow::startTimer(300);
}

void multipleSnake::timerEvent(QTimerEvent *event)
{


    if (event->timerId() == m_timerId){

        for(int i=0; i<numOfPlayer; i++){

        if(length[i] == -1) continue;

        int p=snake[i].at(length[i]).x(), q=snake[i].at(length[i]).y();

        switch (direction[i]) {
        case 0: y[i] = (y[i]-50+800)%800; break;
        case 1: y[i] = (y[i]+50+800)%800; break;
        case 2: x[i] = (x[i]+50+1200)%1200; break;
        case 3: x[i] = (x[i]-50+1200)%1200; break;
        case 4: break;
        }//判断目前方向，前进

        QRect NEW = QRect(x[i], y[i], 25, 25);
        snake[i].append(NEW);
        snake[i].removeFirst();

        if(x[i] == food[i].a && y[i] == food[i].b){

                QRect NEW = QRect(p, q, 25, 25);
                snake[i].push_front(NEW);
                length[i]++;
                score[i]++;

            do{
                food[i].a = rand()%24*50;
                food[i].b = rand()%16*50;
            }while(snake[i].contains(QRect(food[i].a, food[i].b, 25, 25)));
        }//吃到果实则增加长度

        for(int j=0; j<numofExtraFood; j++){
            if(extrafood[j].kind == 0) continue;
            if(x[i] == extrafood[j].a && y[i] == extrafood[j].b){
                QRect NEW = QRect(p, q, 25, 25);
                snake[i].push_front(NEW);
                length[i]++;
                score[i]++;
                extrafood[j].kind = 0;
            }
        }//一条蛇死后会产生奖励果实
        }

    }
    handleCollisions();

    renderLater();
}

void multipleSnake::handleCollisions()//处理碰撞
{
    for(int j=0; j<numOfPlayer; j++){
        if(length[j] == -1) continue;
        for(int i=length[j]-3; i>=0; i--){
            if(snake[j].at(i).x()==snake[j].at(length[j]).x() && snake[j].at(i).y()==snake[j].at(length[j]).y()){
                gameover(j);
                break;
            }//蛇吃到自己
        }
    }
    for(int j=0; j<numOfPlayer; j++){
        if(length[j] == -1) continue;
        for(int k=0; k<numOfPlayer; k++){
            if(length[k] == -1) continue;
            if(j != k && snake[k].at(length[k]).contains(snake[j].at(length[j]))){
                gameover(k);
                gameover(j);
                break;
            }
            if(j != k && snake[k].contains(snake[j].at(length[j]))){
                gameover(j);
                break;
            }
        }
    }//蛇撞到其他蛇
    return;
}

void multipleSnake::gameover(int n)//判断游戏结束
{
    deadPlayer ++;
    if(deadPlayer == numOfPlayer){
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

    snake[n].clear();
    numofExtraFood += length[n];
    length[n] = -1;
    for(int i=0; i<numofExtraFood; i++){
        extrafood[i].a = rand()%24*50;
        extrafood[i].b = rand()%16*50;
        extrafood[i].kind = 1;
    }
    return;
}

void multipleSnake::restart(){
    for(int i=0; i<numOfPlayer; i++){
        direction[i] = 4;
        x[i] = rand()%24*50;
        y[i] = rand()%16*50; //随机出现蛇头位置
        length[i] = 0;     //初始蛇长，0表示还没有吃果实
        score[i] = 0;
        snake[i].append(QRect(x[i], y[i], 25, 25));

        do{//随机出现果实的位置
            food[i].a = rand()%24*50;
            food[i].b = rand()%16*50;
        }while(snake[i].contains(QRect(food[i].a, food[i].b, 25, 25)));
        food[i].kind = i;
    }//蛇的初始位置

    numofExtraFood = 0;

    deadPlayer = 0;

    m_timerId = RasterWindow::startTimer(350);
}//死亡后重新开始或退出

void multipleSnake::render(QPainter *p)
{

    QPen pen;
    pen.setWidth(25);
    pen.setJoinStyle(Qt::RoundJoin);
    p->setPen(pen);
    for(int i=0; i<numOfPlayer; i++){
        if(length[i] == -1) continue;

        switch(i){
        case 0: pen.setBrush(QColor(0,0,203)); break;
        case 1: pen.setBrush(QColor(181,14,31)); break;
        case 2: pen.setBrush(QColor(24,235,35)); break;
        case 3: pen.setBrush(QColor(255,204,0)); break;
        }//画头
        p->setPen(pen);

        p->drawRect(snake[i].at(length[i]));


        switch(i){
        case 0: pen.setBrush(Qt::blue); break;
        case 1: pen.setBrush(Qt::red); break;
        case 2: pen.setBrush(Qt::green); break;
        case 3: pen.setBrush(Qt::yellow); break;
        }
        p->setPen(pen);

        for(int j = length[i]-1; j >= 0; j--){
            p->drawRect(snake[i].at(j));
        }//画身体

        p->drawEllipse(food[i].a, food[i].b, 25, 25);//画食物

        p->setPen(Qt::black);
        p->setFont(QFont("Arial",14));
        p->drawText(1050,50+50*i,"Score: "+QString::number(score[i]*10));
    }

    pen.setBrush(Qt::white);
    p->setPen(pen);
    for(int i=0; i<numofExtraFood; i++){
        if(extrafood[i].kind == 0) {
            p->drawEllipse(extrafood[i].a, extrafood[i].b, 0, 0);
            continue;
        }
        p->drawEllipse(extrafood[i].a, extrafood[i].b, 25, 25);
    }
    return;
}
