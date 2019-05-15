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
#include <QTimeLine>
#include "TeacherPage/TeacherEvlPage.h"

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(594,497+m_excessHeight);

    initBody();
    insertTitle();

    initConnections();

    m_loadingBtn->setVisible(false);
    m_submitBtn->setVisible(true);
}

EvaluationDlg::~EvaluationDlg()
{

}

void EvaluationDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationDlg::initBody()
{
    EvaluationDlgBase::initBody();
    connect(m_closeBtn,&QPushButton::clicked,[=](){
        if(m_timeLine)
            m_timeLine->stop();
        this->close();
    });

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
    m_submitBtn->setFixedSize(180,40);
    m_submitBtn->setProperty("statusPropery",QString("submit"));
    m_submitBtn->style()->unpolish(m_submitBtn);
    m_submitBtn->style()->polish(m_submitBtn);

    layout->addWidget(m_submitBtn,0,Qt::AlignCenter);

    m_loadingBtn = new QLabel(m_frame);
    m_loadingBtn->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loadingBtn->setObjectName("loadingBtn");
    m_loadingBtn->setFixedSize(180,40);
    m_loadingBtn->setPixmap(QPixmap(":/res/loading/3.png").scaled(180,40));
    m_loadingBtn->adjustSize();

    layout->addWidget(m_loadingBtn,0,Qt::AlignCenter);


//    layout->addSpacing(24);

    layout->addSpacing(3);

    QWidget *w = new QWidget(m_frame);
    w->setFixedHeight(17);
    w->setContentsMargins(0,0,0,0);
    QHBoxLayout *layout_w = new QHBoxLayout(w);
    layout_w->setContentsMargins(0,0,0,0);
    layout_w->setSpacing(0);

    m_tipLabel = new QLabel(m_frame);
    m_tipLabel->setObjectName("errorTip");
    m_tipLabel->setFixedHeight(17);
    m_tipLabel->setText("Error Tip!!!");

    m_tipIcon = new QPushButton(m_frame);
    m_tipIcon->setObjectName("iconTip");
    m_tipIcon->setFixedSize(17,17);

    layout_w->addStretch();
    layout_w->addWidget(m_tipIcon,0,Qt::AlignVCenter);
    layout_w->addSpacing(4);
    layout_w->addWidget(m_tipLabel,0,Qt::AlignCenter);
    layout_w->addStretch();
    w->setLayout(layout_w);

    layout->addWidget(w);
    layout->addSpacing(4);

    m_frame->setLayout(layout);

    setTipVisible(false);
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
    cleanScrollWidget();
    if(info.size()>0)
        updateUiByTemplate();

    m_rawHeight = this->height();
    m_topLeft = this->pos();
}

void EvaluationDlg::setTipVisible(bool visible)
{
    m_tipVisible = visible;
    m_tipIcon->setVisible(visible);
    m_tipLabel->setVisible(visible);
}

