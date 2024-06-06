#include "newwindow.h"
#include "mainwindow.h"
NewWindow:: NewWindow(){};
NewWindow:: NewWindow(QWidget *parent) : QWidget(parent) {
    // 设置窗口标题

}
NewWindow:: ~NewWindow() {
    // 删除布局，它会自动删除所有子控件
    delete mainLayout;
}

void NewWindow::show_one( QStringList &headerText)
{
    setWindowTitle("策略窗口");

    // 创建垂直布局
    mainLayout = new QVBoxLayout(this);
    for(int i=0;i<headerText.size();i+=2){
        layout = new QHBoxLayout(this);
        QLabel *label = new QLabel(headerText.at(i), this);
        layout->addWidget(label);
        QLabel *lable1=new QLabel(headerText.at(i+1), this);
        layout->addWidget(lable1);
        mainLayout->addLayout(layout);
    }
    layout = new QHBoxLayout(this);
    QPushButton *button1 = new QPushButton("确认");
    layout->addWidget(button1);
    mainLayout->addLayout(layout);
    connect(button1, &QPushButton::clicked, this, &QWidget::close);
    // 设置布局为窗口的布局
    setLayout(mainLayout);
}

void NewWindow::show_newwindows(QStringList &headerText, std::vector<strategy_*>& Strategy_,std::function<void(void)>it)
{
    setWindowTitle("增加策略");
    mainLayout = new QVBoxLayout(this);
    layout = new QHBoxLayout(this);
    QLabel *label = new QLabel(headerText.at(0), this);
    layout->addWidget(label);
    QComboBox *comboBox = new QComboBox();
    comboBox->addItem(QString("SSE"));
    comboBox->addItem(QString("SEZE"));
    layout->addWidget(comboBox);
    mainLayout->addLayout(layout);
    std::vector<QLineEdit*>LineEdit;
    for(int i=1;i<21;i++){
        layout = new QHBoxLayout(this);
        label = new QLabel(headerText.at(i), this);
        layout->addWidget(label);
        QLineEdit *edit0=new QLineEdit();
        layout->addWidget(edit0);
        mainLayout->addLayout(layout);
        LineEdit.push_back(edit0);
    }
    layout = new QHBoxLayout(this);
    QPushButton *button1 = new QPushButton("取消");
    layout->addWidget(button1);
    QPushButton *button2 = new QPushButton("确认");
    layout->addWidget(button2);
    mainLayout->addLayout(layout);
    connect(button1, &QPushButton::clicked, this,[&](){
        this->close();
    } );
    connect(button2, &QPushButton::clicked, this, [=,&Strategy_](){
        std::string exchangeID=comboBox->currentText().toStdString();
        int buyTriggerVolume=LineEdit[0]->text().toInt();
        int cancelVolume=LineEdit[1]->text().toInt();
        int position=LineEdit[2]->text().toInt();
        int targetPosition=LineEdit[3]->text().toInt();
        int currPosition=LineEdit[4]->text().toInt();
        int maxTriggerTimes=LineEdit[5]->text().toInt();
        std::string id=LineEdit[6]->text().toStdString();
        int status=LineEdit[7]->text().toInt();
        std::string orderID=LineEdit[8]->text().toStdString();
        std::string securityName=LineEdit[9]->text().toStdString();
        int scoutBuyTriggerCashLim=LineEdit[10]->text().toInt();
        float cond2Percent=LineEdit[11]->text().toFloat();
        int cancelTriggerVolumeLarge=LineEdit[12]->text().toInt();
        int scoutStatus=LineEdit[13]->text().toInt();
        long long int lowerTimeLimit=LineEdit[14]->text().toLongLong();
        long long int scoutMonitorDuration=LineEdit[15]->text().toLongLong();
        long long int cond2HighTime=LineEdit[16]->text().toLongLong();
        long long int cond2TrackDuration=LineEdit[17]->text().toLongLong();
        long long int cond4LowTime=LineEdit[18]->text().toLongLong();
        long long int cond4HighTime=LineEdit[19]->text().toLongLong();
        strategy_*st=new strategy_1(
            exchangeID, buyTriggerVolume, cancelVolume,
            position, targetPosition, currPosition, maxTriggerTimes, std::string(id),
            status, std::string(orderID), std::string(securityName), scoutBuyTriggerCashLim,
            cond2Percent, cancelTriggerVolumeLarge, scoutStatus, lowerTimeLimit,
            scoutMonitorDuration, cond2HighTime, cond2TrackDuration,
            cond4LowTime, cond4HighTime);
        Strategy_.push_back(st);
        st->sout();
        it();
        this->close();
    });
    setLayout(mainLayout);
}
void  NewWindow::create_table(QTableWidget *tableWidget,int x,strategy_1&s){
    QTableWidgetItem *item=new QTableWidgetItem("选中",1000);
    item->setCheckState(Qt::Checked);
    tableWidget->setItem(x,0,item);
    // item=new QTableWidgetItem(QString::fromStdString(s.ID),IndexID+1000);
    // tableWidget->setItem(x,IndexID,item);
    item=new QTableWidgetItem(QString::fromStdString(s.SecurityID),IndexSecurityID+1000);
    tableWidget->setItem(x,1,item);
    // item=new QTableWidgetItem(QString::fromStdString(s.SecurityName),IndexSecurityName+1000);
    // tableWidget->setItem(x,IndexSecurityName,item);
    item=new QTableWidgetItem(QString::fromStdString(s.ExchangeID=="1"?"SSZ":"SEZE"),IndexExchangeID+1000);
    tableWidget->setItem(x,2,item);
    item=new QTableWidgetItem(QString::number(s.BuyTriggerVolume),IndexBuyTriggerVolume+1000);
    tableWidget->setItem(x,3,item);
    item=new QTableWidgetItem(QString::number(s.Position),IndexPosition+1000);
    tableWidget->setItem(x,4,item);
    item=new QTableWidgetItem(QString::number(s.CancelVolume),IndexCancelVolume+1000);
    tableWidget->setItem(x,5,item);
    // item=new QTableWidgetItem(QString::number(s.TargetPosition),IndexTargetPosition+1000);
    // tableWidget->setItem(x,IndexTargetPosition,item);
    // item=new QTableWidgetItem(QString::number(s.CurrPosition),IndexCurrPosition+1000);
    // tableWidget->setItem(x,IndexCurrPosition,item);
    // item=new QTableWidgetItem(QString::fromStdString(s.OrderID),IndexOrderID+1000);
    // tableWidget->setItem(x,IndexOrderID,item);
    item=new QTableWidgetItem(QString::number(s.LowerTimeLimit),IndexLowerTimeLimit+1000);
    tableWidget->setItem(x,6,item);
    item=new QTableWidgetItem(QString::number(s.MaxTriggerTimes),IndexMaxTriggerTimes+1000);
    tableWidget->setItem(x,7,item);
    //item=new QTableWidgetItem(QString::number(s.Status),IndexStatus+1000);
    // tableWidget->setItem(x,IndexStatus,item);
    // item=new QTableWidgetItem(QString::number(s.Count),IndexCount+1000);
    //tableWidget->setItem(x,IndexCount,item);
    //item=new QTableWidgetItem(QString::number(s.ScoutStatus),IndexScoutStatus+1000);
    //tableWidget->setItem(x,IndexScoutStatus,item);
    item=new QTableWidgetItem(QString::number(s.ScoutBuyTriggerCashLim),IndexScoutBuyTriggerCashLim+1000);
    tableWidget->setItem(x,8,item);
    item=new QTableWidgetItem(QString::number(s.ScoutMonitorDuration),IndexScoutMonitorDuration+1000);
    tableWidget->setItem(x,9,item);
    item=new QTableWidgetItem(QString::number(s.Cond2Percent),IndexCond2Percent+1000);
    tableWidget->setItem(x,10,item);
    item=new QTableWidgetItem(QString::number(s.Cond2HighTime),IndexCond2HighTime+1000);
    tableWidget->setItem(x,11,item);
    item=new QTableWidgetItem(QString::number(s.Cond2TrackDuration),IndexCond2TrackDuration+1000);
    tableWidget->setItem(x,12,item);
    item=new QTableWidgetItem(QString::number(s.CancelTriggerVolumeLarge),IndexCancelTriggerVolumeLarge+1000);
    tableWidget->setItem(x,13,item);
    item=new QTableWidgetItem(QString::number(s.Cond4LowTime),IndexCond4LowTime+1000);
    tableWidget->setItem(x,14,item);
    item=new QTableWidgetItem(QString::number(s.Cond4HighTime),IndexCond4HighTime+1000);
    tableWidget->setItem(x,15,item);
}
void  NewWindow::setItem(QTableWidget *tableWidget)//设置表格标题
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText<<"选中"<<"股票代码"<<"交易所"<<"封单额"<<"撤单额"<<"目标仓位(元)"<<"延迟触发"<<"大单延迟时间"<<"保护单触发金额"<<"保护单监控区间"<<"撤单动量比例"<<"撤单动量监控时间"<<"撤单动量时间区间"<<"大单大撤单金额"<<"大单大撤单开始时间"<<"大单大撤单结束时间";
    tableWidget->setColumnCount(16);
    for(int i=0;i<tableWidget->columnCount();i++){
        headerItem=new QTableWidgetItem(headerText.at(i));
        tableWidget->setHorizontalHeaderItem(i,headerItem);
    }

}
void NewWindow::show_table(std::vector<strategy_*>&S,Client &CL){
    QVBoxLayout *layout = new QVBoxLayout(this);
    QTableWidget *tableWidget=new  QTableWidget();
    // 创建一个按钮
    QPushButton *button = new QPushButton("确认");
    // 创建垂直布局管理器
    tableWidget->setRowCount(S.size());

    setItem(tableWidget);
    for(int i=0;i<S.size();i++){
        create_table(tableWidget,i,*(strategy_1*)S[i]);
    }
    setWindowTitle("Table and Button Example");
    connect(button,&QPushButton::clicked, this, [=,&CL](){
        json son_message;
        son_message["request_type"]="group_add_strategy";
        son_message["payload"]=nlohmann::json::array();
        for(int i=0;i<S.size();i++){
            if(tableWidget->item(i,0)->checkState()){
                son_message["payload"].push_back( S[i]->to_json((*(strategy_1*)S[i]).SecurityID));
            }
        }
        CL.send(son_message);
        close();
    });
    layout->addWidget(tableWidget);
    layout->addWidget(button);
    setLayout(layout);
}

void NewWindow::show_warn(std::vector<std::string>&S,std::function<void(void)>it)
{
    setWindowTitle("warn");
    mainLayout = new QVBoxLayout(this);
    layout = new QHBoxLayout(this);
    QLabel *label = new QLabel("已经有提交过的策略，是否继续提交?", this);
    layout->addWidget(label);
     mainLayout->addLayout(layout);
    for(int i=0;i<S.size();i++){
        layout = new QHBoxLayout(this);
        QLabel *label = new QLabel(QString::fromStdString(S[i]), this);
        layout->addWidget(label);
        mainLayout->addLayout(layout);
    }
    layout = new QHBoxLayout(this);
    QPushButton *button1 = new QPushButton("确认");
     QPushButton *button2 = new QPushButton("取消");
    layout->addWidget(button1);
     layout->addWidget(button2);
    mainLayout->addLayout(layout);
     connect(button1, &QPushButton::clicked, this, [=](){
        it();
        close();
    });
    connect(button2,&QPushButton::clicked, this, &QWidget::close);
    // 设置布局为窗口的布局
    setLayout(mainLayout);
}
