#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snake.h"
#include "campaign.h"
#include "autosnake.h"
#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QPushButton>

class mainwindow : public QWindow
{
    Q_OBJECT

public:
    explicit mainwindow(QWindow *parent = 0);
    ~mainwindow(){}
    Snakegame *snake;
    campaign *new_win2;
    autoSnake *AI;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


private:

    QBackingStore *m_backingStore;
    QWidget rules;
    QTextEdit text;
    QPushButton bo;

};

#endif // MAINWINDOW_H
