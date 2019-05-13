#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Evaluation/EvaluationDlgBase.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void slt_getEvlResult(const QMap<int,TeacherEvlResult>& result);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
