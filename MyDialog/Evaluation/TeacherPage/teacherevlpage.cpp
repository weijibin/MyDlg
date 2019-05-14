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
#include <QPropertyAnimation>
#include <QDebug>
#include "TeacherEvlEdit.h"

TeacherEvlPage::TeacherEvlPage(const TeacherEvlTemplate& t,QWidget *parent) : QWidget(parent)
{
    m_template = t;
    this->setFixedWidth(554);
    this->resize(554,283);
    this->setContentsMargins(0,0,0,0);

    initUI();
    m_result.type = m_template.type;
//    this->adjustSize();

    m_placeHolder.append(QStringLiteral("说说老师有哪里可以改进的呢？"));
    m_placeHolder.append(QStringLiteral("说说老师有哪里可以改进的呢？"));
    m_placeHolder.append(QStringLiteral("谢谢你的肯定，说点什么夸夸你的老师吧！"));
}

const TeacherEvlResult& TeacherEvlPage::getResult()
{
    int index = m_resumeGroup->checkedId();
    if(index != -1)
    {
        m_result.resumeEvl = m_template.resumeDscrb.at(index);
        m_result.detailEvl.clear();
        QStringList lst = m_template.detailDscrb.value(index);
        QButtonGroup*group = m_detailGroups.at(index);
        foreach(QAbstractButton *btn, group->buttons())
        {
            if(btn->isChecked())
            {
                int id = group->id(btn);
                m_result.detailEvl.append(lst.at(id));
            }
        }
    }
    if(m_template.isNeedTxtEvl && m_textEdit->toPlainText().count())
        m_result.textEvl = m_textEdit->toPlainText();
    return m_result;
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

    layout->setSizeConstraint(QLayout::SetFixedSize);

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
            btn->setContentsMargins(3,3,3,3);

            connect(btn,&QPushButton::clicked,[=](){
//                TeacherEvlResult ret = getResult();
                m_stackWidget->setCurrentIndex(i);
                updateRightWhenChecked();
                updatePlaceHolderById(i);
                if(m_isFirstAni){
                    spreadAnimation();
                    m_isFirstAni = false;
                }
            });

            layoutResum->addWidget(btn);
            m_resumeGroup->addButton(btn,i);
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
            QGridLayout * layoutGrid = new QGridLayout;
            QStringList lst = m_template.detailDscrb.value(i);
            QButtonGroup *group = new QButtonGroup(this);
            for(int i = 0; i< lst.size(); i++)
            {
                QPushButton *btn = new QPushButton;
                btn->setText(lst.at(i));
                btn->setCheckable(true);
                btn->setFixedHeight(28);
                group->setExclusive(false);
                group->addButton(btn,i);
                int row = i/3;
                int col = i%3;
                layoutGrid->addWidget(btn,row,col);
                w->setLayout(layoutGrid);
            }
            m_detailGroups.append(group);
        }
    }

    right->addWidget(m_resumeWidget);
    right->addSpacing(8);
    right->addWidget(m_stackWidget);

    if(m_template.isNeedTxtEvl)
    {
        m_textEdit = new TeacherEvlEdit(this);
        m_textEdit->setObjectName("textEvlPage");
        m_textEdit->setFixedSize(414,80);
        right->addSpacing(12);
        right->addWidget(m_textEdit);
        m_textEdit->setPlaceholderText(QStringLiteral("说说老师有哪里可以改进的呢？"));
    }
    m_right->setLayout(right);
    updateRightWhenChecked();
}

void TeacherEvlPage::updateRightWhenChecked()
{
    if(m_resumeGroup->checkedButton())
    {
        m_stackWidget->setVisible(true);
        if(m_template.isNeedTxtEvl)
        {
            m_textEdit->setVisible(true);
        }
    }
    else
    {
        m_stackWidget->setVisible(false);
        if(m_template.isNeedTxtEvl)
        {
            m_textEdit->setVisible(false);
        }
    }
}

void TeacherEvlPage::updatePlaceHolderById(int index)
{
    if(m_textEdit)
        m_textEdit->setPlaceholderText(m_placeHolder.at(index));
}

void TeacherEvlPage::setProcess(float val)
{
    m_process = val;
    if(m_template.isNeedTxtEvl)
    {
        m_textEdit->setFixedHeight(val*80);
    }
    m_stackWidget->setFixedHeight(val*100);

    emit sigEnableVisible(this);
}

void TeacherEvlPage::spreadAnimation()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "process");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


bool TeacherEvlPage::isOutPutAvaliable()
{
    bool isAvaliable = false;

    const TeacherEvlResult& result = getResult();
    bool isResumAvail = !result.resumeEvl.isEmpty();
    bool isDetailAvail = result.detailEvl.size()>0;
    bool isTextAvail =  m_template.isNeedTxtEvl? (!result.textEvl.isEmpty()):true;

    isAvaliable = isResumAvail&&(isDetailAvail||isTextAvail);
    return isAvaliable;
}
