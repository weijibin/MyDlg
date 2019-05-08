#include "EvaluationResultDlg.h"

EvaluationResultDlg::EvaluationResultDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    setFixedSize(100,64);
}
void EvaluationResultDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}
