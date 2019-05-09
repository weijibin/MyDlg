#include "evaluationretrydlg.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

EvaluationRetryDlg::EvaluationRetryDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    setFixedSize(480,304+m_excessHeight);

    initBody();
    insertTitle();
}
void EvaluationRetryDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationRetryDlg::initBody()
{
    EvaluationDlgBase::initBody();

    QVBoxLayout *layout = new QVBoxLayout(m_frame);
    layout->setContentsMargins(0,0,0,0);
    layout->addSpacing(12);
    layout->setSpacing(0);

    QHBoxLayout *hLayout = new QHBoxLayout(m_frame);
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

    QPushButton *retryBtn = new QPushButton(m_frame);
    retryBtn->setObjectName("retryBtn");
    retryBtn->setFixedSize(100,40);
    layout->addWidget(retryBtn,0,Qt::AlignCenter);

    layout->addSpacing(20);
    m_frame->setLayout(layout);
}
