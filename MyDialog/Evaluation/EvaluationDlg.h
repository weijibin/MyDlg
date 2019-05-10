#ifndef EVALUATIONDLG_H
#define EVALUATIONDLG_H
#include "EvaluationDlgBase.h"

class QPushButton;
class QScrollArea;
class EvaluationDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationDlg(QWidget *parent=0);
    virtual void setEvlTemplate(QMap<int, TeacherEvlTemplate> &info) override;
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void initBody() override;
private:
    void updateUiByTemplate();
private:
    QPushButton *m_submitBtn = nullptr;
    QScrollArea *m_scrollEvlt = nullptr;
//    QPushButton *m_loadingBtn;
};

#endif // EVALUATIONDLG_H
