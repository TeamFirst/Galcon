QT += core gui network


TEMPLATE = app

SOURCES += \
    main.cpp \
#    gui.cpp \
#    enterwindow.cpp \
    Planet.cpp \
    Game.cpp \
    Fleet.cpp \
#    messageconnecttoserver.cpp \
    Space.cpp \
#    criticalmessage.cpp


HEADERS += \
#    gui.h \
#    enterwindow.h \
    Player.h \
    Planet.h \
     Game.h \
     Fleet.h \
     Space.h \
    SceneUpdate.h \
#    criticalmessage.h \
#    Message.h \
#    messageconnecttoserver.h \
#    SceneUpdate.h \
#    message/MessageStartMapGame.h \
#    message/MessageTimeToStartGame.h \
#    message/MessageStepPlayer.h \
#    message/MessageStateMap.h \
#    message/MessageItf.h \
#    message/MessageFinishGame.h \
#    message/MessageError.h \
#    message/MessageConnectToServer.h \
#    message/MessageAddView.h

FORMS += \
    enterwindow.ui

OTHER_FILES += \
    README
