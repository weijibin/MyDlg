#ifndef EVALUATIONDLG_H
#define EVALUATIONDLG_H
#include "EvaluationDlgBase.h"

class QPushButton;
class EvaluationDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationDlg(QWidget *parent=0);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void initBody() override;
private:
    QPushButton *m_sumitBtn;
    QPushButton *m_loadingBtn;
};

#endif // EVALUATIONDLG_H
