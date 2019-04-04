TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    exception.cpp \
    stringhash.cpp \
    treenode.cpp \
    linkedlistnode.cpp \
    main_test.cxx

HEADERS += \
    exception.hpp \
    string.hpp \
    stringhash.hpp \
    treenode.hpp \
    lambda.hpp \
    linkedlistnode.hpp \
    linkedlistitem.hpp \
    list.hpp \
    stack.hpp \
    queue.hpp \
    keyingtree.hpp
