#ifndef EVALUATIONRETRYDLG_H
#define EVALUATIONRETRYDLG_H
#include "EvaluationDlgBase.h"

class QLabel;
class QTimeLine;
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
    void setLoadingState(bool is);
    void startLoadingAnimation();
    void stopLoadingAnimation();
private:
    QPushButton * m_retryBtn = nullptr;
    QLabel * m_loadingBtn = nullptr;
    //animation
    QTimeLine *m_timeLine = nullptr;
};

#endif // EVALUATIONRETRYDLG_H
