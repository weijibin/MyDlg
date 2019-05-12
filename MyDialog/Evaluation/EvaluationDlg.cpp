#include "EvaluationDlg.h"
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QDebug>
#include "TeacherPage/TeacherEvlPage.h"

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(594,497+m_excessHeight);

    initBody();
    insertTitle();

//    m_loadingBtn->setVisible(false);
    m_submitBtn->setVisible(true);

}

void EvaluationDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationDlg::initBody()
{
    EvaluationDlgBase::initBody();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->addSpacing(12);
    layout->setSpacing(0);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0,0,12,0);
    hLayout->addStretch();
    hLayout->addWidget(m_closeBtn);

    layout->addLayout(hLayout);


    layout->addSpacing(37);


    QHBoxLayout *hLayoutScrol = new QHBoxLayout();
    hLayoutScrol->setContentsMargins(20,0,20,0);
    m_scrollEvlt = new QScrollArea(m_frame);
    m_scrollEvlt->setObjectName("scrollEvlt");

    m_scrollWidget = new QWidget;
    m_scrollWidget->setObjectName("evlScrollWidget");
    QVBoxLayout *layoutScroll = new QVBoxLayout;
    layoutScroll->addWidget(m_scrollWidget);

    m_scrollEvlt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollEvlt->setWidget(m_scrollWidget);

    hLayoutScrol->addWidget(m_scrollEvlt);

    layout->addLayout(hLayoutScrol);
    layout->addSpacing(20);

    m_submitBtn = new QPushButton(m_frame);
    m_submitBtn->setObjectName("submitBtn");
    m_submitBtn->setFixedSize(179,40);
    layout->addWidget(m_submitBtn,0,Qt::AlignCenter);

    m_submitBtn->setProperty("statusPropery",QString("submit"));
    m_submitBtn->style()->unpolish(m_submitBtn);
    m_submitBtn->style()->polish(m_submitBtn);

    connect(m_submitBtn,&QPushButton::clicked,[=]()
    {
        QString temp = m_submitBtn->property("statusPropery").toString();
        if(temp == "submit")
            m_submitBtn->setProperty("statusPropery",QString("loading"));
        else
            m_submitBtn->setProperty("statusPropery",QString("submit"));
        m_submitBtn->style()->unpolish(m_submitBtn);
        m_submitBtn->style()->polish(m_submitBtn);
        m_submitBtn->update();

//        TeacherEvlPage * page1 = new TeacherEvlPage(m_evlTemplate.first(), this);
//        page1->show();

//        TeacherEvlPage * page2 = new TeacherEvlPage(m_evlTemplate.last(), this);
//        page2->show();
    });

//    m_loadingBtn = new QPushButton(m_frame);
//    m_loadingBtn->setObjectName("loadingBtn");
//    m_loadingBtn->setFixedSize(179,40);
//    layout->addWidget(m_loadingBtn,0,Qt::AlignCenter);
//    m_loadingBtn->setDisabled(true);


    layout->addSpacing(24);
//    layout->setSizeConstraint(QLayout::SetFixedSize);
    m_frame->setLayout(layout);
}

void EvaluationDlg::setEvlTemplate(QMap<int, TeacherEvlTemplate> &info)
{
    EvaluationDlgBase::setEvlTemplate(info);
    if(info.size()>0)
        updateUiByTemplate();
}

void EvaluationDlg::updateUiByTemplate()
{
    TeacherEvlPage * page1 = new TeacherEvlPage(m_evlTemplate.first(), this);
    TeacherEvlPage * page2 = new TeacherEvlPage(m_evlTemplate.last(), this);

    QVBoxLayout * scrolLayout = new QVBoxLayout;
    scrolLayout->setContentsMargins(0,0,0,0);
    scrolLayout->setSpacing(0);
    scrolLayout->addWidget(page1);
    scrolLayout->addSpacing(20);
    scrolLayout->addWidget(page2);
    scrolLayout->addStretch();
    scrolLayout->setSizeConstraint(QLayout::SetFixedSize);
    m_scrollWidget->setLayout(scrolLayout);
}
