#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//评价窗口
void Widget::on_pushButton_clicked()
{
    qDebug()<< QStringLiteral("评价窗口");
}

//成功提示窗口
void Widget::on_pushButton_2_clicked()
{
    qDebug()<<QStringLiteral("成功提示窗口");
}

//重试窗口
void Widget::on_pushButton_3_clicked()
{
    qDebug()<<QStringLiteral("重试窗口");
}
