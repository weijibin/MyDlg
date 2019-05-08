#include "evaluationdlgbase.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>

EvaluationDlgBase::EvaluationDlgBase(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);

    QFrame *frame = new QFrame(this);
    frame->setObjectName("bodyEvaluation");
    m_layout->addWidget(frame);

    setLayout(m_layout);
    setContentsMargins(0,0,0,0);

}

void EvaluationDlgBase::insertTitle()
{
    QFrame *title = new QFrame(this);
    title->setObjectName("titleEvaluation");
    title->setFixedSize(100,100);
    m_layout->insertWidget(0,title,0,Qt::AlignHCenter);
}

void EvaluationDlgBase::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_offset = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void EvaluationDlgBase::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_offset);
        event->accept();
    }
}

void EvaluationDlgBase::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//void EvaluationDlgBase::resizeEvent(QResizeEvent *event)
//{

//}
