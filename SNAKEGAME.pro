include(../rasterwindow/rasterwindow.pri)

# work-around for QTBUG-13496
CONFIG += no_batch

SOURCES += \
    autosnake.cpp \
    campaign.cpp \
    main.cpp \
    mainwindow.cpp \
    multiplesnake.cpp \
    rasterwindow.cpp \
    snake.cpp \
    widget.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/gui/analogclock
INSTALLS += target

HEADERS += \
    autosnake.h \
    campaign.h \
    mainwindow.h \
    multiplesnake.h \
    rasterwindow.h \
    snake.h \
    widget.h

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

FORMS +=
