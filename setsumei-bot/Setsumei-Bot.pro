QT += core network websockets
QT -= gui

CONFIG += c++11

TARGET = setsumeibot
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    utils.cpp \
    command.cpp \
    interpreter.cpp \
    commandmanager.cpp \
    config.cpp \
    setsumei.cpp

HEADERS += \
    utils.hpp \
    command.hpp \
    interpreter.hpp \
    commandmanager.hpp \
    config.hpp \
    setsumei.hpp

LIBS += "/usr/lib/libQDiscord.a"

INCLUDEPATH += "/usr/include"

include(commands/commands.pri)
