#include "EvaluationDlg.h"
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

EvaluationDlg::EvaluationDlg(QWidget*parent):EvaluationDlgBase(parent)
{
    setFixedSize(594,497+m_excessHeight);

    initBody();
    insertTitle();

    m_loadingBtn->setVisible(false);
    m_sumitBtn->setVisible(true);

}

void EvaluationDlg::paintEvent(QPaintEvent *event)
{
    EvaluationDlgBase::paintEvent(event);
}

void EvaluationDlg::initBody()
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


    layout->addSpacing(37);


    QHBoxLayout *hLayoutScrol = new QHBoxLayout(m_frame);
    hLayoutScrol->setContentsMargins(20,0,20,0);
    QScrollArea *scrollEvlt = new QScrollArea(m_frame);
    scrollEvlt->setObjectName("scrollEvlt");
    hLayoutScrol->addWidget(scrollEvlt);
    layout->addLayout(hLayoutScrol);

    layout->addSpacing(20);

    m_sumitBtn = new QPushButton(m_frame);
    m_sumitBtn->setObjectName("sumitBtn");
    m_sumitBtn->setFixedSize(179,40);
    layout->addWidget(m_sumitBtn,0,Qt::AlignCenter);

    m_loadingBtn = new QPushButton(m_frame);
    m_loadingBtn->setObjectName("loadingBtn");
    m_loadingBtn->setFixedSize(179,40);
    layout->addWidget(m_loadingBtn,0,Qt::AlignCenter);
    m_loadingBtn->setDisabled(true);


    layout->addSpacing(24);
    m_frame->setLayout(layout);
}
