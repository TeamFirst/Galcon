QT += core gui network


TEMPLATE = app

SOURCES += \
#    main.cpp \
#    gui.cpp \
#    enterwindow.cpp \
#    #Planet.cpp \
#    #Game.cpp \
#    #Fleet.cpp \
#    #Space.cpp \
#    criticalmessage.cpp \
#    waitwindow.cpp \
    GUI/criticalmessage.cpp \
    GUI/enterwindow.cpp \
    GUI/gui.cpp \
    GUI/main.cpp \
    GUI/Spike.cpp \
    GUI/Waitwindow.cpp \
    GUI/PlayWindow.cpp \
    GUI/PlayArea.cpp \
    GUI/GUIPlanet.cpp \
    GUI/GUIFleet.cpp \
    Planet.cpp \
    Game.cpp \
    Fleet.cpp \
    Space.cpp \
    GUI/GUIView.cpp


HEADERS += \
    gui.h \
    enterwindow.h \
    #Player.h \
    #Planet.h \
    #Game.h \
    #Fleet.h \
    #Space.h \
    #SceneUpdate.h \
    #messageconnecttoserver.h \
    #SceneUpdate.h \
    #waitwindow.h \
    GUI/criticalmessage.h \
    GUI/enterwindow.h \
    GUI/gui.h \
    message/MessageAddView.h \
    message/MessageConnectToServer.h \
    message/MessageError.h \
    message/MessageFinishGame.h \
    message/MessageItf.h \
    message/MessageStartMapGame.h \
    message/MessageStateMap.h \
    message/MessageStepPlayer.h \
    message/MessageTimeToStartGame.h \
    GUI/Spike.h \
    GUI/WaitWindow.h \
    GUI/PlayWindow.h \
    GUI/PlayArea.h \
    GUI/GUIPlanet.h \
    GUI/GUIFleet.h \
    SceneUpdates.h \
    Player.h \
    Planet.h \
    Game.h \
    Fleet.h \
    Space.h \
    GUI/GUIView.h

FORMS += \
    #enterwindow.ui \
    GUI/enterwindow.ui \
    GUI/waitwindow.ui \
    GUI/playwindow.ui

OTHER_FILES += \
    README
