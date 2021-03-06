QT += quick quickcontrols2 sql

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        addnewdata.cpp \
        main.cpp \
        searchmusic.cpp

RESOURCES += qml.qrc \
    qtquickcontrols2.conf \
    icons/icons/20x20/back.png \
    icons/icons/20x20/drawer.png \
    icons/icons/20x20/menu.png \
    icons/icons/20x20@2/back.png \
    icons/icons/20x20@2/drawer.png \
    icons/icons/20x20@2/menu.png \
    icons/icons/20x20@3/back.png \
    icons/icons/20x20@3/drawer.png \
    icons/icons/20x20@3/menu.png \
    icons/icons/20x20@4/back.png \
    icons/icons/20x20@4/drawer.png \
    icons/icons/20x20@4/menu.png \
    icons/icons/index.theme \
    icons/icons/20x20/search.png \
    icons/icons/20x20@2/search.png \
    icons/icons/20x20@3/search.png \
    icons/icons/20x20@4/search.png \
    icons/icons/20x20/add.png \
    icons/icons/20x20@2/add.png \
    icons/icons/20x20@3/add.png \
    icons/icons/20x20@4/add.png


TRANSLATIONS += \
    Design-And-Implementation-Of-Organizing-Iranian-Traditional-Music_fa_IR.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

HEADERS += \
    addnewdata.h \
    searchmusic.h


