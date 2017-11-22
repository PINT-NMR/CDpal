QT       += core gui printsupport widgets

TARGET = CDpal
TEMPLATE = app
CONFIG += c++11 release

#Compile time, file size and performance will increase
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

#Icons for executables (Macx and Win only)
win32:RC_FILE = cdpal.rc
macx:ICON = rc_icon.icns

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

SOURCES += cdpal.cpp \
           exportdialog.cpp \
           fCDdenaturation.cpp \
           globals.cpp \
           helpdialog.cpp \
           main.cpp \
           mainwindow.cpp \
           mfunc.cpp \
           scaledialog.cpp \
           customformat.cpp \
           ftestchisq.cpp \
           ftest.cpp \
           savepreset.cpp \
           loadpreset.cpp \
           displayerror.cpp \
           namefiles.cpp\
           qcustomplot.cpp\
           qcustomplot_global.h \
    simulatedialog.cpp

HEADERS += cdpal.h \
           errorsim.h \
           exportdialog.h \
           globals.h \
           helpdialog.h \
           mainwindow.h \
           mfunc.h \
           output.h \
           scaledialog.h \
           fitFunction.h \
           invertmatrix.h \
           customformat.h \
           ftest.h \
           savepreset.h \
           loadpreset.h \
           displayerror.h \
           namefiles.h\
           qcustomplot.h \
    fitdiff.h \
    simulatedialog.h

FORMS   += cdpal.ui \
           exportdialog.ui \
           helpdialog.ui \
           mainwindow.ui \
           scaledialog.ui \
           customformat.ui \
           ftest.ui \
           savepreset.ui \
           loadpreset.ui \
           displayerror.ui \
           namefiles.ui \
    simulatedialog.ui

RESOURCES += \
           img/icon.qrc
