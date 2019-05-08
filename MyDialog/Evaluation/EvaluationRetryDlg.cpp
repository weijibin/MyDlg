#include "evaluationretrydlg.h"

EvaluationRetryDlg::EvaluationRetryDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    setFixedSize(240,154);
    insertTitle();
}
void EvaluationRetryDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}
