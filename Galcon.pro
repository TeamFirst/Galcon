QT += core gui


TEMPLATE = app

SOURCES += \
    main.cpp \
    gui.cpp \
    enterwindow.cpp \
    Planet.cpp \
    Game.cpp \
    Fleet.cpp

HEADERS += \
    gui.h \
    enterwindow.h \
    Player.h \
    Planet.h \
    Game.h \
    Fleet.h \
    Space.h \
    Message.h

FORMS += \
    enterwindow.ui

OTHER_FILES += \
    README
