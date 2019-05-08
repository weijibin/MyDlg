#include "evaluationdlgbase.h"

EvaluationDlgBase::EvaluationDlgBase(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
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
