#ifndef TEACHERHEADIMG_H
#define TEACHERHEADIMG_H

#include <QWidget>
#include <QPixmap>
#include <QPen>

class TeacherHeadImg : public QWidget
{
    Q_OBJECT
public:
    TeacherHeadImg(int type,const QPixmap &map,QWidget*parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QPixmap m_pix;
    int m_type;
    QString m_teacherType;
    QPen    m_pen;
    QBrush  m_brush;
    QRect   m_textRect;
};

#endif // TEACHERHEADIMG_H
