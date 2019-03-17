TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    tester.cpp \
    linearnode.cpp \
    exception.cpp \
    stringhash.cpp \
    treenode.cpp

HEADERS += \
    linearnode.hpp \
    exception.hpp \
    string.hpp \
    stringhash.hpp \
    treenode.hpp
