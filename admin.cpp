#include "admin.h"
#include "controller.h"

Admin::Admin(Controller *c, MainWindow *parent)
    : p(parent), controller(c){
  baseLayout = new QGridLayout();
  mainLayout = new QVBoxLayout();

  setWindowTitle(QString("Admin"));

  QFont font;
  font.setPointSize(50);
  font.setBold(true);

  admin = new QLabel("Admin");
  admin->setFont(font);
  admin->setProperty("class", "title");

  mainLayout->addWidget(admin, 0, Qt::AlignCenter);
  mainLayout->addLayout(baseLayout);

  widget = new QWidget();
  widget->setLayout(mainLayout);

  desktop = QApplication::desktop();
  font.setPointSize(15);

  labelAbb = new QLabel("Abbonamenti");
  labelAbb->setFont(font);
  labelAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  listAbb = new QListWidget();
  listAbb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelFilm = new QLabel("Film");
  labelFilm->setFont(font);
  labelFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  listFilm = new QListWidget();
  listFilm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  addFilm= new QPushButton("add Film");

  labelSala = new QLabel("Sala");
  labelSala->setFont(font);
  labelSala->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  listSala = new QListWidget();
  listSala->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  addSala= new QPushButton("add Sala");

  labelFam = new QLabel("Famiglie");
  labelFam->setFont(font);
  labelFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  listFam = new QListWidget();
  listFam->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  labelUt = new QLabel("Utenti");
  labelUt->setFont(font);
  labelUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  listUt = new QListWidget();
  listUt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  connect(listAbb, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickAbb()));
  connect(listFam, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickFam()));
  connect(listUt, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(getClickUt()));
  connect(addFilm, SIGNAL(clicked()), this, SLOT(addFilmLayout()));
  connect(addSala, SIGNAL(clicked()), this, SLOT(addSalaLayout()));


  baseLayout->addWidget(labelAbb, 0, 0, Qt::AlignCenter);
  baseLayout->addWidget(labelUt, 0, 1, Qt::AlignCenter);
  baseLayout->addWidget(labelFam, 0, 2, Qt::AlignCenter);
  baseLayout->addWidget(labelFilm, 0, 3, Qt::AlignCenter);
  baseLayout->addWidget(labelSala, 0, 4, Qt::AlignCenter);


  baseLayout->addWidget(listAbb, 1, 0);
  baseLayout->addWidget(listUt, 1, 1);
  baseLayout->addWidget(listFam, 1, 2);
  baseLayout->addWidget(listFilm, 1, 3);
  baseLayout->addWidget(listSala, 1, 4);


  baseLayout->addWidget(addFilm, 2, 3);
  baseLayout->addWidget(addSala, 2, 4);


  resize(1000, 400);

  setCentralWidget(widget);


}

void Admin::addUtente(QString s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listUt->addItem(item);
}

void Admin::addFamiglia(QString s) {
  QListWidgetItem *item = new QListWidgetItem(s);
  listFam->addItem(item);
}

void Admin::clearListUtenti() { listUt->clear(); }

void Admin::clearListFamiglie() { listFam->clear(); }

QString Admin::getNomeFilm(){ return nomeFilm->text(); }

QString Admin::getColonneSala(){ return colonneSala->text(); }

QString Admin::getRigheSala(){ return righeSala->text(); }

QString Admin::getNomeSala(){ return nomeSala->text(); }

QString Admin::getSalaFilm(){ return salaFilm->text(); }

void Admin::getClickAbb(){ qDebug() << "Abbonamento " << listAbb->currentItem()->text(); }

void Admin::getClickFam(){ qDebug() << "Famiglia " << listFam->currentItem()->text(); }

void Admin::getClickFilm(){ qDebug() << "film " << listFilm->currentItem()->text(); }

void Admin::addFilmLayout()
{
    widgetFilm= new QWidget();
    filmLayout= new QGridLayout;
    nomeFilm= new QLineEdit;
    salaFilm= new QLineEdit;
    saveFilm= new QPushButton("Salva");

    filmLayout->addWidget(nomeFilm, 0, 0);
    filmLayout->addWidget(salaFilm, 1, 0);
    filmLayout->addWidget(saveFilm, 2, 0);

    widgetFilm->setLayout(filmLayout);
    widgetFilm->show();

    connect(saveFilm, SIGNAL(clicked()), controller, SLOT(newFilm()));
}

void Admin::addSalaLayout()
{
    widgetSala= new QWidget();
    salaLayout= new QGridLayout;
    nomeSala= new QLineEdit;
    righeSala= new QLineEdit;
    colonneSala= new QLineEdit;
    saveSala= new QPushButton("Salva");

    salaLayout->addWidget(nomeSala, 0, 0);
    salaLayout->addWidget(righeSala, 1, 0);
    salaLayout->addWidget(colonneSala, 2, 0);
    salaLayout->addWidget(saveSala, 3, 0);

    nomeSala->setText("nome Sala");
    righeSala->setText("numero righe");
    colonneSala->setText("numero colonne");

    widgetSala->setLayout(salaLayout);
    widgetSala->show();

    connect(saveSala, SIGNAL(clicked()), controller, SLOT(newSala()));
}

void Admin::closeEvent(QCloseEvent *event) {
  p->changeTitleAdmin("Admin");
  event->accept();
}

void Admin::getClickUt() {
  qDebug() << "Utente " << listUt->currentItem()->text();
}
