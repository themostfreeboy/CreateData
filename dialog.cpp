#include "dialog.h"
#include "ui_dialog.h"

QString devtype[10] = {"FW","FID","BID","SVR","SW","VEAD","AV","IDS","DB","DCD"};

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(!config())
    {
        mylog("执行配置函数出错");
        QMessageBox::about(NULL,"error","执行配置函数出错");
        return;
    }
    mylog("执行配置函数成功");
    if(!connectDB())
    {
        mylog("数据库连接失败");
        QMessageBox::about(NULL,"error","数据库连接失败");
        return;
    }
    mylog("数据库连接成功");
}

Dialog::~Dialog()
{
    delete ui;
    db.close();
    QSqlDatabase::removeDatabase("QMYSQL");
}

bool Dialog::config()
{
    hostName = "10.0.20.8";//数据库host
    databaseName = "jxltest";//数据库名称
    userName = "root";//数据库用户名
    password = "123456";//数据库密码
    startDate = "20180129000000";//开始时间
    period = TIME_1_DAY;//两张表的时间间隔(单位:秒)
    NumberOfTables = 10;//创建表的数量
    NumberOfRecords = 5;//每张表中的测试数据数目
    TableNamePerfix = "data";//表名前缀
    TableNameFormat = "yyyyMMddHHmmss";//表名时间格式
    NumberOfItems = 8;//每张表中的字段数

    //字段名
    itemNameArray[0] = "id";
    itemNameArray[1] = "level";
    itemNameArray[2] = "datetime";
    itemNameArray[3] = "devname";
    itemNameArray[4] = "devtype";
    itemNameArray[5] = "data_type";
    itemNameArray[6] = "data_subtype";
    itemNameArray[7] = "data_content";

    //字段类型、字段约束、字段描述等其他信息
    itemOtherArray[0] = "int(11) NOT NULL AUTO_INCREMENT";
    itemOtherArray[1] = "tinyint(4) NOT NULL DEFAULT '0' COMMENT '12345'";
    itemOtherArray[2] = "int(10) unsigned NOT NULL COMMENT '日期时间的格林威治秒数，2018-01-01 12:12:12，省略毫秒'";
    itemOtherArray[3] = "varchar(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '设备名'";
    itemOtherArray[4] = "char(4) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '设备类型 4字节定长'";
    itemOtherArray[5] = "tinyint(4) DEFAULT '0' COMMENT '信息类型'";
    itemOtherArray[6] = "tinyint(4) DEFAULT '0' COMMENT '信息子类型'";
    itemOtherArray[7] = "varchar(1024) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '信息内容'";

    //表中的其他约束等信息(主键、索引、外键等设置)
    tableOther = "PRIMARY KEY (id),KEY datetime (datetime),KEY devname (devname),KEY data_subtype (data_subtype)";

    //位于create table括号之外的额外添加信息(引擎设置、字符集设置等)
    outtableOther = "ENGINE=MyISAM AUTO_INCREMENT=0 DEFAULT CHARSET=utf8";


    currentDateTime.setDate(QDate(startDate.mid(0,4).toInt(),startDate.mid(4,2).toInt(),startDate.mid(6,2).toInt()));
    currentDateTime.setTime(QTime(startDate.mid(8,2).toInt(),startDate.mid(10,2).toInt(),startDate.mid(12,2).toInt(),0));
    return true;
}

bool Dialog::connectDB()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);
    bool ok = db.open();
    return ok;
}

bool Dialog::query(QString sql)
{
    QSqlQuery sqlQueryTemp(db);
    sqlResult = sqlQueryTemp.exec(sql);
    sqlQuery = sqlQueryTemp;
    return sqlResult;
}

void Dialog::mylog(QString log)
{
    ui->textLog->append(log);
}

