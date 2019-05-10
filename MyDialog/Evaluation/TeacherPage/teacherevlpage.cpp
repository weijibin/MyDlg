#include "TeacherEvlPage.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QTextEdit>
#include <QString>
#include <QStackedWidget>
#include <QButtonGroup>
#include "TeacherHeadImg.h"
#include <QGridLayout>

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

    m_resumeWidget = new QWidget(this);
    m_resumeWidget->setObjectName("resumeWidget");
    m_resumeWidget->setFixedSize(414,45);
    m_resumeWidget->setAttribute(Qt::WA_TranslucentBackground);

    {
        QHBoxLayout *layoutResum = new QHBoxLayout;
        layoutResum->setContentsMargins(0,0,0,0);
        layoutResum->setSpacing(23);
        m_resumeGroup = new QButtonGroup;

        for(int i = 0; i<m_template.resumeDscrb.size(); i++)
        {
            QPushButton *btn = new QPushButton;
            btn->setObjectName(QString("resumesBtn%1").arg(i));
            btn->setFixedHeight(43);
            btn->setCheckable(true);

            connect(btn,&QPushButton::clicked,[=](){
                m_stackWidget->setCurrentIndex(i);

                m_stackWidget->setVisible(true);
                m_textEdit->setVisible(true);
            });

            layoutResum->addWidget(btn);
            m_resumeGroup->addButton(btn,i);
//            btn->setChecked(true);
        }

        m_resumeWidget->setLayout(layoutResum);
    }


    m_stackWidget = new QStackedWidget(this);

    for(int i=0; i<m_template.resumeDscrb.size(); i++)
    {
        QWidget *w = new QWidget;
        w->setFixedSize(414,100);
        w->setObjectName(QString("resumesWidget%1").arg(i));
        m_stackWidget->addWidget(w);

        {

        }
    }

    m_textEdit = new QTextEdit(this);
    m_textEdit->setObjectName("textEvlPage");
    m_textEdit->setFixedSize(414,80);

    right->addWidget(m_resumeWidget);
    right->addSpacing(8);
    right->addWidget(m_stackWidget);
    right->addSpacing(12);
    right->addWidget(m_textEdit);

    m_right->setLayout(right);

    m_stackWidget->setVisible(false);
    m_textEdit->setVisible(false);

}
