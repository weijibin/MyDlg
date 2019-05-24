#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T16:53:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDialog
TEMPLATE = app

LIBS += -lDbgHelp

#QMAKE_CXXFLAGS_RELEASE =
#QMAKECFLAGSRELEASEWITHDEBUGINFOQMAKELFLAGSRELEASE +=
#QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

QMAKE_LFLAGS_RELEASE += /MAP
QMAKE_CFLAGS_RELEASE += /Zi
QMAKE_LFLAGS_RELEASE += /debug /opt:ref


SOURCES += main.cpp\
        widget.cpp \
    Evaluation/EvaluationDlgBase.cpp \
    Evaluation/EvaluationRetryDlg.cpp \
    Evaluation/EvaluationResultDlg.cpp \
    Evaluation/EvaluationDlg.cpp \
    Evaluation/TeacherPage/TeacherEvlPage.cpp \
    Evaluation/TeacherPage/TeacherHeadImg.cpp \
    Evaluation/TeacherPage/TeacherEvlEdit.cpp

HEADERS  += widget.h \
    Evaluation/EvaluationDlgBase.h \
    Evaluation/EvaluationRetryDlg.h \
    Evaluation/EvaluationResultDlg.h \
    Evaluation/EvaluationDlg.h \
    Evaluation/TeacherPage/TeacherEvlPage.h \
    Evaluation/TeacherPage/TeacherHeadImg.h \
    Evaluation/TeacherPage/TeacherEvlEdit.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
