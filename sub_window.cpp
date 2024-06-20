#include "sub_window.h"
#include "ui_sub_window.h"
#include"mainwindow.h"
#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include<windows.h>
#include <QElapsedTimer>
#include<QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include<QLineEdit>
#include "priorityq.h"
extern int condition;
extern int time_slice;
extern int ch;
extern int num;
bool live;
extern process p[100],p1[100],temp;
extern queue<int>q1;

sub_window::sub_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sub_window)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QStringList header;
    if(ch==5 || ch==6){
    header<<"ID"<<"Arrival Time"<<"Burst Time"<<"Priority"<<"Color";
    ui->tableWidget->setRowCount(num);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
   // ui->lineEdit_timeslice->setPlaceholderText("Input time slice...");
    }
    else if (ch == 4){
        header<<"ID"<<"Arrival Time"<<"Burst Time"<<"Color";
        ui->tableWidget->setRowCount(num);
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
       // ui->lineEdit_timeslice->setPlaceholderText("Input time slice...");
    }
    else{

        header<<"ID"<<"Arrival Time"<<"Burst Time"<<"Color";
        ui->tableWidget->setRowCount(num);
        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels(header);
        ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
        ui->tableWidget->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
        //ui->lineEdit_timeslice->setPlaceholderText("Input time slice...");
    }
}
void sub_window::shortest_job_sort(int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        for (j = 1; j <= i; j++)
        {
            if (p[j].at > p[i].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
            else if (p[j].at == p[i].at)
            {
                if (p[j].bt > p[i].bt)
                {
                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void sub_window::updateBurstTimeInTable() {
    for (int i = 0; i < ui->tableWidget_Result_3->rowCount(); i++) {
        QTableWidgetItem* item = ui->tableWidget_Result_3->item(i, 1); // Get existing item
        item = new QTableWidgetItem(); // Create new item if it doesn't exist
        int burstTime = p[i+1].rt;
        if (burstTime < 0) {
            burstTime = 0; // Ensure burst time is non-negative
        }
        QString temp_string = QString::number(burstTime); // Convert to string
        item->setText(temp_string);
        ui->tableWidget_Result_3->setItem(i, 0, item); // Set item in the table
    }
}

void sub_window::displayturnwait(int n)
{
    int i;
    p[0].tat = 0;
    p[0].wt = 0;
    for(i=1;i<=ui->tableWidget->rowCount();i++)
    {
        p[i].tat=p[i].ft-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[0].tat=p[0].tat+p[i].tat;
        p[0].wt=p[0].wt+p[i].wt;
    }

    p[0].tat=p[0].tat/n;
    p[0].wt=p[0].wt/n;
    AvgTurn(p[0].tat);
    AvgWait(p[0].wt);

    QStringList header;
    header<<"ID"<<"Turnaround Time"<<"Waiting Time";
    ui->tableWidget_Result->setRowCount(ui->tableWidget->rowCount());
    ui->tableWidget_Result->setColumnCount(3);
    ui->tableWidget_Result->setHorizontalHeaderLabels(header);
    ui->tableWidget_Result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result->verticalHeader()->setStyleSheet("QHeaderView::section{background:green;}");
    ui->tableWidget_Result->horizontalHeader()->resizeSection(2,150);

    for (i=0 ; i<=ui->tableWidget_Result->rowCount() ; i++ )
    {

        QTableWidgetItem* item = new QTableWidgetItem();
        QString temp_string=QString::number(p[i+1].id);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,0,item);

        item = new QTableWidgetItem();
        temp_string=QString::number(p[i+1].tat);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,1,item);

        item = new QTableWidgetItem();
        temp_string=QString::number(p[i+1].wt);
        item->setText(temp_string);
        ui->tableWidget_Result->setItem(i,2,item);
    }
}

void sub_window::AvgTurn(double value)
{
    QString textValue = QString::number(value);
    ui->AvgTurn->setText(textValue);
}
void sub_window::AvgWait(double value)
{
    QString textValue = QString::number(value);
    ui->AvgWait->setText(textValue);
}

sub_window::~sub_window()
{
    delete ui;
}

void sub_window::on_pushButton_clicked()
{
    int temp_data[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    QString tableData[ui->tableWidget->rowCount()][ui->tableWidget->columnCount()];

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount();j++)
        {
            tableData[i][j]=ui->tableWidget->item(i,j)->text();
        }
    }

    // ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<ui->tableWidget->columnCount()-1;j++)
        {
            temp_data[i][j]=tableData[i][j].toInt();
        }
    }

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i+1].id=temp_data[i][0];
        p[i+1].at=temp_data[i][1];
        p[i+1].bt=temp_data[i][2];
        if(ch==5 || ch==6){
        p[i+1].pr=temp_data[i][3];
        p[i+1].color=tableData[i][4];
        }
        else
            p[i+1].color=tableData[i][3];
        p[i+1].rt=p[i+1].bt; //Initialize remaining burst time
    }

 condition+=1;

}

