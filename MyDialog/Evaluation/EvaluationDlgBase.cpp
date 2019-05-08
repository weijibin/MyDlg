#include "evaluationdlgbase.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>

EvaluationDlgBase::EvaluationDlgBase(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);

    QFrame *frame = new QFrame(this);
    QVBoxLayout * layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(frame);
    setLayout(layout);
    setContentsMargins(0,0,0,0);
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
