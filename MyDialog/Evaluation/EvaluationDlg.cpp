#include "EvaluationDlg.h"
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include "TeacherPage/TeacherEvlPage.h"

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(594,497+m_excessHeight);

    initBody();
    insertTitle();

    initConnections();

//    m_loadingBtn->setVisible(false);
//    m_submitBtn->setVisible(true);

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
    m_submitBtn->setProperty("statusPropery",QString("submit"));
    m_submitBtn->style()->unpolish(m_submitBtn);
    m_submitBtn->style()->polish(m_submitBtn);

    layout->addWidget(m_submitBtn,0,Qt::AlignCenter);

//    m_loadingBtn = new QPushButton(m_frame);
//    m_loadingBtn->setObjectName("loadingBtn");
//    m_loadingBtn->setFixedSize(179,40);
//    layout->addWidget(m_loadingBtn,0,Qt::AlignCenter);
//    m_loadingBtn->setDisabled(true);

//    layout->addSpacing(24);

    layout->addSpacing(3);

    QWidget *w = new QWidget(m_frame);
    w->setFixedHeight(17);
    w->setContentsMargins(0,0,0,0);
    QVBoxLayout *layout_w = new QVBoxLayout(w);
    layout_w->setContentsMargins(0,0,0,0);
    layout_w->setSpacing(0);

    m_tipLabel = new QLabel(m_frame);
    m_tipLabel->setFixedHeight(17);
    m_tipLabel->setText("Error Tip!!!");
    m_tipLabel->setVisible(false);
    layout_w->addWidget(m_tipLabel,0,Qt::AlignCenter);
    w->setLayout(layout_w);

    layout->addWidget(w);

    layout->addSpacing(4);

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
    if(m_evlTemplate.contains(1))
    {
        QVBoxLayout * scrolLayout = new QVBoxLayout;
        scrolLayout->setContentsMargins(0,0,0,0);
        scrolLayout->setSpacing(0);

        TeacherEvlPage * page1 = new TeacherEvlPage(m_evlTemplate.value(1), this);
        scrolLayout->addWidget(page1);

        m_pages.append(page1);

        QMap<int,TeacherEvlTemplate>::Iterator iter = m_evlTemplate.begin();
        while(iter != m_evlTemplate.end())
        {
            if(iter.key() != 1)
            {
                scrolLayout->addSpacing(16);
                TeacherEvlPage * page2 = new TeacherEvlPage(iter.value(), this);
                scrolLayout->addWidget(page2);
                m_pages.append(page2);
            }
            iter++;
        }

        scrolLayout->addStretch();
        scrolLayout->setSizeConstraint(QLayout::SetFixedSize);
        m_scrollWidget->setLayout(scrolLayout);
    }
}

bool EvaluationDlg::checkTheValidity()
{
    bool isAvliable = true;
    for(int i = 0; i<m_pages.size(); i++)
    {
        isAvliable &= m_pages.at(i)->isOutPutAvaliable();
    }
    return isAvliable;
}

void EvaluationDlg::initConnections()
{
    connect(m_submitBtn,&QPushButton::clicked,[=]()
    {
        if(checkTheValidity())
        {
            QString temp = m_submitBtn->property("statusPropery").toString();
            if(temp == "submit")
                m_submitBtn->setProperty("statusPropery",QString("loading"));
            else
                m_submitBtn->setProperty("statusPropery",QString("submit"));
            m_submitBtn->style()->unpolish(m_submitBtn);
            m_submitBtn->style()->polish(m_submitBtn);
            m_submitBtn->update();
            m_submitBtn->setEnabled(false);

            qDebug()<<"EvaluationDlg::initConnections=== submit";
            emit sigSubmitResult(getResultInfo());
        }
        else
        {
            qDebug()<<"EvaluationDlg::initConnections=== Input Error!!!!";
            m_tipLabel->setVisible(true);
            m_tipLabel->setText("Error Input!!!");

            QTimer::singleShot(2000,this,[=](){
                m_tipLabel->setVisible(false);
            });
        }
    });
}
