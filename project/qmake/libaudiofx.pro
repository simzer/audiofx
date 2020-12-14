TARGET = audiofx
TEMPLATE = lib
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += staticlib
CONFIG += c++17
CONFIG += silent

QMAKE_CXXFLAGS += -ggdb -g3 -std=c++17 -Wpedantic -Wall -Wextra

REPODIR = $$PWD/../..
DESTDIR = $$REPODIR/bin

SOURCES += $$files($$REPODIR/src/lib/*.cpp, true)
HEADERS += $$files($$REPODIR/src/lib/*.h, true)
HEADERS += $$files($$REPODIR/src/lib/*.inc, true)

INCLUDEPATH += $$REPODIR/src/lib
