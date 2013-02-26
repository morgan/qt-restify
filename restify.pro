TEMPLATE = app
TARGET = restify
DEPENDPATH += .
INCLUDEPATH += .

RESOURCES += media/qimageprepare.qrc

QT += network widgets

HEADERS += restify.h highlighter.h
SOURCES += main.cpp restify.cpp highlighter.cpp 
