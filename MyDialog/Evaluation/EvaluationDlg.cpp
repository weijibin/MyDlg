#include "EvaluationDlg.h"
#include <QStyleOption>
#include <QPainter>

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(297,249);
}

void EvaluationDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}
