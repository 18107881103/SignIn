#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel.h>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Sql_init();
    void Sql_close();

private:
    Ui::Widget *ui;
    QPushButton *loginButton_lcz;
    QPushButton *signOutButton_lcz;
    QPushButton *emitButton;
    QLabel *label_lcz;
    QLabel *login_time_label;
    QLabel *signOut_time_label;
    QLabel *stay_time_label;
    QTextEdit *nameEdit;
    qint64 login_time;
    qint64 signOut_time;
    QTime startTime;
    QTime endTime;
    QSqlDatabase db;
    QDateTime time1;
    QDateTime time2;
    QString name;
    QString start_time;
    QString end_time;
    bool flag_create_table = false;
    bool flag_insert = false;
    bool login_time_count = false;
    bool signOut_time_count = false;
    int secInt = 0;
    int minuteInt = 0;
    int hourInt = 0;
};
#endif // WIDGET_H
