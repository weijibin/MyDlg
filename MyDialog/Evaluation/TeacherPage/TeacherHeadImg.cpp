#include "TeacherHeadImg.h"
#include <QPainter>
#include <QPainterPath>
#include <QFont>

TeacherHeadImg::TeacherHeadImg(int type,const QPixmap &map,QWidget*parent) : QWidget(parent)
{
    m_type = type;
    m_pix = map;

    bool is = map.save(QString("test%1.png").arg(type));

    this->setFixedSize(60,60);

    m_pix = map.scaled(60,60,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    bool is1 = m_pix.save(QString("test%1.png").arg(type+10));

    if(type == 1)
    {
        m_teacherType = QStringLiteral("主讲");
        m_pen.setColor("#FB5E50");
        m_brush.setColor(QColor("#FB5E50"));
    }
    else
    {
        m_teacherType = QStringLiteral("辅导");
        m_pen.setColor("#F47D00");
        m_brush.setColor(QColor("#F47D00"));
    }

    m_brush.setStyle(Qt::SolidPattern);
    m_pen.setWidth(2);

    m_textRect.setRect(19,48,22,11);
}

void TeacherHeadImg::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);


    painter.save();
    QPainterPath path;
    path.addEllipse(rect().center(),28,28);
    painter.setClipPath(path);
    painter.drawPixmap(rect(),m_pix);
    painter.restore();

    painter.save();
    painter.setPen(m_pen);
    painter.drawEllipse(rect().center(),28,28);
    painter.restore();

    painter.save();
    painter.setBrush(m_brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(m_textRect,6,6);
    painter.restore();

    painter.save();
    QFont font;
    font.setPixelSize(11);
    painter.setFont(font);

    QPen pen;
    pen.setColor(QColor("#ffffff"));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawText(m_textRect,Qt::AlignCenter,m_teacherType);
    painter.restore();
}