void sub_window::addRowToTable()
{
    // Get the current row count
    int rowCount = ui->tableWidget->rowCount();

    // Insert a new row at the end
    ui->tableWidget->insertRow(rowCount);

    // Example: Read data from the new row and populate the p array
    QTableWidgetItem *idItem = ui->tableWidget->item(rowCount, 0);
    QTableWidgetItem *atItem = ui->tableWidget->item(rowCount, 1);
    QTableWidgetItem *btItem = ui->tableWidget->item(rowCount, 2);

    QTableWidgetItem *prItem = ui->tableWidget->item(rowCount, 3);
    QTableWidgetItem *colorItem = ui->tableWidget->item(rowCount, 4);

    // Example: Add data to the p array (you can modify this according to your requirements)
    if (idItem && atItem && btItem && prItem && colorItem) {
        p[rowCount + 1].id = idItem->text().toInt();
        p[rowCount + 1].at = atItem->text().toInt();
        p[rowCount + 1].bt = btItem->text().toInt();
        if(ch==5 || ch==6)
        p[rowCount + 1].pr = prItem->text().toInt();
        p[rowCount + 1].color = colorItem->text();
        p[rowCount + 1].rt = p[rowCount + 1].bt;    //Remaining time equals burst time at initialization
    }
}

void sub_window::on_Add_Process_clicked()
{
    // Call the function to add a row to the table
    addRowToTable();
}


