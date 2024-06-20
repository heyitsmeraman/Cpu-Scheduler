#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include"sub_window.h"

extern int condition;
extern int time_slice;
extern int num;
extern int ch;
bool t=false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->QLineEdit_Process_Num->setPlaceholderText("input number...");

}

MainWindow::~MainWindow()
{
    delete ui;
}
int condition = 0;
int time_slice =0;

void MainWindow::on_pushButton_Input_clicked()
{
    QString text=ui->QLineEdit_Process_Num->text();
    num=text.toInt();
    if(ui->radioButton_Sub_FCFS->isChecked())
    {
        ch=1;
        condition+=1;
    }
    else if(ui->radioButton_Sub_NSJF->isChecked())
    {
        ch=2;
        condition+=1;
    }
    else if(ui->radioButton_Sub_PSJF->isChecked())
    {
        ch=3;
        condition+=1;
    }
    else if(ui->radioButton_Sub_RR->isChecked())
    {
        ch=4;
        condition+=1;
        bool ok;
        time_slice = QInputDialog::getInt(nullptr, "Enter Time Slice", "Please enter the time slice:", 1, 1, 100, 1, &ok);

        // If the user clicks OK, the value will be stored in 'timeSlice'
        if (ok) {
            // Display the entered time slice
            QMessageBox::information(nullptr, "Saved", "Enter process information " );
            t=false;
        } else {
            // User clicked Cancel or closed the dialog
            QMessageBox::information(nullptr, "Cancelled", "Operation cancelled. No time slice entered.");
            t=true;
        }
    }
    else if(ui->radioButton_Sub_PR->isChecked())
    {
        ch=5;
        condition+=1;
    }

    else if(ui->radioButton_Sub_PR_2->isChecked())
    {
        ch=6;
        condition+=1;
    }

    else
    {
        QMessageBox::warning(this,"Warning","Please select an algorithm!");
    }

    if(num==0)
    {
        QMessageBox::warning(this,"Waring","You input a wrong number!");
    }


    if (num !=0 && condition !=0 && !t )//didnt handle time slice isnt entered
    {
        sub_window sub_window;
        sub_window.setModal(true);
        sub_window.exec();
    }
}


