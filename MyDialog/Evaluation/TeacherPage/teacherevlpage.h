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
public slots:

private:
    void initUI();
    void initLeft();
    void initRight();

    void updateRightWhenChecked();
    void spreadAnimation();
    void updatePlaceHolderById(int index);
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
