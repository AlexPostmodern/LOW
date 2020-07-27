#-------------------------------------------------
#
# Project created by QtCreator 2019-06-29T13:29:39
#
#-------------------------------------------------

QT       += core gui
QT       += sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LOW
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        admin.cpp \
        choosing.cpp \
        database.cpp \
        editor.cpp \
        functioins.cpp \
        instruction.cpp \
        main.cpp \
        mainwindow.cpp \
        menu.cpp \
        mytablemodel.cpp \
        mytextedit.cpp \
        newsyntax.cpp \
        reg.cpp \
        result.cpp \
        test.cpp \
        update.cpp \
        updateadmin.cpp \
        updatetables.cpp

HEADERS += \
        admin.h \
        choosing.h \
        database.h \
        editor.h \
        functioins.h \
        instruction.h \
        mainwindow.h \
        menu.h \
        mytablemodel.h \
        mytextedit.h \
        newsyntax.h \
        reg.h \
        result.h \
        test.h \
        update.h \
        updateadmin.h \
        updatetables.h

FORMS += \
        admin.ui \
        choosing.ui \
        editor.ui \
        instruction.ui \
        mainwindow.ui \
        menu.ui \
        reg.ui \
        result.ui \
        test.ui \
        update.ui \
        updateadmin.ui \
        updatetables.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

RC_ICONS = Ico.ico

DISTFILES +=
