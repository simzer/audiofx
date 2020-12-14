TARGET = audiofx
TEMPLATE = lib
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += staticlib
CONFIG += c++17
CONFIG += silent
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -ggdb -g3 -std=c++17 -Wpedantic -Wall -Wextra -ffast-math

REPODIR = $$PWD/../..
DESTDIR = $$REPODIR/bin

SOURCES += $$files($$REPODIR/src/lib/*.cpp, true)
HEADERS += $$files($$REPODIR/src/lib/*.h, true)
HEADERS += $$files($$REPODIR/src/lib/*.inc, true)

INCLUDEPATH += $$REPODIR/src/lib
