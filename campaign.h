#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include <QWindow>
#include <multiplesnake.h>
#include <QApplication>
#include <QWidget>
#include <QPushButton>

class campaign : public QWindow
{
    Q_OBJECT

public:
    explicit campaign(QWindow *parent = nullptr);
    ~campaign(){}
    multipleSnake *m;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    QBackingStore *m_backingStore;
    QWidget w;
    QPushButton b1;
    QPushButton b2;
    QPushButton b3;
    QPushButton b4;
};

#endif // CAMPAIGN_H
