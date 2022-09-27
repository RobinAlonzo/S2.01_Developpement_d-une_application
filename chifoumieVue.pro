QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db.cpp \
    identification.cpp \
    main.cpp \
    chifoumivue.cpp \
    modele.cpp \
    parametres.cpp \
    presentation.cpp \
    scores.cpp

HEADERS += \
    chifoumivue.h \
    db.h \
    identification.h \
    modele.h \
    parametres.h \
    presentation.h \
    scores.h

FORMS += \
    chifoumivue.ui \
    identification.ui \
    parametres.ui \
    scores.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    chifoumieVue.qrc