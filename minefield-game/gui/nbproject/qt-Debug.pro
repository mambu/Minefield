# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = gui
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += ../src/Minefield.cpp main.cpp src/AboutDialog.cpp src/MainWindow.cpp src/NewDialog.cpp
HEADERS += ../include/Minefield.h ../include/Table.h include/AboutDialog.h include/MainWindow.h include/NewDialog.h
FORMS += res/AboutDialog.ui res/MainWindow.ui res/NewDialog.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += include src ../../minefield-game/include 
LIBS += 
