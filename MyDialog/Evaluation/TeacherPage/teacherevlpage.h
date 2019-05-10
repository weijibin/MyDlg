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
public:
    explicit TeacherEvlPage(const TeacherEvlTemplate& t,QWidget *parent = 0);

signals:

public slots:

private:
    void initUI();
    void initLeft();
    void initRight();
private:
    TeacherEvlTemplate m_template;
private:
    QFrame *m_left;
    QFrame *m_right;

    QLabel * m_teacherName;
    TeacherHeadImg * m_teacherImg;

    QWidget * m_resumeWidget;
    QButtonGroup * m_resumeGroup;
    QList<QPushButton*> *m_resumeBtns;

    QButtonGroup * m_detailGroup0;
    QButtonGroup * m_detailGroup1;
    QButtonGroup * m_detailGroup2;


    QStackedWidget * m_stackWidget;
    QTextEdit * m_textEdit;
};

#endif // TEACHEREVLPAGE_H
