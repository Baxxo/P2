#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
     mainLayout = new QHBoxLayout(this);
     label = new QLabel("Ciao Joseph !!! <3");
     mainLayout->addWidget(label);
     label->setStyleSheet("QLabel {border: 1px solid gray;border-radius: 2px;background-color: red;padding: 0px 5px 10px 15px;}");
     label->setMargin(5);
}

MainWindow::~MainWindow(){}
