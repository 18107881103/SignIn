#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Sql_init();
    QDateTime time = QDateTime::currentDateTime();
    login_time_label = new QLabel(this);
    signOut_time_label = new QLabel(this);
    signOut_time_label->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    signOut_time_label->setVisible(false);
    signOut_time_label->move(500,105);
    login_time_label->setText(time.toString("yyyy-MM-dd HH:mm:ss"));
    login_time_label->move(350,105);
    login_time_label->setVisible(false);
    loginButton_lcz = new QPushButton(this);
    label_lcz = new QLabel(this);
    label_lcz->setText("林承志");
    label_lcz->move(100,105);
    loginButton_lcz->setText("签到");
    loginButton_lcz->move(150,100);
    signOutButton_lcz = new QPushButton(this);
    signOutButton_lcz->setText("签退");
    signOutButton_lcz->move(250,100);
    emitButton = new QPushButton(this);
    emitButton->setText("提交");
    emitButton->move(350,300);
    stay_time_label = new QLabel(this);
    connect(loginButton_lcz, &QPushButton::clicked,
            [=](){
                time1 = QDateTime::currentDateTime();
                login_time_label->setText(time1.toString("yyyy-MM-dd HH:mm:ss"));
                login_time = time.toMSecsSinceEpoch();
                login_time_label->setVisible(true);
                startTime = QTime::currentTime();
                //qDebug()<<time2.toString("yyyy-MM-dd HH:mm:ss");
                login_time_count = true;
                update();
            });
    connect(signOutButton_lcz, &QPushButton::clicked,
            [=](){
                time2 = QDateTime::currentDateTime();
                signOut_time_label->setText(time2.toString("yyyy-MM-dd HH:mm:ss"));
                signOut_time_label->setVisible(true);
                signOut_time = time.toMSecsSinceEpoch();
                endTime = QTime::currentTime();
                //qDebug()<<time.toString("yyyy-MM-dd HH:mm:ss");
                signOut_time_count = true;
                int mSecInt = startTime.msecsTo(endTime);
                qDebug()<<mSecInt<<" "<<time1.toString();
                QString secNum;
                QString minuteNum;
                QString hourNum;
                if(mSecInt<60000)
                    secInt = mSecInt/1000;
                else if(mSecInt>60000&&mSecInt<3600000){
                    minuteInt=mSecInt/60000;
                    secInt = (mSecInt-minuteInt*60000)/1000;
                    secNum = QString::number(secInt);
                    minuteNum = QString::number(minuteInt);
                }
                else if(mSecInt>3600000){
                    hourInt = mSecInt/3600000;
                    minuteInt = (mSecInt-hourInt*3600000)/60000;
                    secInt = (mSecInt-hourInt*3600000-minuteInt*60000)/1000;
                    minuteNum = QString::number(minuteInt);
                    hourNum = QString::number(hourInt);
                }
                secNum = QString::number(secInt);
                minuteNum = QString::number(minuteInt);
                hourNum = QString::number(hourInt);
                stay_time_label->setText("您本次呆在实验室的时间为"+hourNum+"小时, "+minuteNum+"分钟, "+secNum+"秒");
                stay_time_label->move(100,150);
                stay_time_label->setFixedWidth(400);
                stay_time_label->setVisible(true);
                qDebug()<<time1.toString()<<time2.toString();
                start_time = time1.toString("yyyy-MM-dd HH:mm:ss");
                end_time = time2.toString("yyyy-MM-dd HH:mm:ss");
                update();
    });
    connect(emitButton, &QPushButton::clicked,
            [=](){
                db.open();
                QSqlQuery query(db);
                name = label_lcz->text();
                qDebug()<<name<<start_time<<end_time;
                QString sql_1 = "create table stay_time(name varchar(100), start_time varchar(100), end_time varchar(100))";
                query.exec(sql_1);
                QString sql_2 = QString("insert into stay_time(`name`, `start_time`, `end_time`) values('%1', '%2', '%3')").arg(name).arg(start_time).arg(end_time);
                query.exec(sql_2);
                QString connection;
                connection = db.connectionName();
                db.close();
                QSqlDatabase::removeDatabase(connection);
            });
}
void Widget::Sql_init(){
    if(QSqlDatabase::contains("str1")){
        db = QSqlDatabase::database("str1");
    }else{
        db = QSqlDatabase::addDatabase("QODBC","str1");
    }
    db.setHostName("IP");
    db.setPort(3306);
    db.setDatabaseName("mysql_odbc");
    db.setUserName("root");
    db.setPassword("541124703lcz");
    db.open();
}

Widget::~Widget()
{
    delete ui;
}

