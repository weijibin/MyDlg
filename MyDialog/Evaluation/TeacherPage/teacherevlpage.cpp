#include "TeacherEvlPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QTextEdit>
#include <QString>
#include "TeacherHeadImg.h"

TeacherEvlPage::TeacherEvlPage(const TeacherEvlTemplate& t,QWidget *parent) : QWidget(parent)
{
    m_template = t;

//    this->setFixedSize(554,283);
    this->setFixedWidth(554);
    this->resize(554,283);
    this->setWindowFlags(windowFlags()| /*Qt::FramelessWindowHint |*/ Qt::Dialog);
    this->setContentsMargins(0,0,0,0);

    initUI();
}

void TeacherEvlPage::initUI()
{
    QHBoxLayout * layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    m_left = new QFrame(this);
    m_left->setObjectName("evlPageLeft");
    m_left->setFixedWidth(120);
    m_left->setContentsMargins(0,0,0,0);

    m_right = new QFrame(this);
    m_right->setObjectName("evlPageRight");
    m_right->setFixedWidth(434);
    m_right->setContentsMargins(0,0,0,0);

    layout->addWidget(m_left);
    layout->addWidget(m_right);

    this->setLayout(layout);

    initLeft();
    initRight();
}

void TeacherEvlPage::initLeft()
{
    QVBoxLayout * left = new QVBoxLayout();
    left->setSpacing(0);
    left->setContentsMargins(20,20,40,0);

    m_teacherImg = new TeacherHeadImg(m_template.type,m_template.img, this);
    m_teacherImg->setFixedSize(60,60);
    m_teacherImg->setObjectName("teacherImg");

    m_teacherName = new QLabel(this);
    m_teacherName->setFixedHeight(20);
    m_teacherName->setObjectName("teacherName");
    m_teacherName->setAlignment(Qt::AlignCenter);
    m_teacherName->setText(m_template.name);

    left->addWidget(m_teacherImg);
    left->addSpacing(9);
    left->addWidget(m_teacherName);
    left->addStretch();

    m_left->setLayout(left);
}

void TeacherEvlPage::initRight()
{
    QVBoxLayout * right = new QVBoxLayout();
    right->setSpacing(0);
    right->setContentsMargins(0,31,20,20);

    QGroupBox *box1 = new QGroupBox(this);
    QGroupBox *box2 = new QGroupBox(this);
    QTextEdit *edit = new QTextEdit(this);

    right->addWidget(box1);
    right->addWidget(box2);
    right->addWidget(edit);
    right->addStretch();

    m_right->setLayout(right);
}
