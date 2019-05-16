#include "evaluationretrydlg.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimeLine>
#include <QDebug>

EvaluationRetryDlg::EvaluationRetryDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    setFixedSize(480,304+m_excessHeight);

    initBody();
    insertTitle();
    initConnections();

    setLoadingState(false);
}
void EvaluationRetryDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationRetryDlg::initBody()
{
    EvaluationDlgBase::initBody();
    connect(m_closeBtn,&QPushButton::clicked,[=](){
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
    layout->addStretch();

    QLabel *label1 = new QLabel(m_frame);
    label1->setObjectName("retryTip");
    label1->setFixedSize(112,20);
    label1->setText(QString("提交失败，请重试"));
    label1->setAlignment(Qt::AlignHCenter);

    layout->addWidget(label1,0,Qt::AlignCenter);
    layout->addStretch();

    m_retryBtn = new QPushButton(m_frame);
    m_retryBtn->setObjectName("retryBtn");
    m_retryBtn->setFixedSize(100,40);
    layout->addWidget(m_retryBtn,0,Qt::AlignCenter);

    m_loadingBtn = new QLabel(m_frame);
    m_loadingBtn->setAttribute(Qt::WA_TranslucentBackground, true);
    m_loadingBtn->setFixedSize(100,40);
    m_loadingBtn->setPixmap(QPixmap(":/res/retryloading/1.png").scaled(100,40));
    m_loadingBtn->adjustSize();

    layout->addWidget(m_loadingBtn,0,Qt::AlignCenter);

    layout->addSpacing(20);

    m_frame->setLayout(layout);
}

void EvaluationRetryDlg::initConnections()
{
    connect(m_retryBtn,&QPushButton::clicked,[=](){
        qDebug()<<"EvaluationRetryDlg::initConnections=== Retry";
        setLoadingState(true);
        emit sigSubmitResult(getResultInfo());
    });
}

void EvaluationRetryDlg::startLoadingAnimation()
{
    if(!m_timeLine)
    {
        m_timeLine = new QTimeLine(1000,this);
        m_timeLine->setFrameRange(1,9);;
        m_timeLine->setUpdateInterval(100);
        m_timeLine->setLoopCount(0);
        connect(m_timeLine, &QTimeLine::frameChanged,[=](int index){
            QString path = QString(":/res/retryloading/%1.png").arg(index);
            QPixmap pix(path);
            m_loadingBtn->setPixmap(pix.scaled(100,40));
        });
    }

    m_timeLine->start();
}

void EvaluationRetryDlg::stopLoadingAnimation()
{
    if(m_timeLine)
        m_timeLine->stop();
}

void EvaluationRetryDlg::setLoadingState(bool is)
{
    if(is)
    {
        m_retryBtn->setVisible(false);
        m_retryBtn->setEnabled(false);

        m_loadingBtn->setVisible(true);

        startLoadingAnimation();

    }
    else
    {
        m_retryBtn->setVisible(true);
        m_retryBtn->setEnabled(true);

        m_loadingBtn->setVisible(false);

        stopLoadingAnimation();
    }

}

