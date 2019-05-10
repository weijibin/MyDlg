#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFile>
#include "Evaluation/EvaluationDlg.h"
#include "Evaluation/EvaluationRetryDlg.h"
#include "Evaluation/EvaluationResultDlg.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);

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
    EvaluationDlg *dlg = new EvaluationDlg(this);
    dlg->setObjectName("evaluationgDlg");

    {
        TeacherEvlTemplate temp1;
        temp1.img = QPixmap();
        temp1.name = "111111";
        temp1.type = 1;
        temp1.resumeDscrb = QStringList()<<QStringLiteral("满意")<<QStringLiteral("一般")
                                        <<QStringLiteral("不满意");

        QMap<int,QStringList> map;
        QStringList fonts1;
        fonts1<< "Arial" << "Helvetica" << "Times" << "Courier";
        map.insert(0,fonts1);
        QStringList fonts2;
        fonts2 << "Arial22" << "Helvetica22" << "Times22" << "Courier22";
        map.insert(1,fonts2);
        QStringList fonts3;
        fonts3 << "Arial33" << "Helvetica33" << "Times33" << "Courier33";
        map.insert(2,fonts3);
        temp1.detailDscrb = map;
        temp1.isNeedTxtEvl = true;


        TeacherEvlTemplate temp2;
        temp2.img = QPixmap();
        temp2.name = "111111";
        temp2.type = 2;
        temp2.resumeDscrb = QStringList()<<QStringLiteral("满意")<<QStringLiteral("一般")
                                        <<QStringLiteral("不满意");
        temp2.detailDscrb = map;
        temp2.isNeedTxtEvl = true;

        QMap<int,TeacherEvlTemplate> infos;
        infos.insert(temp1.type,temp1);
        infos.insert(temp2.type,temp2);

        dlg->setEvlTemplate(infos);
    }

//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}

//成功提示窗口
void Widget::on_pushButton_2_clicked()
{
    qDebug()<<QStringLiteral("成功提示窗口");
    EvaluationResultDlg *dlg = new EvaluationResultDlg(this);
    dlg->setObjectName("evaluationResultDlg");
//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}

//重试窗口
void Widget::on_pushButton_3_clicked()
{
    qDebug()<<QStringLiteral("重试窗口");
    EvaluationRetryDlg *dlg = new EvaluationRetryDlg(this);
    dlg->setObjectName("evaluationRetryDlg");
//    dlg->setWindowModality(Qt::ApplicationModal);
    dlg->show();
}
