# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = ./
TARGET = hra2016cli
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += src/GUI/qboard.cpp src/GUI/qfield.cpp src/hra2016.cpp src/hra2016cli.cpp src/logic/board.cpp src/logic/field.cpp src/logic/game.cpp src/logic/player.cpp
HEADERS += src/GUI/qboard.h src/GUI/qfield.h src/hra2016.h src/hra2016cli.h src/logic/board.h src/logic/field.h src/logic/game.h src/logic/player.h src/logic/types.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
