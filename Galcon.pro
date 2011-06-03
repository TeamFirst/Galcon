QT       += core
QT       += gui network

TARGET = Galcon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



SOURCES += main.cpp \
    GUI/Waitwindow.cpp \
#    GUI/PlayWindow.cpp \
#    GUI/PlayArea.cpp \
#    GUI/GUIView.cpp \
#    GUI/GUIPlanet.cpp \
#    GUI/GUIFleet.cpp \
    GUI/gui.cpp \
    GUI/enterwindow.cpp \
    GUI/criticalmessage.cpp \
    serverManager/ServerManager.cpp \
    serverManager/Parser.cpp \
    Galcon.cpp \
#    GUI/GUISky.cpp \
    Game/Fleet.cpp \
    Game/Game.cpp \
    Game/Planet.cpp \
    Game/Player.cpp \
    Game/Space.cpp \
    GUI/Guifleet.cpp \
    GUI/Guiplanet.cpp \
    GUI/Guispace.cpp \
    GUI/Guiview.cpp \
    GUI/Playwindow.cpp

HEADERS += Galcon.h \
    GUI/WaitWindow.h \
#    GUI/PlayWindow.h \
#    GUI/PlayArea.h \
#    GUI/GUIView.h \
#    GUI/GUIPlanet.h \
#    GUI/GUIFleet.h \
    GUI/gui.h \
    GUI/enterwindow.h \
    GUI/criticalmessage.h \
    SceneUpdates.h \
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
    message/MessageTimeToStartGame.h \
#    GUI/GUISky.h \
    Game/Fleet.h \
    Game/Game.h \
    Game/Planet.h \
    Game/Player.h \
    Game/Space.h \

    GUI/Guifleet.h \
    GUI/Guiplanet.h \
    GUI/Guispace.h \
    GUI/Guiview.h \
    GUI/Playwindow.h

    message/MessageInformation.h


FORMS += \
    GUI/waitwindow.ui \
#    GUI/playwindow.ui \
    GUI/enterwindow.ui


RESOURCES += \
    resource.qrc

OTHER_FILES += \
    GUI/sky.png
