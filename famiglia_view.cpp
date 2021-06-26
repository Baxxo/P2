#include "famiglia_view.h"
#include "controller.h"
#include <QTimer>

Famiglia_View::Famiglia_View(Controller *c, QWidget *parent)
    : QWidget(parent),
      familyName(new QLineEditClickable("Type in a family name")),
      listaUtenti(new QListWidget),
      searchEditText(new QLineEditClickable("Type in a CF and press search")),
      menuLayout(new QVBoxLayout), btnLayout(new QVBoxLayout),
      searchBtn(new QPushButton("Search")),
      saveFamily(new QPushButton("Salva Famiglia")),
      mainlayout(new QGridLayout), widget(new QWidget(this)),
      layoutListUsers(new QVBoxLayout),
      labelListaUtenti(new QLabel(
          "\nUtenti presenti nel sistema\n\n clicca una volra per "
          "aggiungere un utente\n\n clicca di nuovo per rimuoverlo")),
      utility(new QLabel()), controller(c) {

  widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  labelListaUtenti->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  saveFamily->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  searchBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  setWindowTitle(QString("Creazione famiglia"));

  menuLayout->addWidget(familyName, Qt::AlignCenter);
  menuLayout->addWidget(labelListaUtenti, Qt::AlignCenter);
  menuLayout->addWidget(listaUtenti, Qt::AlignCenter);
  menuLayout->addWidget(searchEditText, Qt::AlignCenter);
  btnLayout->addWidget(searchBtn, Qt::AlignCenter);
  btnLayout->addWidget(utility, Qt::AlignCenter);
  btnLayout->addWidget(saveFamily, Qt::AlignCenter);
  mainlayout->addLayout(menuLayout, 0, 0, Qt::AlignCenter);
  mainlayout->addLayout(btnLayout, 1, 0, Qt::AlignCenter);

  widget->setLayout(mainlayout);

  setMinimumSize(320, 450);

  setStyle();

  connect(searchBtn, SIGNAL(clicked()), controller, SLOT(searchCF()));
  connect(saveFamily, SIGNAL(clicked()), controller, SLOT(salvaFamiglia()));
  connect(familyName, SIGNAL(clicked()), this, SLOT(cleanTextFamily()));
  connect(searchEditText, SIGNAL(clicked()), this, SLOT(cleanTextSearch()));
  connect(listaUtenti, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(addUtenteToFamiglia(QListWidgetItem *)));
}

void Famiglia_View::addUtenteToLista(const QString &text, const QString &cf) {
  QListWidgetItem *itemN = new QListWidgetItem();
  QLabelCF *widgetText = new QLabelCF(new QLabel(text), cf);

  listaUtenti->addItem(itemN);
  itemN->setSelected(false);
  listaUtenti->setItemWidget(itemN, widgetText);
}

void Famiglia_View::setStyle() {
  QFile style(":/qss/style.css");
  style.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(style.readAll());

  setStyleSheet(styleSheet);
}

QString Famiglia_View::getItem(int i) { return listaUtenti->item(i)->text(); }

QString Famiglia_View::getSearch() { return searchEditText->text(); }

int Famiglia_View::getListSize() { return listaUtenti->count(); }

QString Famiglia_View::getFamilyName() { return familyName->text(); }

QString Famiglia_View::getCF_SearchText() const {
  return searchEditText->text();
}

void Famiglia_View::clearList() { listaUtenti->clear(); }

void Famiglia_View::selectIndexbyCF(QString cf) { qDebug() << cf; }

void Famiglia_View::findUser(QString search) {
  bool find = false;
  for (int i = 0; i < listaUtenti->count() && !find; ++i) {
    QListWidgetItem *item = listaUtenti->item(i);
    QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));
    if (lbl->getCf() == search && !lbl->isSelected()) {
      if (controller->addUserToFamily(lbl->getCf())) {
        lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
        lbl->setSelect(true);

        listaUtenti->setItemWidget(item, lbl);
        setUtilityText(QString("Utente aggiunto"));
        find = true;
      }
    }
  }
}

void Famiglia_View::setUtilityText(QString txt) {
  utility->setText(txt);
  QTimer::singleShot(1500, this, SLOT(cleanUtilityText()));
}

void Famiglia_View::signaltest() { qDebug() << "signal"; }

void Famiglia_View::resizeMe() { adjustSize(); }

void Famiglia_View::cleanUtilityText() { utility->setText(""); }

void Famiglia_View::cleanTextFamily() {
  if (familyName->text() == "Type in a family name")
    familyName->setText("");
}

void Famiglia_View::cleanTextSearch() {
  if (searchEditText->text() == "Type in a CF and press search")
    searchEditText->setText("");
}

void Famiglia_View::addUtenteToFamiglia(QListWidgetItem *item) {

  QLabelCF *lbl = dynamic_cast<QLabelCF *>(listaUtenti->itemWidget(item));

  if (!lbl->isSelected()) {

    if (controller->addUserToFamily(lbl->getCf())) {
      lbl->setStyleSheet("QLabel { background-color : LightGreen;}");
      lbl->setSelect(true);

      listaUtenti->setItemWidget(item, lbl);
      setUtilityText(QString("Utente aggiunto"));
    }

  } else {

    if (controller->removeUserFromFamily(lbl->getCf())) {

      lbl->setStyleSheet("QLabel { background-color : #00A2E8;}");
      lbl->setSelect(false);

      listaUtenti->setItemWidget(item, lbl);
      setUtilityText(QString("Utente rimosso"));
    }
  }

  // manca da cercare utente nel vector
}
