#include "mysql_connect.h"

mysql_connect::mysql_connect(QWidget *parent)
    : QWidget{parent}
{
    QSqlDatabase db;
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
    QSqlQuery query(db);
    QString sql_1 = "create table student (id int primary key,"
                    "name varchar(20))";
    query.exec(sql_1);
    query.exec("insert into student values(0, 'Mike')");
    query.exec("insert into student values(1, 'Lili')");
    query.exec("insert into student values(2, 'Jame')");
    query.exec("select * from student");//执行sql语句
    while(query.next()){
        qDebug()<< query.value(0).toInt() << query.value(1).toString();
    }

    QString connection;
    connection = db.connectionName();
    db.close();
    QSqlDatabase::removeDatabase(connection);
}