QString Dialog::calTableName()
{
    QString currentDateTimeStr = currentDateTime.toString(TableNameFormat);
    if(period == TIME_1_MINUTE)//1分钟
    {
        currentDateTime = currentDateTime.addSecs(60);
    }
    else if(period == TIME_2_MINUTE)//2分钟
    {
        currentDateTime = currentDateTime.addSecs(120);
    }
    else if(period == TIME_3_MINUTE)//3分钟
    {
        currentDateTime = currentDateTime.addSecs(180);
    }
    else if(period == TIME_4_MINUTE)//4分钟
    {
        currentDateTime = currentDateTime.addSecs(240);
    }
    else if(period == TIME_5_MINUTE)//5分钟
    {
        currentDateTime = currentDateTime.addSecs(300);
    }
    else if(period == TIME_10_MINUTE)//10分钟
    {
        currentDateTime = currentDateTime.addSecs(600);
    }
    else if(period == TIME_15_MINUTE)//15分钟
    {
        currentDateTime = currentDateTime.addSecs(900);
    }
    else if(period == TIME_20_MINUTE)//20分钟
    {
        currentDateTime = currentDateTime.addSecs(1200);
    }
    else if(period == TIME_30_MINUTE)//30分钟
    {
        currentDateTime = currentDateTime.addSecs(1800);
    }
    else if(period == TIME_1_HOUR)//1小时
    {
        currentDateTime = currentDateTime.addSecs(3600);
    }
    else if(period == TIME_2_HOUR)//2小时
    {
        currentDateTime = currentDateTime.addSecs(7200);
    }
    else if(period == TIME_3_HOUR)//3小时
    {
        currentDateTime = currentDateTime.addSecs(10800);
    }
    else if(period == TIME_4_HOUR)//4小时
    {
        currentDateTime = currentDateTime.addSecs(14400);
    }
    else if(period == TIME_5_HOUR)//5小时
    {
        currentDateTime = currentDateTime.addSecs(18000);
    }
    else if(period == TIME_6_HOUR)//6小时
    {
        currentDateTime = currentDateTime.addSecs(21600);
    }
    else if(period == TIME_10_HOUR)//10小时
    {
        currentDateTime = currentDateTime.addSecs(36000);
    }
    else if(period == TIME_12_HOUR)//12小时
    {
        currentDateTime = currentDateTime.addSecs(43200);
    }
    else if(period == TIME_1_DAY)//1天
    {
        currentDateTime = currentDateTime.addDays(1);
    }
    else if(period == TIME_2_DAY)//2天
    {
        currentDateTime = currentDateTime.addDays(2);
    }
    else if(period == TIME_3_DAY)//3天
    {
        currentDateTime = currentDateTime.addDays(3);
    }
    else if(period == TIME_5_DAY)//5天
    {
        currentDateTime = currentDateTime.addDays(5);
    }
    else if(period == TIME_10_DAY)//10天
    {
        currentDateTime = currentDateTime.addDays(10);
    }
    else if(period == TIME_15_DAY)//15天
    {
        currentDateTime = currentDateTime.addDays(15);
    }
    else if(period == TIME_1_EWEEK)//1周
    {
        currentDateTime = currentDateTime.addDays(7);
    }
    else if(period == TIME_2_WEEK)//2周
    {
        currentDateTime = currentDateTime.addDays(14);
    }
    else if(period == TIME_1_MONTH)//1个月
    {
        currentDateTime = currentDateTime.addMonths(1);
    }
    else if(period == TIME_2_MONTH)//2个月
    {
        currentDateTime = currentDateTime.addMonths(2);
    }
    else if(period == TIME_3_MONTH)//3个月
    {
        currentDateTime = currentDateTime.addMonths(3);
    }
    else if(period == TIME_4_MONTH)//4个月
    {
        currentDateTime = currentDateTime.addMonths(4);
    }
    else if(period == TIME_6_MONTH)//6个月
    {
        currentDateTime = currentDateTime.addMonths(6);
    }
    else if(period == TIME_1_YEAR)//1年
    {
        currentDateTime = currentDateTime.addYears(1);
    }
    else if(period == TIME_2_YEAR)//2年
    {
        currentDateTime = currentDateTime.addYears(2);
    }
    else if(period == TIME_3_YEAR)//3年
    {
        currentDateTime = currentDateTime.addYears(3);
    }
    else if(period == TIME_4_YEAR)//4年
    {
        currentDateTime = currentDateTime.addYears(4);
    }
    else if(period == TIME_5_YEAR)//5年
    {
        currentDateTime = currentDateTime.addYears(5);
    }
    else if(period >= 0)//其他正常指定的情况(单位:秒)
    {
        currentDateTime = currentDateTime.addSecs(period);
    }
    else//其他未定义的负数，可用于扩展添加实现自己分表逻辑的代码
    {
        //TODO
    }
    return TableNamePerfix + currentDateTimeStr;
}

