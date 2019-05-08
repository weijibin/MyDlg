#-------------------------------------------------
#
# Project created by QtCreator 2019-05-08T16:53:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyDialog
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    Evaluation/EvaluationDlgBase.cpp \
    Evaluation/EvaluationRetryDlg.cpp \
    Evaluation/EvaluationResultDlg.cpp \
    Evaluation/EvaluationDlg.cpp

HEADERS  += widget.h \
    Evaluation/EvaluationDlgBase.h \
    Evaluation/EvaluationRetryDlg.h \
    Evaluation/EvaluationResultDlg.h \
    Evaluation/EvaluationDlg.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
