#ifndef EVALUATIONDLGBASE_H
#define EVALUATIONDLGBASE_H

#include <QWidget>

class QMouseEvent;
class QVBoxLayout;
class QFrame;
class QPushButton;

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

    void insertTitle();
    virtual void initBody();
protected:
    const int m_excessHeight;
    QFrame * m_frame;
    QPushButton *m_closeBtn;
private:
    QPoint m_offset = QPoint();
    QVBoxLayout * m_layout;
};

#endif // EVALUATIONDLGBASE_H
