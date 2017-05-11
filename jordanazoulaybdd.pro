TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    tools.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    tools.h

