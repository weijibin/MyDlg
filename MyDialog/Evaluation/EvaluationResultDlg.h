#ifndef EVALUATIONRESULTDLG_H
#define EVALUATIONRESULTDLG_H
#include "EvaluationDlgBase.h"

class EvaluationResultDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationResultDlg(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // EVALUATIONRESULTDLG_H