void sub_window::on_pushButton_2_clicked()
{
    QStringList head;
    head << "Burst Time";
    ui->tableWidget_Result_3->setRowCount(ui->tableWidget->rowCount());
    ui->tableWidget_Result_3->setColumnCount(1); // Assuming 2 columns: Process ID and Burst Time
    ui->tableWidget_Result_3->setHorizontalHeaderLabels(head);
    ui->tableWidget_Result_3->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget_Result_3->horizontalHeader()->resizeSection(2, 150);

    // Update burst time values in the table
    updateBurstTimeInTable();

    if(ui->live_button->isChecked()){
        live=true;
    }

    if(condition>=2){
        if(ch==1) //FCFS
        {
            int nextval = 0;
            int i;
            //Sort array according to arrival time
            shortest_job_sort(ui->tableWidget->rowCount());

            for(i=1;i<=ui->tableWidget->rowCount();i++)
            {
                while(p[i].at>nextval){
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                    while (t.elapsed() < 1000) {
                        QCoreApplication::processEvents();
                    }
                    else
                        QCoreApplication::processEvents();

                    nextval++;
                }
                while(p[i].rt--){
                    // Draw a rectangle representing execution of the process
                    updateBurstTimeInTable();
                    QBrush color_brush(QColor(p[i].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    nextval++;
                    if(p[i].rt==0){
                        p[i].ft=nextval;
                    }
                }
            }
            updateBurstTimeInTable();
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        if(ch==2) //NP SJF
        {   // Initialize variables
            int total_Burst_Time = 0, nextval = 0, min_burst, m;
            // Execute SJF scheduling algorithm
            for (int i = 1; i <= ui->tableWidget->rowCount(); i++) {
                total_Burst_Time += p[i].bt;    // Update total burst time
            }
            // Simulate SJF scheduling
            while (nextval < total_Burst_Time) {
                min_burst = INT_MAX;    // Initialize minimum burst time to maximum integer value
                m = -1;                 // Initialize index of chosen process to -1
                // Find the process with the shortest remaining burst time
                for (int j = 1; j <= ui->tableWidget->rowCount(); ++j) {
                    if (p[j].at <= nextval && p[j].rt > 0) {
                        if (p[j].rt < min_burst) {
                            min_burst = p[j].rt;
                            m = j;
                        }
                    }
                }
                // If a process is found to execute, schedule it
                if (m != -1) {
                    while(p[m].rt--){
                        updateBurstTimeInTable();
                        // Draw a rectangle representing execution of the process
                        QBrush color_brush(QColor(p[m].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                                   0,
                                                   Rectangle_Width * 1,
                                                   Rectangle_Height,
                                                   blackpen,
                                                   color_brush);
                        // Display the current time value on top of the rectangle
                        QString temp_str = QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                        scene->addItem(txtitem);

                        // Wait for approximately 1 seconds for visualization
                        QElapsedTimer t;
                        t.start();
                        if(live)
                            while (t.elapsed() < 1000) {
                                QCoreApplication::processEvents();
                            }
                        else
                            QCoreApplication::processEvents();
                        nextval++;
                    }
                    p[m].ft = nextval;
                } else {
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    nextval++;
                    total_Burst_Time++;
                }
            }
            updateBurstTimeInTable();
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        if(ch==3) //P SJF
        {
            // Initialize variables
            int nextval = 0, min_burst, m;
            int total_Burst_Time = 0; //Must be global if inserting dynamic proccess***************
            // Execute SJF scheduling algorithm
            for (int i = 1; i <= ui->tableWidget->rowCount(); i++) {
                total_Burst_Time += p[i].bt;         // Update total burst time
            }
            // Simulate SJF scheduling
            while (nextval < total_Burst_Time) {
                min_burst = INT_MAX;     // Initialize minimum burst time to maximum integer value
                m = -1;         // Initialize index of chosen process to -1

                // Find the process with the shortest remaining burst time
                for (int j = 1; j <= ui->tableWidget->rowCount(); ++j) {
                    if (p[j].at <= nextval && p[j].rt > 0) {
                        if (p[j].rt < min_burst) {
                            min_burst = p[j].rt;
                            m = j;
                        }
                    }
                }
                // If a process is found to execute, schedule it
                if (m != -1) {
                    p[m].rt--;  // Decrement burst time of the chosen process
                    updateBurstTimeInTable(); // Update burst time values in the table
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor(p[m].color));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);

                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    if(p[m].rt == 0){
                        p[m].ft = (nextval+1);
                    }
                }
                else{
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    total_Burst_Time++;
                }
                nextval++;            // Increment current time
            }
            updateBurstTimeInTable(); // Update burst time values in the table
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        if(ch==4) //RR
        {
            extern queue<int>q1;
            int nextval=0;
            int count = ui->tableWidget->rowCount();
            shortest_job_sort(ui->tableWidget->rowCount());
            //copy array to p1
            for(int i=1;i<=ui->tableWidget->rowCount();i++)
            {
                p1[i]=p[i];
            }
            while(!q1.empty() || count > 0){
                // Insert processes into the queue if their arrival time is less than or equal to the current time
                for (int i = 1; i <= count; i++) {
                    if (p1[i].at <= nextval) {
                        q1.push(p1[i].id);
                        for (int j = i; j <= count - 1; j++) {
                            p1[j] = p1[j + 1];
                        }
                        count--;
                        i--;
                    }
                }
                if (q1.empty()) {
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    nextval++;
                }
                else{
                    int m = q1.front();
                    q1.pop();
                    int ind;
                    for(int i=1; i <= ui->tableWidget->rowCount();i++)
                    {
                        if(p[i].id == m){
                            ind=i;
                            break;
                        }
                    }
                    if(p[ind].rt > time_slice){
                        p[ind].rt -= time_slice;
                        // Wait for approximately the time slice seconds seconds for visualization
                        QElapsedTimer t;
                        t.start();
                        if(live)
                        while (t.elapsed() < 1000 * time_slice) {
                            QCoreApplication::processEvents();
                        }
                        else
                            QCoreApplication::processEvents();

                        // Draw a rectangle representing execution of the process
                        QBrush color_brush(QColor(p[ind].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                                   0,
                                                   Rectangle_Width * time_slice,
                                                   Rectangle_Height,
                                                   blackpen,
                                                   color_brush);
                        // Display the current time value on top of the rectangle
                        QString temp_str = QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                        scene->addItem(txtitem);

                        nextval=nextval+time_slice;
                        q1.push(m);
                    }
                    else{
                        // Wait for approximately the remaining burst time seconds for visualization
                        QElapsedTimer t;
                        t.start();
                        if(live)
                        while (t.elapsed() < 1000 * p[ind].rt) {
                            QCoreApplication::processEvents();
                        }
                        else
                            QCoreApplication::processEvents();

                        // Draw a rectangle representing execution of the process
                        QBrush color_brush(QColor(p[ind].color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                                   0,
                                                   Rectangle_Width * p[ind].rt,
                                                   Rectangle_Height,
                                                   blackpen,
                                                   color_brush);
                        // Display the current time value on top of the rectangle
                        QString temp_str = QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                        scene->addItem(txtitem);

                        nextval += p[ind].rt;
                        p[ind].ft =nextval;
                        p[ind].rt = 0;
                    }
                    updateBurstTimeInTable(); // Update burst time values in the table
                }
            }
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        if(ch==5) //NP priority
        {
            int nextval = 0;
            int count = ui->tableWidget->rowCount();
            //copy contents of array to p1
            for(int i=1;i<= ui->tableWidget->rowCount();i++)
            {
                p1[i]=p[i];
            }
            PriorityQueue Q;
            while (!Q.isEmpty() || count > 0) {
                // Insert processes into the queue if their arrival time is less than or equal to the current time
                for (int i = 1; i <= count; i++) {
                    if (p1[i].at <= nextval) {
                        Q.insert(p1[i]);
                        for (int j = i; j <= count - 1; ++j) {
                            p1[j] = p1[j + 1];
                        }
                        count--;
                        i--;
                    }
                }
                if (Q.isEmpty()) {
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                    while (t.elapsed() < 1000) {
                        QCoreApplication::processEvents();
                    }
                    else
                        QCoreApplication::processEvents();

                    nextval++;
                } else {
                    process P = Q.extractMin();
                    int ind;
                    for(int i=1;i<= ui->tableWidget->rowCount();i++)
                    {
                        if(p[i].id==P.id){
                            ind=i;
                            break;
                        }
                    }
                    while(P.rt--){
                        p[ind].rt--;
                        updateBurstTimeInTable();
                        // Draw a rectangle representing execution of the process
                        QBrush color_brush(QColor(P.color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                                   0,
                                                   Rectangle_Width * 1,
                                                   Rectangle_Height,
                                                   blackpen,
                                                   color_brush);
                        // Display the current time value on top of the rectangle
                        QString temp_str = QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                        scene->addItem(txtitem);
                        // Wait for approximately 1 seconds for visualization
                        QElapsedTimer t;
                        t.start();
                        if(live)
                            while (t.elapsed() < 1000) {
                                QCoreApplication::processEvents();
                            }
                        else
                            QCoreApplication::processEvents();
                        nextval++;
                    }
                    p[ind].ft=nextval;
                }
            }
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
        if(ch==6) //P priority
        {
            int nextval = 0;
            int count = ui->tableWidget->rowCount();
            //copy contents of array to p1
            for(int i=1;i<= ui->tableWidget->rowCount();i++)
            {
                p1[i]=p[i];
            }
            PriorityQueue Q;
            while (!Q.isEmpty() || count > 0) {
                // Insert processes into the queue if their arrival time is less than or equal to the current time
                for (int i = 1; i <= count; i++) {
                    if (p1[i].at <= nextval) {
                        Q.insert(p1[i]);
                        for (int j = i; j <= count - 1; j++) {
                            p1[j] = p1[j + 1];
                        }
                        count--;
                        i--;
                    }
                }
                if (Q.isEmpty()) {
                    // Draw a rectangle representing execution of the process
                    QBrush color_brush(QColor("transparent"));
                    QPen blackpen(Qt::black);
                    blackpen.setWidth(1);
                    rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                               0,
                                               Rectangle_Width * 1,
                                               Rectangle_Height,
                                               blackpen,
                                               color_brush);
                    // Display the current time value on top of the rectangle
                    QString temp_str = QString::number(nextval);
                    QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                    txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                    scene->addItem(txtitem);
                    // Wait for approximately 1 seconds for visualization
                    QElapsedTimer t;
                    t.start();
                    if(live)
                        while (t.elapsed() < 1000) {
                            QCoreApplication::processEvents();
                        }
                    else
                        QCoreApplication::processEvents();
                    nextval++;
                }
                else{
                    process P = Q.extractMin();
                    int ind;
                    for(int i=1;i<= ui->tableWidget->rowCount();i++)
                    {
                        if(p[i].id==P.id){
                            ind=i;
                            break;
                        }
                    }
                    if(P.rt>0){
                        // Draw a rectangle representing execution of the process
                        QBrush color_brush(QColor(P.color));
                        QPen blackpen(Qt::black);
                        blackpen.setWidth(1);
                        rectangle = scene->addRect(-200 + (Rectangle_Width * nextval),
                                                   0,
                                                   Rectangle_Width * 1,
                                                   Rectangle_Height,
                                                   blackpen,
                                                   color_brush);
                        // Display the current time value on top of the rectangle
                        QString temp_str = QString::number(nextval);
                        QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
                        txtitem->setPos(QPointF((-200 + Rectangle_Width * nextval), 100));
                        scene->addItem(txtitem);
                        P.rt--;
                        p[ind].rt--;
                        updateBurstTimeInTable();
                        Q.insert(P);
                        nextval++;

                        // Wait for approximately 1 seconds for visualization
                        QElapsedTimer t;
                        t.start();
                        if(live)
                            while (t.elapsed() < 1000) {
                                QCoreApplication::processEvents();
                            }
                        else
                            QCoreApplication::processEvents();
                    }
                    else{
                        p[ind].ft = nextval;
                    }
                }
            }
            // Display the final time value
            QString temp_str = QString::number(nextval);
            QGraphicsTextItem *txtitem = new QGraphicsTextItem(temp_str);
            txtitem->setPos(QPointF(-200 + Rectangle_Width * nextval, 100));
            scene->addItem(txtitem);

            // Update condition variable and perform additional operations
            condition = 0;
            displayturnwait(ui->tableWidget->rowCount());
            QMessageBox::information(this, "Succeed", "Simulation Completed!");
        }
    }
    else
    {
        QMessageBox::warning(this,"Warning","Check your data!");
    }
}

void sub_window::on_pushButton_4_clicked()
{
    scene->clear();
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        p[i].at=0;
        p[i].bt=0;
        p[i].color="";
        p[i].ft=0;
        p[i].id=0;
        p[i].pr=0;
        p[i].st=0;
        p[i].tat=0;
        p[i].wt=0;
        p[i].rt=0;
    }
    AvgTurn(p[0].tat);
    AvgWait(p[0].wt);
    live=false;
}
