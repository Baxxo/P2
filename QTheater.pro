#-------------------------------------------------
#
# Project created by QtCreator 2021-04-22T22:25:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTheater
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Abbonamento.cpp \
    AbbonamentoFamigliare.cpp \
    Biglietto.cpp \
    Data.cpp \
    EntrataFilm.cpp \
    Famiglia.cpp \
    main.cpp \
    mainwindow.cpp \
    MyVector.cpp \
    regola.cpp \
    regolaarancione.cpp \
    regolabianca.cpp \
    regolagialla.cpp \
    regolarossa.cpp \
    Sala.cpp \
    Singolo.cpp \
    Utente.cpp

HEADERS += \
        mainwindow.h \
    Abbonamento.h \
    AbbonamentoFamigliare.h \
    Biglietto.h \
    Data.h \
    EntrataFilm.h \
    Famiglia.h \
    MyVector.h \
    regola.h \
    regolaarancione.h \
    regolabianca.h \
    regolagialla.h \
    Sala.h \
    Singolo.h \
    Utente.h

FORMS +=

SUBDIRS += \
    QTheater.pro

DISTFILES +=

RESOURCES +=
