#ifndef SUB_WINDOW_H
#define SUB_WINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include<QGraphicsScene>
#include "priorityQ.h"

const int Rectangle_Width=20;
const int Rectangle_Height=100;

namespace Ui {
class sub_window;
}

class sub_window : public QDialog
{
    Q_OBJECT

public:
    explicit sub_window(QWidget *parent = 0);
    void shortest_job_sort(int n);
    void displayturnwait(int n);
    ~sub_window();
    void AvgTurn(double value);
    void AvgWait(double value);
    void addRowToTable();

    void updateBurstTimeInTable();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();
    void on_Add_Process_clicked();

private:
    Ui::sub_window *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QGraphicsRectItem *rectangle;

};

#endif // SUB_WINDOW_H
