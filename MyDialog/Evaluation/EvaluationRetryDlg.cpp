#include "evaluationretrydlg.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

EvaluationRetryDlg::EvaluationRetryDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    setFixedSize(480,304+m_excessHeight);

    initBody();
    insertTitle();
    initConnections();
}
void EvaluationRetryDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationRetryDlg::initBody()
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

    layout->addSpacing(20);

    m_frame->setLayout(layout);
}

void EvaluationRetryDlg::initConnections()
{
    connect(m_retryBtn,&QPushButton::clicked,[=](){
        qDebug()<<"EvaluationRetryDlg::initConnections=== Retry";
        emit sigSubmitResult(getResultInfo());
    });
}