void EvaluationDlg::cleanScrollWidget()
{
    m_pages.clear();
    delete m_scrollWidget;
    m_scrollWidget = nullptr;
    m_scrollWidget = new QWidget;
    m_scrollWidget->setObjectName("evlScrollWidget");
    m_scrollEvlt->setWidget(m_scrollWidget);
    m_submitBtn->setProperty("statusPropery",QString("submit"));
    m_submitBtn->style()->unpolish(m_submitBtn);
    m_submitBtn->style()->polish(m_submitBtn);
    m_submitBtn->update();

    setTipVisible(false);
    setLoadingState(false);
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
//                int curHeight = 155+w->height()+m_excessHeight;
//                if(curHeight > (278+m_excessHeight))
//                    setFixedHeight(curHeight);

                int curHeight = 155+w->height()+m_excessHeight;
                if(curHeight > (278+m_excessHeight))
                {
                    setFixedHeight(curHeight);

                    float offset = (curHeight-m_rawHeight)/2;
                    int y = m_topLeft.y();

                    move(m_topLeft.x(),(y-offset));
                }
            }

        });

        connect(page1,&TeacherEvlPage::sigInputChanged,[=](int type){
            if(m_tipVisible)
            {
                bool isCanHide = false;
                int first = 1;
                int count = m_resultInfo.count();
                if(count == 1)
                {
                    if(m_errorTipType.second == type)
                    {
                        isCanHide = true;
                    }
                }
                else
                {
                    if(checkTheValidity())
                    {
                        isCanHide = true;
                    }
                    else
                    {
                        if(m_errorTipType.first==3)
                        {
                            isCanHide = true;
                        }
                        else if(m_errorTipType.first == first)
                        {
                            if(type == m_errorTipType.second)
                            {
                                isCanHide = true;
                            }
                        }
                    }
                }
                if(isCanHide)
                    setTipVisible(!m_tipVisible);
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
                    Q_UNUSED(w)
                    int val = m_scrollEvlt->verticalScrollBar()->maximum();
                    m_scrollEvlt->verticalScrollBar()->setValue(val);
                });

                connect(page2,&TeacherEvlPage::sigInputChanged,[=](int type){
                    if(m_tipVisible)
                    {
                        bool isCanHide = false;
                        int first = 2;
                        int count = m_resultInfo.count();
                        if(count == 1)
                        {
                            if(m_errorTipType.second == type)
                            {
                                isCanHide = true;
                            }
                        }
                        else
                        {
                            if(checkTheValidity())
                            {
                                isCanHide = true;
                            }
                            else
                            {
                                if(m_errorTipType.first==3)
                                {
                                    isCanHide = true;
                                }
                                else if(m_errorTipType.first == first)
                                {
                                    if(type == m_errorTipType.second)
                                    {
                                        isCanHide = true;
                                    }
                                }
                            }
                        }
                        if(isCanHide)
                            setTipVisible(!m_tipVisible);
                    }
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

void EvaluationDlg::startLoadingAnimation()
{
    if(!m_timeLine)
    {
        m_timeLine = new QTimeLine(1000,this);
        m_timeLine->setFrameRange(1,9);;
        m_timeLine->setUpdateInterval(100);
        m_timeLine->setLoopCount(100);
        connect(m_timeLine, &QTimeLine::frameChanged,[=](int index){
            QString path = QString(":/res/loading/%1.png").arg(index);
            QPixmap pix(path);
            m_loadingBtn->setPixmap(pix.scaled(180,40));
        });
    }

    m_timeLine->start();
}

void EvaluationDlg::stopLoadingAnimation()
{
    if(m_timeLine)
        m_timeLine->stop();
}

void EvaluationDlg::setLoadingState(bool is)
{
    if(is)
    {
        m_submitBtn->setVisible(false);
        m_loadingBtn->setVisible(true);

        m_submitBtn->setEnabled(false);
        m_scrollEvlt->setEnabled(false);

        startLoadingAnimation();
    }
    else
    {
        m_submitBtn->setVisible(true);
        m_loadingBtn->setVisible(false);
        m_submitBtn->setEnabled(true);
        m_scrollEvlt->setEnabled(true);

        stopLoadingAnimation();
    }

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

            setTipVisible(false);

            setLoadingState(true);

            emit sigSubmitResult(getResultInfo());

        }
        else
        {
            setTipVisible(true);
            m_tipLabel->setText(getErrorInfoByResult());

            m_errorTipType = getErrorType();

        }
    });
}

QPair<int,int> EvaluationDlg::getErrorType()
{
    QPair<int,int> type;

    int count = m_resultInfo.count();
    if(count == 1)
    {
        type.first = 1;
        if(m_resultInfo.value(1).resumeEvl.isEmpty())
            type.second = 1;
        else
            type.second = 2;
    }
    else if(count == 2)
    {
        bool is1 = m_resultInfo.value(1).resumeEvl.isEmpty();
        bool is2 = m_resultInfo.value(2).resumeEvl.isEmpty();

        if(is1 && is2)
        {
            type.first = 3;
            type.second = 1;
        }
        else if(!is1)
        {
            type.first = 1;
            type.second = 2;
        }
        else if(!is2)
        {
            type.first =2;
            type.second =2;
        }
    }
    return type;
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
