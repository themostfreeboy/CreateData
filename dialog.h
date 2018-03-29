#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QtGlobal>
#include <QMessageBox>
//#include <QDebug>

#define TIME_1_MINUTE -101//1分钟
#define TIME_2_MINUTE -102//2分钟
#define TIME_3_MINUTE -103//3分钟
#define TIME_4_MINUTE -104//4分钟
#define TIME_5_MINUTE -105//5分钟
#define TIME_10_MINUTE -110//10分钟
#define TIME_15_MINUTE -115//15分钟
#define TIME_20_MINUTE -120//20分钟
#define TIME_30_MINUTE -130//30分钟
#define TIME_1_HOUR -201//1小时
#define TIME_2_HOUR -202//2小时
#define TIME_3_HOUR -203//3小时
#define TIME_4_HOUR -204//4小时
#define TIME_5_HOUR -205//5小时
#define TIME_6_HOUR -206//6小时
#define TIME_10_HOUR -210//10小时
#define TIME_12_HOUR -212//12小时
#define TIME_1_DAY -301//1天
#define TIME_2_DAY -302//2天
#define TIME_3_DAY -303//3天
#define TIME_5_DAY -305//5天
#define TIME_10_DAY -310//10天
#define TIME_15_DAY -315//15天
#define TIME_1_EWEEK -401//1周
#define TIME_2_WEEK -402//2周
#define TIME_1_MONTH -501//1个月，特殊处理(28天，29天，30天，31天)
#define TIME_2_MONTH -502//2个月，特殊处理(28天，29天，30天，31天)
#define TIME_3_MONTH -503//3个月，特殊处理(28天，29天，30天，31天)
#define TIME_4_MONTH -504//4个月，特殊处理(28天，29天，30天，31天)
#define TIME_6_MONTH -506//6个月，特殊处理(28天，29天，30天，31天)
#define TIME_1_YEAR -601//1年，特殊处理(365天，366天)
#define TIME_2_YEAR -602//2年，特殊处理(365天，366天)
#define TIME_3_YEAR -603//3年，特殊处理(365天，366天)
#define TIME_4_YEAR -604//4年，特殊处理(365天，366天)
#define TIME_5_YEAR -605//5年，特殊处理(365天，366天)

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_btnStart_clicked();

private:
    Ui::Dialog *ui;
    QString hostName;//数据库host
    QString databaseName;//数据库名称
    QString userName;//数据库用户名
    QString password;//数据库密码
    QString startDate;//开始时间
    int period;//两张表的时间间隔(单位:秒)
    int NumberOfTables;//创建表的数量
    int NumberOfRecords;//每张表中的测试数据数目
    QString TableNamePerfix;//表名前缀
    QString TableNameFormat;//表名时间格式
    QDateTime currentDateTime;//用户保存当前计算出的日期，避免每次计算日期时从头计算而效率低(在calTableName函数中以类似于迭代器的形式去使用)
    int NumberOfItems;//每张表中的字段数
    QString itemNameArray[1024];//字段名
    QString itemOtherArray[1024];//字段类型、字段约束、字段描述等其他信息
    QString tableOther;//表中的其他约束等信息(主键、索引、外键等设置)
    QString outtableOther;//位于create table括号之外的额外添加信息(引擎设置、字符集设置等)

    QSqlDatabase db;//数据库操作对象
    QSqlQuery sqlQuery;//数据库操作返回对象
    bool sqlResult;//数据库操作是否成功结果
    bool config();//配置函数
    bool connectDB();//连接数据库
    bool query(QString sql);//数据库操作
    void mylog(QString log);//输出日志信息
    QString calTableName();//计算表名称
    int randInt(int min,int max);//产生范围内的随机整数
    QString randValue(QString data[],int rangeMin,int rangeMax);//返回data数组中随机下标所对应的值
    QString randQString(int length);//产生指定长度的随机字符串
    bool createTable(QString tableName);//创建表
    bool insertItem(QString tableName);//插入数据
};

#endif // DIALOG_H
