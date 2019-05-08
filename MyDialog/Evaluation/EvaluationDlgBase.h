#ifndef EVALUATIONDLGBASE_H
#define EVALUATIONDLGBASE_H

#include <QWidget>
#include <QMouseEvent>

class EvaluationDlgBase : public QWidget
{
    Q_OBJECT
public:
    explicit EvaluationDlgBase(QWidget *parent = 0);

signals:

public slots:
protected:
    virtual void mousePressEvent(QMouseEvent*event) override;
    virtual void mouseMoveEvent(QMouseEvent*event) override;
    virtual void paintEvent(QPaintEvent *event) override;
//    virtual void resizeEvent(QResizeEvent *event) override;
private:
    QPoint m_offset = QPoint();
};

#endif // EVALUATIONDLGBASE_H
