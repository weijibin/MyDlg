#include "EvaluationResultDlg.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

EvaluationResultDlg::EvaluationResultDlg(QWidget *parent):EvaluationDlgBase(parent)
{
    initBody();
    setFixedSize(200,128);
    setContentsMargins(0,0,0,0);

    m_closeBtn->setVisible(false);

}
void EvaluationResultDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationResultDlg::initBody()
{
    EvaluationDlgBase::initBody();
    QVBoxLayout *layout = new QVBoxLayout(m_frame);
    layout->setContentsMargins(0,0,0,0);
    layout->addSpacing(20);
    QLabel* label = new QLabel(m_frame);
    label->setFixedSize(60,60);
    label->setObjectName("resultLabel");
    layout->addWidget(label,0,Qt::AlignCenter);
    layout->addSpacing(2);
    QLabel *label1 = new QLabel(m_frame);
    label1->setObjectName("resultTip");
    label1->setFixedSize(56,20);
    label1->setText(QString("提交成功"));
    label1->setAlignment(Qt::AlignHCenter);
    layout->addWidget(label1,0,Qt::AlignCenter);
    layout->addSpacing(20);
    m_frame->setLayout(layout);
}
