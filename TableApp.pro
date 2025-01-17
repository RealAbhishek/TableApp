QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LargeTableAccessibilityApp
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           largetablemodel.cpp \

HEADERS += mainwindow.h \
           largetablemodel.h
