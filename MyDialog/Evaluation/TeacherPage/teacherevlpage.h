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
    const TeacherEvlResult& getResult();
signals:

public slots:

private:
    void initUI();
    void initLeft();
    void initRight();

    void updateRightWhenChecked();
private:
    TeacherEvlTemplate m_template;
    TeacherEvlResult m_result;
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
