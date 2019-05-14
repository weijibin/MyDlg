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
#include <QScrollBar>
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
    m_tipLabel->setObjectName("errorTip");
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

    //只有主讲时的特殊处理
    if(info.size()==1)
    {
        m_scrollEvlt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedSize(594,278+m_excessHeight);
    }

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

        connect(page1,&TeacherEvlPage::sigEnableVisible,[=](QWidget *w){
            //此方法有问题 ，有改进空间
            int val = m_scrollEvlt->verticalScrollBar()->minimum();
            m_scrollEvlt->verticalScrollBar()->setValue(val);

            //只有主讲时的特殊处理
            if(m_evlTemplate.size()==1)
            {
                int curHeight = 155+w->height()+m_excessHeight;
                if(curHeight > (278+m_excessHeight))
                    setFixedHeight(curHeight);
            }

        });


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

                connect(page2,&TeacherEvlPage::sigEnableVisible,[=](QWidget *w){
                    int val = m_scrollEvlt->verticalScrollBar()->maximum();
                    m_scrollEvlt->verticalScrollBar()->setValue(val);
                });
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
    m_resultInfo.clear();
    bool isAvliable = false;
    for(int i = 0; i<m_pages.size(); i++)
    {
        isAvliable |= m_pages.at(i)->isOutPutAvaliable();
        TeacherEvlResult ret = m_pages.at(i)->getResult();
        m_resultInfo.insert(ret.type,ret);
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

//            qDebug()<<"EvaluationDlg::initConnections=== submit";
            emit sigSubmitResult(getResultInfo());
        }
        else
        {
//            qDebug()<<"EvaluationDlg::initConnections=== Input Error!!!!";
            m_tipLabel->setVisible(true);
            m_tipLabel->setText(getErrorInfoByResult());

            QTimer::singleShot(2000,this,[=](){
                m_tipLabel->setVisible(false);
            });
        }
    });
}

QString EvaluationDlg::getErrorInfoByResult()
{
    QString info = "other";
    int count = m_resultInfo.count();
    if(count == 1)
    {
        if(m_resultInfo.value(1).resumeEvl.isEmpty())
            info = QString::fromLocal8Bit("请选择一个满意度");
        else
            info = QString::fromLocal8Bit("请输入文字建议或至少选择一个标签");
    }
    else if(count == 2)
    {
        bool is1 = m_resultInfo.value(1).resumeEvl.isEmpty();
        bool is2 = m_resultInfo.value(2).resumeEvl.isEmpty();

        if(is1 && is2)
            info = QString::fromLocal8Bit("请选择一个满意度");
        else
            info = QString::fromLocal8Bit("请至少为一位老师做出文字评价或者至少选择一个标签");
    }

    return info;
}
