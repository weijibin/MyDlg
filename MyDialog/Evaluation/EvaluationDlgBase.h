#ifndef EVALUATIONDLGBASE_H
#define EVALUATIONDLGBASE_H

#include <QWidget>
#include <QPixmap>
#include <QMap>
class QMouseEvent;
class QVBoxLayout;
class QFrame;
class QPushButton;

struct TeacherEvlTemplate
{
   QString name;
   QPixmap img;
   QStringList resumeDscrb;
   QMap<int,QStringList> detailDscrb;
   bool isNeedTxtEvl=true;
   int type=1; //1,主讲  2,辅导
};

struct TeacherEvlResult
{
   QString resumeEvl="";
   QStringList detailEvl;
   QString textEvl="";
   int type=1; //1,主讲  2,辅导
};

class EvaluationDlgBase : public QWidget
{

    Q_OBJECT
public:
    explicit EvaluationDlgBase(QWidget *parent = 0);

    const QMap<int,TeacherEvlResult>& getResultInfo(){return m_resultInfo;}
    void setResultInfo(QMap<int,TeacherEvlResult> &info) {m_resultInfo = info;}

    const QMap<int,TeacherEvlTemplate>& getEvlTemplate(){return m_evlTemplate;}
    virtual void setEvlTemplate(QMap<int,TeacherEvlTemplate> &info);

signals:
    void sigSubmitResult(const QMap<int,TeacherEvlResult> &info);

public slots:
    virtual void sltSubmitResult(bool isSuccess);

protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent*event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    void insertTitle();
    virtual void initBody();
protected:
    const int m_excessHeight;
    QFrame * m_frame;
    QPushButton *m_closeBtn;

    QMap<int,TeacherEvlResult> m_resultInfo;
    QMap<int,TeacherEvlTemplate> m_evlTemplate;
private:
    QPoint m_offset = QPoint();
    QVBoxLayout * m_layout;

};

#endif // EVALUATIONDLGBASE_H
