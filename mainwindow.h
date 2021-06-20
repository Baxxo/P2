#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class Controller;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

  MainWindow *getMainwindow();

  void setController(Controller *c);

  void changeTitleChooseUtenti(QString s);
  void changeTitleChooseFamiglie(QString s);
  void changeTitleChooseEntrata(QString s);
  void changeTitleAdmin(QString s);

  void setLabelPathUser(QString s);
  void setLabelPathFamiglie(QString s);
  void setLabelPathEntrata(QString s);
  void setLabelPathPosti(QString s);
  void setLabelPathFilm(QString s);

  void createLayoutSetup();
  void destroyLayoutSetup();

  void setPrevAdmin(const QString &value);

 private slots:

  void changeMenuSlot();
  void resizeMe();

 private:
  QDesktopWidget *desktop;

  QWidget *widget;

  QGridLayout *mainLayout;
  QVBoxLayout *v_layout;
  QGridLayout *buttonLayout;

  QLabel *title;

  QPushButton *changeBtn;

  QPushButton *chooseUtenti;
  QPushButton *chooseFamiglie;
  QPushButton *chooseEntrata;
  QPushButton *choosePosti;
  QPushButton *chooseFilm;

  QPushButton *adminBtn;
  QPushButton *clientBtn;

  QLabel *pathUser;
  QLabel *pathFamilies;
  QLabel *pathEntrata;
  QLabel *pathPosti;
  QLabel *pathFilm;

  Controller *controller;

  void setStyle();
  void changeMenu();
  void setSlot();

  bool isVisReadBtn;

  //  bool isVisFam;
  //  bool isVisEntrata;
  //  bool isVisPosti;
  //  bool isVisFilm;

  void createLayoutAdCl();
  void destroyLayoutAdCl();

  QString prevAdmin;
  QString prevChooseUtenti;
  QString prevChooseFamiglie;
  QString prevChooseEntrata;
};
#endif  // MAINWINDOW_H
