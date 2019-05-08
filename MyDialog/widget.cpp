#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "Evaluation/EvaluationDlg.h"
#include "Evaluation/EvaluationRetryDlg.h"
#include "Evaluation/EvaluationResultDlg.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile f(":/qss/style.qss");
    if ( f.open(QFile::ReadOnly) ) {
        QByteArray a_qss (std::move(f.readAll()));
        f.close();
        this->setStyleSheet(a_qss);
    }
}

Widget::~Widget()
{
    delete ui;
}

//评价窗口
void Widget::on_pushButton_clicked()
{
    qDebug()<< QStringLiteral("评价窗口");
    EvaluationDlg *dlg = new EvaluationDlg;
//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}

//成功提示窗口
void Widget::on_pushButton_2_clicked()
{
    qDebug()<<QStringLiteral("成功提示窗口");
    EvaluationResultDlg *dlg = new EvaluationResultDlg;
//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}

//重试窗口
void Widget::on_pushButton_3_clicked()
{
    qDebug()<<QStringLiteral("重试窗口");
    EvaluationRetryDlg *dlg = new EvaluationRetryDlg;
//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}
