QT       += core
QT       += gui network

TARGET = Galcon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app



SOURCES += main.cpp \
    Game/Space.cpp \
    Game/Planet.cpp \
    Game/Game.cpp \
    Game/Fleet.cpp \
    GUI/Waitwindow.cpp \
    GUI/Playwindow.cpp \
    GUI/Guiview.cpp \
    GUI/Guispace.cpp \
    GUI/Guiplanet.cpp \
    GUI/Guifleet.cpp \
    serverManager/ServerManager.cpp \
    serverManager/Parser.cpp \    
    Galcon.cpp \
    SingleGame/SingleGameManager.cpp \
    SingleGame/MapGame.cpp \
    GUI/Enterwindow.cpp \
    GUI/Gui.cpp \
    GUI/Errorwindow.cpp \
    SingleGame/Bot.cpp \
    Player.cpp


HEADERS += \
    Game/Space.h \
    Game/Planet.h \
    Game/Game.h \
    Game/Fleet.h \
    GUI/Playwindow.h \
    GUI/Guiview.h \
    GUI/Guispace.h \
    GUI/Guiplanet.h \
    GUI/Guifleet.h \
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
    GUI/Gui.h \
    GUI/Enterwindow.h \
    GUI/Errorwindow.h \
    GUI/Waitwindow.h \
    GUI/SceneUpdates.h \
    SingleGame/Bot.h \
    SingleGame/Bot.h \
    Player.h


FORMS += \
    GUI/waitwindow.ui \
    GUI/playwindow.ui \
    GUI/enterwindow.ui


RESOURCES += \
    resource.qrc \
    space.qrc \
    GUI/Spaceship.qrc

OTHER_FILES += \
    GUI/sky.png \
    GUI/Spaceship.png \
    GUI/SpaceshipSmall.png
