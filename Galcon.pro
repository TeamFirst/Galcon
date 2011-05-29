QT += core gui network


TEMPLATE = app

SOURCES += \
    main.cpp \
    gui.cpp \
    enterwindow.cpp \
    Planet.cpp \
    Game.cpp \
    Fleet.cpp \
    criticalmessage.cpp

HEADERS += \
    gui.h \
    enterwindow.h \
    Player.h \
    Planet.h \
    Game.h \
    Fleet.h \
    Space.h \
    SceneUpdate.h \
    criticalmessage.h
    Message.h \
    SceneUpdate.h

FORMS += \
    enterwindow.ui

OTHER_FILES += \
    README
