#include "TeacherEvlEdit.h"
#include <QPainter>
#include <QTextCursor>
#include <QDebug>

TeacherEvlEdit::TeacherEvlEdit(QWidget *parent):QTextEdit(parent)
{
    m_tipRect.setRect(340,46,50,17);

    m_color1 = "#8C8CA7";
    m_color2 = "#ff0000";
    m_tipColor = m_color1;
    m_maxTextLength = 200;
    m_warnLenght = 195;
    m_textLength = 0;

    connect(this,SIGNAL(textChanged()),this,SLOT(sltTextChanged()));
}

void TeacherEvlEdit::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);

    QPainter painter(this->viewport());
    painter.save();
    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);

    QPen pen;
    pen.setColor(QColor(m_tipColor));
    painter.setPen(pen);
    painter.drawText(m_tipRect,QString("%1/%2").arg(m_textLength).arg(m_maxTextLength));
    painter.restore();
}

void TeacherEvlEdit::sltTextChanged()
{
    QString textContent = this->toPlainText();
    int length = textContent.count();

    if(length > m_maxTextLength) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        if(cursor.hasSelection()) {
            cursor.clearSelection();
        }
        cursor.deletePreviousChar();
        //设置当前的光标为更改后的光标
        this->setTextCursor(cursor);
    }
    m_textLength = this->toPlainText().length();
    if(m_textLength > m_warnLenght)
    {
        m_tipColor = m_color2;
    }
    else
    {
        m_tipColor = m_color1;
    }

}
