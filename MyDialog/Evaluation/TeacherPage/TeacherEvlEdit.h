#ifndef TEACHEREVLEDIT_H
#define TEACHEREVLEDIT_H
#include <QTextEdit>
#include <QRect>
class QLabel;
class TeacherEvlEdit : public QTextEdit
{
    Q_OBJECT
public:
    TeacherEvlEdit(QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private slots:
    void sltTextChanged();
private:
    QRect m_tipRect;
    QString m_tipColor;
    QString m_color1;
    QString m_color2;
    int m_maxTextLength;
    int m_textLength;
    int m_warnLenght;

    QLabel *m_tipLabel = nullptr;

};

#endif // TEACHEREVLEDIT_H
