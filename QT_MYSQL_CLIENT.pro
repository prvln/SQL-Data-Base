QT       += core
QT       += gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataBase
TEMPLATE = app

DEFINES += PATH=\\\"F:/QT_MYSQL_CLIENT/DataBase.db\\\"

SOURCES += main.cpp\
    database.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    database.h

FORMS    += mainwindow.ui
