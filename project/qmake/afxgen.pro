TARGET = afxgen
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17
CONFIG += silent

QMAKE_CXXFLAGS += -ggdb -g3 -std=c++17 -Wpedantic -Wall -Wextra

REPODIR = $$PWD/../..
DESTDIR = $$REPODIR/bin

SOURCES += $$files($$REPODIR/src/app/*.cpp, true)
HEADERS += $$files($$REPODIR/src/app/*.h, true)
HEADERS += $$files($$REPODIR/src/app/*.inc, true)

INCLUDEPATH += $$REPODIR/src/lib

PRE_TARGETDEPS += $$DESTDIR/libaudiofx.a
LIBS += -L$$DESTDIR -laudiofx
LIBS += -lz -lm
