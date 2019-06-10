#include "TeacherEvlEdit.h"
#include <QPainter>
#include <QTextCursor>
#include <QLabel>
#include <QDebug>

TeacherEvlEdit::TeacherEvlEdit(QWidget *parent):QTextEdit(parent)
{
    m_tipRect.setRect(365,60,50,17);

    m_color1 = "#8C8CA7";
    m_color2 = "#ff0000";
    m_tipColor = m_color1;
    m_maxTextLength = 200;
    m_warnLenght = 195;
    m_textLength = 0;

    m_tipLabel = new QLabel(this);
    m_tipLabel->setFixedSize(m_tipRect.size());
    QFont font;
    font.setPixelSize(12);
    m_tipLabel->setFont(font);
    m_tipLabel->move(m_tipRect.topLeft());
    m_tipLabel->setVisible(true);
    m_tipLabel->setStyleSheet(QString("color:%1;").arg(m_tipColor));
    m_tipLabel->setText(QString("%1/%2").arg(m_textLength).arg(m_maxTextLength));

    connect(this,SIGNAL(textChanged()),this,SLOT(sltTextChanged()));
}

void TeacherEvlEdit::paintEvent(QPaintEvent *event)
{
    QTextEdit::paintEvent(event);
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
    if(m_tipLabel)
    {
        m_tipLabel->setStyleSheet(QString("color:%1;").arg(m_tipColor));
        m_tipLabel->setText(QString("%1/%2").arg(m_textLength).arg(m_maxTextLength));
    }
}
