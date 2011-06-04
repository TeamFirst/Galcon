QT       += core
QT       += gui network

TARGET = Galcon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



SOURCES += main.cpp \
    Game/Space.cpp \
    Game/Player.cpp \
    Game/Planet.cpp \
    Game/Game.cpp \
    Game/Fleet.cpp \
    GUI/Waitwindow.cpp \
    GUI/Playwindow.cpp \
    GUI/Guiview.cpp \
    GUI/Guispace.cpp \
    GUI/Guiplanet.cpp \
    GUI/Guifleet.cpp \
    GUI/gui.cpp \
    GUI/enterwindow.cpp \
    GUI/criticalmessage.cpp \
    serverManager/ServerManager.cpp \
    serverManager/Parser.cpp \    
    Galcon.cpp \
    SingleGame/SingleGameManager.cpp \
    SingleGame/MapGame.cpp


HEADERS += \
    Game/Space.h \
    Game/Player.h \
    Game/Planet.h \
    Game/Game.h \
    Game/Fleet.h \
    GUI/WaitWindow.h \
    GUI/Playwindow.h \
    GUI/Guiview.h \
    GUI/Guispace.h \
    GUI/Guiplanet.h \
    GUI/Guifleet.h \
    GUI/gui.h \
    GUI/enterwindow.h \
    GUI/criticalmessage.h \
    message/MessageTimeToStartGame.h \
    message/MessageStepPlayer.h \
    message/MessageStateMap.h \
    message/MessageStartMapGame.h \
    message/MessageItf.h \
    message/MessageInformation.h \
    message/MessageFinishGame.h \
    message/MessageError.h \
    message/MessageConnectToServer.h \
    message/MessageAddView.h \
    serverManager/ServerManager.h \
    serverManager/Parser.h \
    SceneUpdates.h \
    Galcon.h \
    SingleGame/SingleGameManager.h \
    SingleGame/MapGame.h \
    SingleGame/GameMapObject.h \
    SingleGame/GameMapObject.h \
    SingleGame/MapGame.h \
    SingleGame/SingleGameManager.h


FORMS += \
    GUI/waitwindow.ui \
    GUI/playwindow.ui \
    GUI/enterwindow.ui


RESOURCES += \
    resource.qrc \
    space.qrc

OTHER_FILES += \
    GUI/sky.png
