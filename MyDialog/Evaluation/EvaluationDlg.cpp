#include "EvaluationDlg.h"
#include <QStyleOption>
#include <QPainter>

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(297,249);

//    QWidget *title = new QWidget(this);
//    title->setFixedSize(100,100);

//    title->move(50,-100);
//    title->show();
}

void EvaluationDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}
