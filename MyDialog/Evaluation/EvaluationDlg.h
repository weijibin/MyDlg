#ifndef EVALUATIONDLG_H
#define EVALUATIONDLG_H
#include "EvaluationDlgBase.h"

class QPushButton;
class QScrollArea;
class TeacherEvlPage;
class QLabel;
class QTimeLine;
class EvaluationDlg : public EvaluationDlgBase
{
    Q_OBJECT
public:
    EvaluationDlg(QWidget *parent=0);
    virtual ~EvaluationDlg();
    virtual void setEvlTemplate(QMap<int, TeacherEvlTemplate> &info) override;

    void setTipVisible(bool visible);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void initBody() override;
private:
    void updateUiByTemplate();
    void initConnections();
    bool checkTheValidity();
    QString getErrorInfoByResult();
    QPair<int,int> getErrorType();
    void cleanScrollWidget();
    void setLoadingState(bool is);
    void startLoadingAnimation();
    void stopLoadingAnimation();
private:

//    QMap<int,TeacherEvlPage*> m_pages;
    QList<TeacherEvlPage*> m_pages;

    int m_rawHeight;

    QPushButton *m_submitBtn = nullptr;
    QScrollArea *m_scrollEvlt = nullptr;
    QWidget *m_scrollWidget = nullptr;
    QLabel * m_tipLabel = nullptr;
    QPushButton * m_tipIcon = nullptr;
    QLabel *m_loadingBtn;

    bool m_tipVisible = false;
    ///first :信息出错page index
    /// second: 错误类型
    QPair<int,int> m_errorTipType;

    //animation
    QTimeLine *m_timeLine = nullptr;
};

#endif // EVALUATIONDLG_H
