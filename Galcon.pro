#-------------------------------------------------
#
# Project created by QtCreator 2011-06-01T17:48:04
#
#-------------------------------------------------

QT       += core

QT       += gui network

TARGET = Galcon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    GUI/Waitwindow.cpp \
    GUI/PlayWindow.cpp \
    GUI/PlayArea.cpp \
    GUI/GUIView.cpp \
    GUI/GUIPlanet.cpp \
    GUI/GUIFleet.cpp \
    GUI/gui.cpp \
    GUI/enterwindow.cpp \
    GUI/criticalmessage.cpp \
    Space.cpp \
    Player.cpp \
    Planet.cpp \
    Game.cpp \
    Fleet.cpp \
    serverManager/ServerManager.cpp \
    serverManager/Parser.cpp \
    Galcon.cpp \
    main.cpp

HEADERS += \
    Galcon.h \
    GUI/WaitWindow.h \
    GUI/PlayWindow.h \
    GUI/PlayArea.h \
    GUI/GUIView.h \
    GUI/GUIPlanet.h \
    GUI/GUIFleet.h \
    GUI/gui.h \
    GUI/enterwindow.h \
    GUI/criticalmessage.h \
    Space.h \
    SceneUpdates.h \
    Player.h \
    Planet.h \
    Game.h \
    Fleet.h \
    serverManager/ServerManager.h \
    serverManager/Parser.h \
    message/MessageAddView.h \
    message/MessageConnectToServer.h \
    message/MessageError.h \
    message/MessageFinishGame.h \
    message/MessageItf.h \
    message/MessageStartMapGame.h \
    message/MessageStateMap.h \
    message/MessageStepPlayer.h \
    message/MessageTimeToStartGame.h

FORMS += \
    GUI/waitwindow.ui \
    GUI/playwindow.ui \
    GUI/enterwindow.ui
