#include "biglietto_view.h"
#include "controller.h"

Biglietto_View::Biglietto_View(Controller *c, QWidget *parent) : controller(c), QWidget(parent)
{
    tipologia=new QComboBox;
    compraBiglietto= new QPushButton("Compra");
    tipologiaBtn=new QPushButton("OK");
    compraLayout=new QVBoxLayout;
    layoutTipologia=new QVBoxLayout;
    mainLayout=new QGridLayout;
    mainWidget=new QWidget(this);
    widgetSing=new QWidget();
    listaFilm=new QListWidget;
    utenteBigl=new QVBoxLayout;
    search= new QLineEdit;
    searchBtn= new QPushButton("ok");
    salaWidget=new QWidget();
    salaLayout=new QVBoxLayout;
    selectSeat=new QPushButton("scegli un posto");
    posti= new QTableWidget(2, 3);


    compraLayout->addWidget(listaFilm, Qt::AlignTop);
    compraLayout->addWidget(compraBiglietto, Qt::AlignBottom);
    compraLayout->addWidget(selectSeat, Qt::AlignRight);
    layoutTipologia->addWidget(tipologia, Qt::AlignCenter);
    layoutTipologia->addWidget(tipologiaBtn, Qt::AlignCenter);
    salaLayout->addWidget(posti);


    mainLayout->addLayout(layoutTipologia, 0, 0, Qt::AlignCenter);
    mainLayout->addLayout(compraLayout, 1, 1, Qt::AlignCenter);

    utenteBigl->addWidget(search, Qt::AlignCenter);
    utenteBigl->addWidget(searchBtn, Qt::AlignCenter);

    mainWidget->setLayout(mainLayout);
    mainWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    widgetSing->setLayout(utenteBigl);


    salaWidget->setLayout(salaLayout);
    salaWidget->hide();

    tipologia->insertItem(0, "Singolo");
    tipologia->insertItem(1, "Abbonamento");

    connect(tipologiaBtn, SIGNAL(clicked()), this, SLOT(showSearch()));
    connect(searchBtn, SIGNAL(clicked()), controller, SLOT(stpBigl()));
    connect(selectSeat, SIGNAL(clicked()), controller, SLOT(showSala()));

    setStyle();

}

void Biglietto_View::setStyle()
{
    QFile file(":/qss/style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    setStyleSheet(styleSheet);
}

QString Biglietto_View::getSearch()
{
    return search->text();
}

QString Biglietto_View::getTipologia()
{
    return tipologia->currentText();
}

void Biglietto_View::getSalaView()
{

    salaWidget->show();

}

void Biglietto_View::showSearch()
{
    widgetSing->show();

}
