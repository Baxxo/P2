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
  QPushButton *chooseSala;
  QPushButton *choosePosti;
  QPushButton *chooseFilm;

  QPushButton *adminBtn;
  QPushButton *clientBtn;

  QLabel *pathUser;
  QLabel *pathFamilies;
  QLabel *pathEntrata;
  QLabel *pathPosti;
  QLabel *pathSala;
  QLabel *pathFilm;

  Controller *controller;

  bool isVisReadBtn;

  void setStyle();
  void changeMenu();
  void setSlot();

  void createLayoutAdCl();
  void hideLayoutAdCLl();
  void showLayoutAdCLl();

  void createLayoutSetup();
  void hideLayoutSetup();

  void showPath(bool hide = false);

  void closeEvent(QCloseEvent *event);

 private slots:

  void changeMenuSlot();
  void resizeMe();

 public:
  MainWindow(QWidget *parent = nullptr);

  MainWindow *getMainwindow();

  void setController(Controller *c);

  void changeTitleChooseUtenti(const QString &s);
  void changeTitleChooseFamiglie(const QString &s);
  void changeTitleChooseEntrata(const QString &s);
  void changeTitleChoosePosti(const QString &s);
  void changeTitleChooseFilm(const QString &s);
  void changeTitleChooseSala(const QString &s);
  void changeTitleAdmin(const QString &s);
  void changeTitleClient(const QString &s);

  void setLabelPathUser(const QString &s);
  void setLabelPathFamiglie(const QString &s);
  void setLabelPathEntrata(const QString &s);
  void setLabelPathPosti(const QString &s);
  void setLabelPathSale(const QString &s);
  void setLabelPathFilm(const QString &s);

  void showLayoutSetup();
};
#endif  // MAINWINDOW_H