int Dialog::randInt(int min,int max)
{
    return (qrand()%(max-min+1))+min;
}

QString Dialog::randValue(QString data[],int rangeMin,int rangeMax)
{
    int randIndex = randInt(rangeMin,rangeMax);
    return data[randIndex];
}

QString Dialog::randQString(int length)
{
    QString allStr = "abcdefghijklmnopqrstuvwxzyABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    QString randStr = "";
    int allStrLength = allStr.length();
    int i;
    int randIndex;
    for(i=0;i<length;i++)
    {
        randIndex = randInt(0,allStrLength-1);
        randStr.append(allStr.at(randIndex));
    }
    return randStr;
}

bool Dialog::createTable(QString tableName)
{
    if(NumberOfItems == 0)
    {
        return true;
    }
    QString sql = "";
    bool createTable_sqlResult = false;
    int i;
    sql += "CREATE TABLE " + tableName + " (";
    sql += itemNameArray[0];
    sql += " " + itemOtherArray[0];
    for(i=1;i<NumberOfItems;i++)
    {
        sql += "," + itemNameArray[i];
        sql += " " + itemOtherArray[i];
    }
    if(!tableOther.trimmed().isEmpty())
    {
        sql += "," + tableOther.trimmed();
    }
    sql += ")";
    if(!outtableOther.trimmed().isEmpty())
    {
        sql += outtableOther.trimmed();
    }
    sql += ";";
    createTable_sqlResult = query(sql);
    return createTable_sqlResult;
}

bool Dialog::insertItem(QString tableName)
{
    if(NumberOfRecords == 0)
    {
        return true;
    }
    QString sql = "";
    bool insertItem_sqlResult = false;
    int i;
    sql += "LOCK TABLES " + tableName + " WRITE;";
    sql += "INSERT INTO "+ tableName + " (" + itemNameArray[1];//第1列是id列，不需要产生随机数，会自加
    for(i=2;i<NumberOfItems;i++)
    {
        sql += "," + itemNameArray[i];
    }
    sql += ") VALUES (";
    sql += QString::number(randInt(1,5),10);
    sql += "," + QString::number(randInt(1,32767)*randInt(1,32767),10);
    sql += ",'" + randQString(randInt(1,30)) + "'";
    sql += ",'" + randValue(devtype,0,9) + "'";
    sql += "," + QString::number(randInt(0,255),10);
    sql += "," + QString::number(randInt(0,255),10);
    sql += ",'" + randQString(randInt(1,1024)) + "'";
    sql += ");UNLOCK TABLES;";
    insertItem_sqlResult = query(sql);
    return insertItem_sqlResult;
}

void Dialog::on_btnStart_clicked()
{
    ui->btnStart->setEnabled(false);
    mylog("正在创建......");
    QString tableName = "";
    int i,j;
    bool creatTableResult = false;
    for(i=0;i<NumberOfTables;i++)
    {
        tableName = calTableName();
        creatTableResult = createTable(tableName);
        if(creatTableResult)//创建表成功
        {
            mylog(tableName + "表创建成功");
            for(j=0;j<NumberOfRecords;j++)
            {
                insertItem(tableName);
            }
        }
        else//创建表失败
        {
            mylog(tableName + "表创建失败");
        }
    }
    mylog("创建完成!");
    mylog("注意:如要重新生成测试表，请关闭此程序重新打开，否则再次点击开始按钮，将按照当前生成的日期当前设置的间隔继续往后生成，将不再是以最初设置的开始时间开始分表!");
    ui->btnStart->setEnabled(true);
}
