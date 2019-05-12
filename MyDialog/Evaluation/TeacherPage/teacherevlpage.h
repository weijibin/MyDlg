#ifndef TEACHEREVLPAGE_H
#define TEACHEREVLPAGE_H

#include <QWidget>
#include <QFrame>
#include <QPixmap>
#include <Evaluation/EvaluationDlgBase.h>

class QLabel;
class QPushButton;
class TeacherHeadImg;
class QStackedWidget;
class QTextEdit;
class QButtonGroup;

class TeacherEvlPage : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float process READ getProcess WRITE setProcess)
public:
    explicit TeacherEvlPage(const TeacherEvlTemplate& t,QWidget *parent = 0);
    const TeacherEvlResult& getResult();
    float getProcess(){return m_process;}
    void  setProcess(float val);
signals:

public slots:

private:
    void initUI();
    void initLeft();
    void initRight();

    void updateRightWhenChecked();
    void spreadAnimation();
private:
    TeacherEvlTemplate m_template;
    TeacherEvlResult m_result;
private:
    float m_process=0;
    bool m_isFirstAni = true;
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


    QTextEdit * m_textEdit = nullptr;
};

#endif // TEACHEREVLPAGE_H
