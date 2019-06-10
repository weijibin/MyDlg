#ifndef TEACHEREVLPAGE_H
#define TEACHEREVLPAGE_H

#include <QWidget>
#include <QFrame>
#include <QPixmap>
#include "Evaluation/EvaluationDlgBase.h"

class QLabel;
class QPushButton;
class TeacherHeadImg;
class QStackedWidget;
class QTextEdit;
class QButtonGroup;
class TeacherEvlEdit;

class TeacherEvlPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float process READ getProcess WRITE setProcess)
public:
    explicit TeacherEvlPage(const TeacherEvlTemplate& t,QWidget *parent = 0);
    virtual ~TeacherEvlPage();
    const TeacherEvlResult& getResult();
    float getProcess(){return m_process;}
    void  setProcess(float val);

    bool  isOutPutAvaliable();
signals:
    void sigEnableVisible(QWidget*w);
    void sigInputChanged(int type);  //引起变化的类型  type: 1:选择主标签  2:选择子标签或者输入评价
public slots:

private:
    void initUI();
    void initLeft();
    void initRight();

    void initConnections();

    void updateRightWhenChecked();
    void spreadAnimation();
    void updatePlaceHolderById(int index);
    void clearDetailChecked(QButtonGroup *group);

    QString getElidedText(QFont font, QString str, int maxWidth);
private:
    TeacherEvlTemplate m_template;
    TeacherEvlResult m_result;
private:
    float m_process=0;
    bool m_isFirstAni = true;

    QStringList m_placeHolder;
private:
    QFrame *m_left;
    QFrame *m_right;

    QLabel * m_teacherName;
    TeacherHeadImg * m_teacherImg;

    QWidget * m_resumeWidget;
    QButtonGroup * m_resumeGroup;
    QList<QPushButton*> *m_resumeBtns;

    QList<QButtonGroup*> m_detailGroups;


    QStackedWidget * m_stackWidget;


    TeacherEvlEdit * m_textEdit = nullptr;
};

#endif // TEACHEREVLPAGE_H
