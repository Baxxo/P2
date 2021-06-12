#include "admin.h"

Admin::Admin(Controller *c, MainWindow *parent)
    : p(parent), controller(c), i(0) {

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

  baseLayout->addWidget(labelAbb, 0, 0, Qt::AlignCenter);
  baseLayout->addWidget(labelUt, 0, 1, Qt::AlignCenter);
  baseLayout->addWidget(labelFam, 0, 2, Qt::AlignCenter);

  baseLayout->addWidget(listAbb, 1, 0);
  baseLayout->addWidget(listUt, 1, 1);
  baseLayout->addWidget(listFam, 1, 2);

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

void Admin::getClickAbb() {
  qDebug() << "Abbonamento " << listAbb->currentItem()->text();
}

void Admin::getClickFam() {
  qDebug() << "Famiglia " << listFam->currentItem()->text();
}

void Admin::closeEvent(QCloseEvent *event) {
  p->setIsAdmin(false);
  event->accept();
}

void Admin::getClickUt() {
  qDebug() << "Utente " << listUt->currentItem()->text();
}
