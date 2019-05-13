#include "evaluationdlgbase.h"
#include <QStyleOption>
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>
#include "EvaluationResultDlg.h"
#include "EvaluationRetryDlg.h"

const int titlePngWidth = 314;
const int titlePngHeight = 206;

EvaluationDlgBase::EvaluationDlgBase(QWidget *parent) : QWidget(parent),m_excessHeight(144)
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Dialog);
    setAttribute(Qt::WA_TranslucentBackground);

    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0); 
}

void EvaluationDlgBase::insertTitle()
{
    QFrame *title = new QFrame(this);
    title->setObjectName("titleEvaluation");
    title->setFixedSize(titlePngWidth,titlePngHeight);
    title->move((width()-titlePngWidth)/2,0);
}

void EvaluationDlgBase::initBody()
{
    m_frame = new QFrame(this);
    m_frame->setObjectName("bodyEvaluation");

    m_closeBtn = new QPushButton(m_frame);
    m_closeBtn->setObjectName("evaluationClose");
    m_closeBtn->setFixedSize(20,20);

    m_layout->addWidget(m_frame);
    setContentsMargins(0,m_excessHeight,0,0);
    setLayout(m_layout);

    connect(m_closeBtn,&QPushButton::clicked,[=](){
        this->close();
    });
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

void EvaluationDlgBase::sltSubmitResult(bool isSuccess)
{
    if(isSuccess)
    {
        //successful
    }
    else
    {
        //retry
    }
}

void EvaluationDlgBase::setEvlTemplate(QMap<int, TeacherEvlTemplate> &info)
{
    m_evlTemplate = info;
}




