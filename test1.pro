QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++17
#CONFIG += c++17
CONFIG += release

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# Qt modules
#QT += charts

# Include directories
INCLUDEPATH += \
    D:/QT/environment/websocketpp-master/websocketpp-master \
    D:/QT/environment/OpenSSL-Win64/include \
    D:/QT/environment/boost_1_84_0/boost_1_84_0 \
    D:/QT/environment/json-develop/json-develop/single_include/nlohmann

# Library directories and libraries
debug {
    LIBS += -LD:/QT/environment/OpenSSL-Win64/lib/VC/x64/MTd \
        -llibcrypto \
        -llibssl
}

release {
    LIBS += -LD:/QT/environment/OpenSSL-Win64/lib/VC/x64/MT \
        -llibcrypto \
        -llibssl
}

# Source files
SOURCES += \
    client.cpp \
    event.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    newwindow.cpp \
    strategy.cpp \
    strategy_.cpp \
    strategy_1.cpp

# Header files
HEADERS += \
    client.h \
    event.h \
    log.h \
    mainwindow.h \
    newwindow.h \
    strategy.h \
    strategy_.h \
    strategy_1.h

# UI files
FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
