#ifndef EVALUATIONDLG_H
#define EVALUATIONDLG_H
#include "EvaluationDlgBase.h"

class EvaluationDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationDlg(QWidget *parent=0);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // EVALUATIONDLG_H
