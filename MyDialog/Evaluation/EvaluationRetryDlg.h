#ifndef EVALUATIONRETRYDLG_H
#define EVALUATIONRETRYDLG_H
#include "EvaluationDlgBase.h"

class EvaluationRetryDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationRetryDlg(QWidget *parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void initBody() override;
private:
    void initConnections();
private:
    QPushButton * m_retryBtn = nullptr;
};

#endif // EVALUATIONRETRYDLG_H
