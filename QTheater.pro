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
    controller.cpp \
    famiglia_view.cpp \
    main.cpp \
    regola.cpp \
    regolaarancione.cpp \
    regolabianca.cpp \
    regolagialla.cpp \
    regolarossa.cpp \
    mainwindow.cpp \
    admin.cpp \
    client.cpp \
    abbonamento.cpp \
    abbonamentoFamigliare.cpp \
    biglietto.cpp \
    data.cpp \
    entrataFilm.cpp \
    famiglia.cpp \
    sala.cpp \
    singolo.cpp \
    utente.cpp \
    utente_View.cpp \
    model.cpp \
    errordisplay.cpp \
    qlineeditclickable.cpp \
    qlabelcf.cpp

HEADERS += \
    controller.h \
    famiglia_view.h \
    regola.h \
    regolaarancione.h \
    regolabianca.h \
    regolagialla.h \
    mainwindow.h \
    admin.h \
    client.h \
    abbonamento.h \
    abbonamentoFamigliare.h \
    biglietto.h \
    data.h \
    entrataFilm.h \
    famiglia.h \
    myVector.h \
    sala.h \
    singolo.h \
    utente.h \
    utente_View.h \
    model.h \
    deepPtr.h \
    errordisplay.h \
    qlineeditclickable.h \
    qlabelcf.h

FORMS +=

SUBDIRS += \
    QTheater.pro

DISTFILES +=

RESOURCES += \
    styleresources.qrc
