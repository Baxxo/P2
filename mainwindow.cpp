#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  mainLayout = new QGridLayout();
  v_layout = new QVBoxLayout();

  title = new QLabel();
  title->setText("QTheater");
  title->move(width()/2,height()/2);

  v_layout->addWidget(title,Qt::AlignCenter);

  mainLayout->addLayout(v_layout,0,0,Qt::AlignCenter);

  widget = new QWidget(this);
  widget->setLayout(mainLayout);

  setCentralWidget(widget);

  desktop = QApplication::desktop();

  resize(450,450);
  move((desktop->width()-450)/2,(desktop->height()-450)/2);

  setStyle();

}

MainWindow::~MainWindow()
{
}

void MainWindow::setStyle()
{
  QFile file(":/qss/style.css");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());

  setStyleSheet(styleSheet);
}
