#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include<cstdlib>
#include<queue>
#include<cstdio>
using namespace std;

typedef struct process
{
    int id;
    int at; // Arrival time
    int bt; // Burst time
    int pr; // Priority
    int st; // Start time
    int ft; // Finish time
    int rt; // Remaining time

    double wt;  // Waiting time
    double tat; // Turnaround time

    QString color;
}process;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Input_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
