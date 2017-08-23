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

INCLUDEPATH +="F:\Dev\Includes\qdiscord"

LIBS += "F:\Dev\Libs\qdiscord\libQDiscord.a"

include(commands/commands.pri)
