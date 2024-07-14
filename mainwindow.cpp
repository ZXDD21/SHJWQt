#include "mainwindow.h"
#include "./ui_mainwindow.h"
std::unordered_map<std::string, int>MainWindow:: dataMap={
    {"ID",1},{"S_id",1},{"SecurityID",2},{"SecurityName",3},{"BuyTriggerVolume",4},{"volume_before_strate",5},{"fengban_volume",6},{"TargetPosition",7},{"CurrPosition",8},{"formal_status",9},{"scout_status",10},{"Status",9},{"ScoutStatus",10},{"FormalOrderAcptTime",11},{"order_trigger_time",11},{"formal_trigger_times",12},{"MaxTriggerTimes",12},{"trade_volume",13},{"scout_trigger_times",14},
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),CL()
{
    logger=new DailyLogger("LOG/");
    logger->log("\n");
    logger->log(get_now_time()+"log init successful");
    CL.url=geturl();
    std::thread tha(std::bind(&MainWindow::ClientRun,this));
    Strategy_=deserializeStrategyFromFile(FILE);
    Sleep(3000);
    ui->setupUi(this);
    showstrategy_();
    ui->label->setText(QString::fromStdString("事件驱动策略管理系统   "+CL.url));
    logger->log(get_now_time()+"client start successful");
    tha.detach();
}
MainWindow::~MainWindow()
{
    serializeStrategyToFile(Strategy_,FILE);
    saveurl();
    delete ui;
}

void MainWindow::ClientRun(){
    logger->log(get_now_time()+"start thread to run  newwork");
    this->CL.Client_Init(std::function<void(void*)>(std::bind(&MainWindow::recive,this,std::placeholders::_1)));
}
void MainWindow::recive(void*ptr){//接受函数,当收到json包且有type类型时，自动调用
    json event_to_send = *(json*)(ptr);
    std::cout<<event_to_send<<std::endl;
    logger->log(get_now_time()+" recive "+event_to_send["type"].get<std::string>());
    std::string type = event_to_send["type"].get<std::string>();
    if(type=="check_runningStrategy"){
        getstrategy(event_to_send);
    }
    else if(type =="check_removedStrategy"){
        //removestategy(event_to_send);
    }
    else if(type=="update_volume"){
        if(uiHasBeenDisplayed==false)return;
        getvolume(event_to_send);
    }
    else if(type=="FORMAL_ORDER_CANCELED"){
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_ORDER_CANCELED(event_to_send);
    }
    else if(type=="SCOUT_ORDER_CANCELED"){
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_ORDER_CANCELED(event_to_send);
    }
    else if (type == "SCOUT_ORDER_SUCCESS") {
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_ORDER_SUCCESS(event_to_send);
    }
    else if (type == "FORMAL_ORDER_SUCCESS") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_ORDER_SUCCESS(event_to_send);
    } else if (type == "SCOUT_CANCEL_SUCCESS") {
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_CANCEL_SUCCESS(event_to_send);
    } else if (type == "FORMAL_CANCEL_SUCCESS") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_CANCEL_SUCCESS(event_to_send);
    } else if (type == "SCOUT_ORDER_ERROR") {
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_ORDER_ERROR(event_to_send);
    } else if (type == "FORMAL_ORDER_ERROR") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_ORDER_ERROR(event_to_send);
    } else if (type == "SCOUT_CANCEL_ERROR") {
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_CANCEL_ERROR(event_to_send);
    } else if (type == "FORMAL_CANCEL_ERROR") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_CANCEL_ERROR(event_to_send);
    } else if (type == "FORMAL_PART_TRADE") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_PART_TRADE(event_to_send);
    } else if (type == "FORMAL_FULLY_TRADE") {
        if(uiHasBeenDisplayed==false)return;
        getFORMAL_FULLY_TRADE(event_to_send);
    } else if (type == "SCOUT_TRADE") {
        if(uiHasBeenDisplayed==false)return;
        getSCOUT_TRADE(event_to_send);
    }
}
void MainWindow::createTableRow(int x, strategy &s,int choice,int len)
{
    if(choice==0){
        QTableWidgetItem *item=new QTableWidgetItem("选中",1000);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(x,0,item);
        item=new QTableWidgetItem(QString::fromStdString(s.ID),IndexID+1000);
        ui->tableWidget->setItem(x,dataMap["ID"],item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityID),IndexSecurityID+1000);
        ui->tableWidget->setItem(x,dataMap["SecurityID"],item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityName),IndexSecurityName+1000);
        ui->tableWidget->setItem(x,dataMap["SecurityName"],item);
        item=new QTableWidgetItem(QString::number(s.TargetPosition),IndexTargetPosition+1000);
        ui->tableWidget->setItem(x,dataMap["TargetPosition"],item);
        item=new QTableWidgetItem(QString::number(s.CurrPosition),IndexCurrPosition+1000);
        ui->tableWidget->setItem(x,dataMap["CurrPosition"],item);
        item=new QTableWidgetItem(QString::number(s.MaxTriggerTimes),IndexMaxTriggerTimes+1000);
        ui->tableWidget->setItem(x,dataMap["MaxTriggerTimes"],item);
        item=new  QTableWidgetItem(QString::fromStdString(s.FormalOrderAcptTime),IndexMaxTriggerTimes+1000);
        ui->tableWidget->setItem(x,dataMap["FormalOrderAcptTime"],item);
        item=new QTableWidgetItem(QString::number(s.BuyTriggerVolume),IndexBuyTriggerVolume+1000);
        ui->tableWidget->setItem(x,dataMap["BuyTriggerVolume"],item);
        int sta=s.Status;
        std::string Sta;
        switch(sta){
            case 0: Sta="运行中";break;
            case 1: Sta="已委托";break;
            case 2:Sta="已撤单";break;
            case 3: Sta="全部成交";break;
            case 4:Sta="已停止";break;
            case 5: Sta="撤单异常";break;
            case 6: Sta="已暂停";break;
            case 7: Sta="部分成交";break;
            case -1:Sta= "交易所拒单";break;
        }
            if(sta!=0){
            createTableRow(x,s,2,len);
            }
        item=new QTableWidgetItem(QString::fromStdString(Sta),IndexStatus+1000);
        ui->tableWidget->setItem(x,dataMap["Status"],item);
        int stb=s.ScoutStatus;
        std::string Stb;
        switch(stb){
        case 0: Stb="运行中";break;
        case 1: Stb="已委托";break;
        case 2:Stb="已撤单";break;
        case 3: Stb="撤单异常";break;
        case 4:Stb="成交";break;
        case -1:Stb= "交易所拒单";break;
        }
        item=new QTableWidgetItem(QString::fromStdString(Stb),IndexScoutStatus+1000);
        ui->tableWidget->setItem(x,dataMap["ScoutStatus"],item);
    }
    if(choice==1){
        QTableWidgetItem *item=new QTableWidgetItem("选中",1000);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget_5->setItem(x,0,item);
        item=new QTableWidgetItem(QString::fromStdString(s.ID),IndexID+1000);
        ui->tableWidget_5->setItem(x,IndexID,item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityID),IndexSecurityID+1000);
        ui->tableWidget_5->setItem(x,IndexSecurityID,item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityName),IndexSecurityName+1000);
        ui->tableWidget_5->setItem(x,IndexSecurityName,item);
        item=new QTableWidgetItem(QString::fromStdString(s.ExchangeID=="1"?"SSE":"SZSE"),IndexExchangeID+1000);
        ui->tableWidget_5->setItem(x,IndexExchangeID,item);
        item=new QTableWidgetItem(QString::number(s.BuyTriggerVolume),IndexBuyTriggerVolume+1000);
        ui->tableWidget_5->setItem(x,IndexBuyTriggerVolume,item);
        item=new QTableWidgetItem(QString::number(s.Position),IndexPosition+1000);
        ui->tableWidget_5->setItem(x,IndexPosition,item);
        item=new QTableWidgetItem(QString::number(s.CancelVolume),IndexCancelVolume+1000);
        ui->tableWidget_5->setItem(x,IndexCancelVolume,item);
        item=new QTableWidgetItem(QString::number(s.TargetPosition),IndexTargetPosition+1000);
        ui->tableWidget_5->setItem(x,IndexTargetPosition,item);
        item=new QTableWidgetItem(QString::number(s.CurrPosition),IndexCurrPosition+1000);
        ui->tableWidget_5->setItem(x,IndexCurrPosition,item);
        item=new QTableWidgetItem(QString::fromStdString(s.OrderID),IndexOrderID+1000);
        ui->tableWidget_5->setItem(x,IndexOrderID,item);
        item=new QTableWidgetItem(QString::number(s.LowerTimeLimit),IndexLowerTimeLimit+1000);
        ui->tableWidget_5->setItem(x,IndexLowerTimeLimit,item);
        item=new QTableWidgetItem(QString::number(s.MaxTriggerTimes),IndexMaxTriggerTimes+1000);
        ui->tableWidget_5->setItem(x,IndexMaxTriggerTimes,item);
        item=new QTableWidgetItem(QString::number(s.Status),IndexStatus+1000);
        ui->tableWidget_5->setItem(x,IndexStatus,item);
        item=new QTableWidgetItem(QString::number(s.Count),IndexCount+1000);
        ui->tableWidget_5->setItem(x,IndexCount,item);
        item=new QTableWidgetItem(QString::number(s.ScoutStatus),IndexScoutStatus+1000);
        ui->tableWidget_5->setItem(x,IndexScoutStatus,item);
        item=new QTableWidgetItem(QString::number(s.ScoutBuyTriggerCashLim),IndexScoutBuyTriggerCashLim+1000);
        ui->tableWidget_5->setItem(x,IndexScoutBuyTriggerCashLim,item);
        item=new QTableWidgetItem(QString::number(s.ScoutMonitorDuration),IndexScoutMonitorDuration+1000);
        ui->tableWidget_5->setItem(x,IndexScoutMonitorDuration,item);
        item=new QTableWidgetItem(QString::number(s.Cond2Percent),IndexCond2Percent+1000);
        ui->tableWidget_5->setItem(x,IndexCond2Percent,item);
        item=new QTableWidgetItem(QString::number(s.Cond2HighTime),IndexCond2HighTime+1000);
        ui->tableWidget_5->setItem(x,IndexCond2HighTime,item);
        item=new QTableWidgetItem(QString::number(s.Cond2TrackDuration),IndexCond2TrackDuration+1000);
        ui->tableWidget_5->setItem(x,IndexCond2TrackDuration,item);
        item=new QTableWidgetItem(QString::number(s.CancelTriggerVolumeLarge),IndexCancelTriggerVolumeLarge+1000);
        ui->tableWidget_5->setItem(x,IndexCancelTriggerVolumeLarge,item);
        item=new QTableWidgetItem(QString::number(s.Cond4LowTime),IndexCond4LowTime+1000);
        ui->tableWidget_5->setItem(x,IndexCond4LowTime,item);
        item=new QTableWidgetItem(QString::number(s.Cond4HighTime),IndexCond4HighTime+1000);
        ui->tableWidget_5->setItem(x,IndexCond4HighTime,item);
    }
    else if(choice==2){
        int x=len;
        QTableWidgetItem *item=new QTableWidgetItem("选中",1000);
        item->setCheckState(Qt::Unchecked);
        ui->tableWidget_5->setItem(x,0,item);
        item=new QTableWidgetItem(QString::fromStdString(s.ID),IndexID+1000);
        ui->tableWidget_5->setItem(x,dataMap["ID"],item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityID),IndexSecurityID+1000);
        ui->tableWidget_5->setItem(x,dataMap["SecurityID"],item);
        item=new QTableWidgetItem(QString::fromStdString(s.SecurityName),IndexSecurityName+1000);
        ui->tableWidget_5->setItem(x,dataMap["SecurityName"],item);
        item=new QTableWidgetItem(QString::number(s.TargetPosition),IndexTargetPosition+1000);
        ui->tableWidget_5->setItem(x,dataMap["TargetPosition"],item);
        item=new QTableWidgetItem(QString::number(s.CurrPosition),IndexCurrPosition+1000);
        ui->tableWidget_5->setItem(x,dataMap["CurrPosition"],item);
        item=new QTableWidgetItem(QString::number(s.MaxTriggerTimes),IndexMaxTriggerTimes+1000);
        ui->tableWidget_5->setItem(x,dataMap["MaxTriggerTimes"],item);
        item=new  QTableWidgetItem(QString::fromStdString(s.FormalOrderAcptTime),IndexMaxTriggerTimes+1000);
        ui->tableWidget_5->setItem(x,dataMap["FormalOrderAcptTime"],item);
        item=new QTableWidgetItem(QString::number(s.BuyTriggerVolume),IndexBuyTriggerVolume+1000);
        ui->tableWidget_5->setItem(x,dataMap["BuyTriggerVolume"],item);
        int sta=s.Status;
        std::string Sta;
        switch(sta){
        case 0: Sta="运行中";break;
        case 1: Sta="已委托";break;
        case 2:Sta="已撤单";break;
        case 3: Sta="全部成交";break;
        case 4:Sta="已停止";break;
        case 5: Sta="撤单异常";break;
        case 6: Sta="已暂停";break;
        case 7: Sta="部分成交";break;
        case -1:Sta= "交易所拒单";break;
        }
        item=new QTableWidgetItem(QString::fromStdString(Sta),IndexStatus+1000);
        ui->tableWidget_5->setItem(x,dataMap["Status"],item);
        int stb=s.ScoutStatus;
        std::string Stb;
        switch(stb){
        case 0: Stb="运行中";break;
        case 1: Stb="已委托";break;
        case 2:Stb="已撤单";break;
        case 3: Stb="撤单异常";break;
        case 4:Stb="成交";break;
        case -1:Stb= "交易所拒单";break;
        }
        item=new QTableWidgetItem(QString::fromStdString(Stb),IndexScoutStatus+1000);
        ui->tableWidget_5->setItem(x,dataMap["ScoutStatus"],item);
    }
}
void MainWindow::createTableRow(std::vector<int>choice){
    logger->log(get_now_time()+"createTableRow");
    if(ui->tableWidget->rowCount()==0)return;
    for(int i=0;i<ui->tableWidget->rowCount();i++){
        auto it = event_map.find(ui->tableWidget->item(i,1)->text().toStdString());
        if(it!=event_map.end()){
            for(auto j:choice){
                if(j==dataMap["volume_before_strate"]){
                    QTableWidgetItem *item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget->item(i,1)->text().toStdString()].volume_before_strate/10000)+"万",1000+50);
                    ui->tableWidget->setItem(i,dataMap["volume_before_strate"],item);
                }
                else if(j==dataMap["fengban_volume"]){
                    QTableWidgetItem *item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget->item(i,1)->text().toStdString()].fenban_volume/10000)+"万",51+1000);
                    ui->tableWidget->setItem(i,dataMap["fengban_volume"],item);
                }else if(choice[j]==dataMap["Status"]){
                    QString stab=QString::number(event_map[ui->tableWidget->item(i,1)->text().toStdString()].trade_volume);
                    int sta=stab.toInt();
                    std::string Sta;
                    switch(sta){
                    case 0: Sta="运行中";break;
                    case 1: Sta="已委托";break;
                    case 2:Sta="已撤单";break;
                    case 3: Sta="全部成交";break;
                    case 4:Sta="已停止";break;
                    case 5: Sta="撤单异常";break;
                    case 6: Sta="已暂停";break;
                    case 7: Sta="部分成交";break;
                    case -1:Sta= "交易所拒单";break;
                    }
                     QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(Sta),1000+50+j);
                    ui->tableWidget->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["ScoutStatus"]){
                    QString stab=QString::number(event_map[ui->tableWidget->item(i,1)->text().toStdString()].scout_status);
                    int stb=stab.toInt();
                    std::string Stb;
                    switch(stb){
                    case 0: Stb="运行中";break;
                    case 1: Stb="已委托";break;
                    case 2:Stb="已撤单";break;
                    case 3: Stb="撤单异常";break;
                    case 4:Stb="成交";break;
                    case -1:Stb= "交易所拒单";break;
                    }
                     QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(Stb),1000+50+j);
                    ui->tableWidget->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["formal_trigger_times"]){
                     QTableWidgetItem * item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget->item(i,1)->text().toStdString()].formal_trigger_times),1000+50+j);
                    ui->tableWidget->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["order_trigger_time"]){
                    QTableWidgetItem * item=new QTableWidgetItem(QString::fromStdString(event_map[ui->tableWidget->item(i,1)->text().toStdString()].order_trigger_time),1000+50+j);
                    ui->tableWidget->setItem(i,choice[j],item);
                }
            }
        }
    }
    for(int i=0;i<ui->tableWidget_5->rowCount();i++){
        auto it = event_map.find(ui->tableWidget_5->item(i,1)->text().toStdString());
        if(it!=event_map.end()){
            for(auto j:choice){
                if(j==dataMap["volume_before_strate"]){
                    QTableWidgetItem *item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].volume_before_strate/10000)+"万",1000+50);
                    ui->tableWidget_5->setItem(i,dataMap["volume_before_strate"],item);
                }
                else if(j==dataMap["fengban_volume"]){
                    QTableWidgetItem *item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].fenban_volume/10000)+"万",51+1000);
                    ui->tableWidget_5->setItem(i,dataMap["fengban_volume"],item);
                }else if(choice[j]==dataMap["Status"]){
                    QString stab=QString::number(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].trade_volume);
                    int sta=stab.toInt();
                    std::string Sta;
                    switch(sta){
                    case 0: Sta="运行中";break;
                    case 1: Sta="已委托";break;
                    case 2:Sta="已撤单";break;
                    case 3: Sta="全部成交";break;
                    case 4:Sta="已停止";break;
                    case 5: Sta="撤单异常";break;
                    case 6: Sta="已暂停";break;
                    case 7: Sta="部分成交";break;
                    case -1:Sta= "交易所拒单";break;
                    }
                    QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(Sta),1000+50+j);
                    ui->tableWidget_5->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["ScoutStatus"]){
                    QString stab=QString::number(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].scout_status);
                    int stb=stab.toInt();
                    std::string Stb;
                    switch(stb){
                    case 0: Stb="运行中";break;
                    case 1: Stb="已委托";break;
                    case 2:Stb="已撤单";break;
                    case 3: Stb="撤单异常";break;
                    case 4:Stb="成交";break;
                    case -1:Stb= "交易所拒单";break;
                    }
                    QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(Stb),1000+50+j);
                    ui->tableWidget_5->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["formal_trigger_times"]){
                    QTableWidgetItem * item=new QTableWidgetItem(QString::number(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].formal_trigger_times),1000+50+j);
                    ui->tableWidget_5->setItem(i,choice[j],item);
                }else if(choice[j]==dataMap["order_trigger_time"]){
                    QTableWidgetItem * item=new QTableWidgetItem(QString::fromStdString(event_map[ui->tableWidget_5->item(i,1)->text().toStdString()].order_trigger_time),1000+50+j);
                    ui->tableWidget_5->setItem(i,choice[j],item);
                }
            }
        }
    }
}
void  MainWindow::serializeStrategyToFile(const std::vector<strategy_*>& strategies, const std::string& filename) {//存入文件
    logger->log(get_now_time()+"open file to save strategy");
    std::ofstream file(filename);
    if (!file.is_open()) {
        logger->log(get_now_time()+"file open err");
        return;
    }
    for (const auto& strategy : strategies) {
        //strategy_1* temp_TradeField = static_cast<strategy_1*>(strategy);
        strategy->sout();
        *strategy<<file;
        //file<<strategy;
    }
    logger->log(get_now_time()+"file save successful");
}

void MainWindow::addstrategy_(strategy_* str)
{
    Strategy_.push_back(str);
}

void MainWindow::showstrategy_()//展示获取策略
{

    QLayoutItem *item;

    while ((item = ui->groupBox_3->layout()->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget(); // 删除widget
        } else if (item->layout()) {
            delete item->layout(); // 如果有子布局，也删除
        }
        delete item; // 删除布局项
    }

    QLabel *labda0=new QLabel("批量编辑",ui->groupBox_3);
    ui->gridLayout_3->addWidget(labda0, 0, 0, 1, 1);
    QLabel *labda1=new QLabel("股票代码(6位数字)",ui->groupBox_3);
    ui->gridLayout_3->addWidget(labda1, 1, 0, 1, 1);
    QLineEdit *edit0=new QLineEdit(ui->groupBox_3);
    ui->gridLayout_3->addWidget(edit0, 2, 0, 1, 2);
    std::vector<QPushButton *>Button;
    std::vector<QCheckBox *>CheckBox;
    for(int i=0;i<Strategy_.size();i++){
        QCheckBox *checkBox;
        if(i<this->min_strategy_size){
            checkBox = new QCheckBox(QString("固定策略 ")+QString::number(i),ui->groupBox_3);
        }
        else checkBox = new QCheckBox(QString("策略 ")+QString::number(i),ui->groupBox_3);
        checkBox->setObjectName("checkBox");
        CheckBox.push_back(checkBox);
        ui->gridLayout_3->addWidget(CheckBox[i], 3+i, 0, 1, 1);
        // 创建按钮
        QPushButton *button = new QPushButton("查看", ui->groupBox_3);
        Button.push_back(button);
        ui->gridLayout_3->addWidget(Button[i],3+i,1,1,1);
        connect(Button[i], &QPushButton::clicked, this,[=](){show_txt(Strategy_[i]);});
    }
    QPushButton *ack = new QPushButton("提交", ui->groupBox_3);
    ui->gridLayout_3->addWidget(ack, 3+Strategy_.size(), 0, 1, 2);
    QPushButton *deleteack = new QPushButton("删除", ui->groupBox_3);
    ui->gridLayout_3->addWidget(deleteack, 4+Strategy_.size(), 0, 1, 2);
    connect(deleteack,&QPushButton::clicked,this,[this,CheckBox](){
        int i=0;
        for(auto it=this->Strategy_.begin();it!=this->Strategy_.end();){
            if(i<this->min_strategy_size){++it;}
            else{
                if(CheckBox[i]->checkState()){
                    it=this->Strategy_.erase(it);
                }
                else ++it;
            }
            i++;
        }
        showstrategy_();
    });
    connect(ack,&QPushButton::clicked,this,[=](){
        std::vector<std::string>S;
        for(auto it:Strategy){
            if(it.SecurityID==edit0->text().toStdString()){
                S.push_back(it.ID);
            }
        }
        if(S.size()!=0){
            NewWindow *newWindow = new NewWindow(nullptr);
            newWindow->show_warn(S,[=](){
                json son_message;
                son_message["request_type"]="group_add_strategy";
                son_message["payload"]=nlohmann::json::array();
                for(int i=0;i<this->Strategy_.size();i++){
                    if(CheckBox[i]->checkState()){
                        son_message["payload"].push_back(this->Strategy_[i]->to_json(edit0->text().toStdString()));
                    }
                }
                logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());
                CL.send(son_message);
            });
            newWindow->show();
        }
        else{
            json son_message;
            son_message["request_type"]="group_add_strategy";
            son_message["payload"]=nlohmann::json::array();
            for(int i=0;i<this->Strategy_.size();i++){
                if(CheckBox[i]->checkState()){
                    son_message["payload"].push_back(this->Strategy_[i]->to_json(edit0->text().toStdString()));
                }
            }
            logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());
            CL.send(son_message);
        }
    logger->log(get_now_time()+"main interface build successful");
    });
}
std::vector<strategy_*> MainWindow::deserializeStrategyFromFile(const std::string& filename) {//从文件中读取策略
    logger->log(get_now_time()+"open file to get strategy");
    std::vector<strategy_*> strategies;
    std::ifstream file(filename);
    if (!file.is_open()) {
       logger->log(get_now_time()+"open file err");
        return strategies;
    }
    std::string exchangeID; int buyTriggerVolume;int cancelVolume;
    int position; int targetPosition; int currPosition; int maxTriggerTimes; std::string id;
    int status; std::string orderID; std::string securityName; int scoutBuyTriggerCashLim;
    float cond2Percent;int cancelTriggerVolumeLarge; int scoutStatus; long long int lowerTimeLimit;
    long long int scoutMonitorDuration; long long int cond2HighTime; long long int cond2TrackDuration;
    long long int cond4LowTime; long long int cond4HighTime;
    while (  file >> exchangeID
           >> buyTriggerVolume
           >> cancelVolume
           >> position
           >> targetPosition
           >> currPosition
           >> maxTriggerTimes
           >> id
           >> status
           >> orderID
           >> securityName
           >> scoutBuyTriggerCashLim
           >> cond2Percent
           >> cancelTriggerVolumeLarge
           >> scoutStatus
           >> lowerTimeLimit
           >> scoutMonitorDuration
           >> cond2HighTime
           >> cond2TrackDuration
           >> cond4LowTime
           >> cond4HighTime) {
        strategy_*st=new strategy_1(
            exchangeID, buyTriggerVolume, cancelVolume,
            position, targetPosition, currPosition, maxTriggerTimes, std::string(id),
            status, std::string(orderID), std::string(securityName), scoutBuyTriggerCashLim,
            cond2Percent, cancelTriggerVolumeLarge, scoutStatus, lowerTimeLimit,
            scoutMonitorDuration, cond2HighTime, cond2TrackDuration,
            cond4LowTime, cond4HighTime);
        strategies.push_back(st);
    }


    file.close();
    logger->log(get_now_time()+"open file to get strategy successful");
    return strategies;
}
void MainWindow::setItem(int choice)//设置表格标题
{
    logger->log(get_now_time()+"setItem");
    QTableWidgetItem *headerItem;
    QStringList headerText;

    if(choice==0){
        headerText<<"选中"<<"策略编号"<<"股票代码"<< "股票名称"<<"触发金额"<<"单前金额（万）"<<"封单金额(万)"<<"目标仓位（股)"<<"已买仓位"<<"正式单状态"<<"保护单状态"<<"委托时间"<<"触发次数";
        ui->tableWidget->setColumnCount(13);
        for(int i=0;i<ui->tableWidget->columnCount();i++){
            headerItem=new QTableWidgetItem(headerText.at(i));
            ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
        }
    }
    if(choice==1){
        headerText<<"选中"<<"策略编号"<<"股票代码"<<"股票名称"<<"交易所"<<"封单额"<<"撤单额"<<"目标仓位(元)"<<"目标仓位(股)"<<"已买仓位(股)"<<"策略委托"<<"延迟触发"<<"大单延迟时间"<<"策略状态"<<"撤单次数"<<"保护单状态"<<"保护单触发金额"<<"保护单监控区间"<<"撤单动量比例"<<"撤单动量监控时间"<<"撤单动量时间区间"<<"大单大撤单金额"<<"大单大撤单开始时间"<<"大单大撤单结束时间";
        ui->tableWidget_5->setColumnCount(24);
        for(int i=0;i<ui->tableWidget_5->columnCount();i++){
            headerItem=new QTableWidgetItem(headerText.at(i));
            ui->tableWidget_5->setHorizontalHeaderItem(i,headerItem);
        }
    }
    if(choice==2){
        headerText<<"选中"<<"策略编号"<<"股票代码"<< "股票名称"<<"触发金额"<<"单前金额（万）"<<"封单金额(万)"<<"目标仓位（股)"<<"已买仓位"<<"正式单状态"<<"保护单状态"<<"委托时间"<<"触发次数";
        ui->tableWidget_5->setColumnCount(13);
        for(int i=0;i<ui->tableWidget_5->columnCount();i++){
            headerItem=new QTableWidgetItem(headerText.at(i));
            ui->tableWidget_5->setHorizontalHeaderItem(i,headerItem);
        }
    }

}

void MainWindow::getvolume(json event_to_send)
{
    updata_event_map(event_to_send,{dataMap["volume_before_strate"],dataMap["fengban_volume"]});
    createTableRow({dataMap["volume_before_strate"],dataMap["fengban_volume"]});
}


void MainWindow::updata_event_map(json &event_to_send,std::vector<int>choice)
{
    if(event_map.find(event_to_send["S_id"].get<std::string>())==event_map.end()){
        event_map[event_to_send["S_id"].get<std::string>()]=Event(event_to_send);
    }
    else{
        for(auto &i:event_map){
            if(i.first==event_to_send["S_id"].get<std::string>()){
                for(int j:choice){
                    if (j == dataMap.at("formal_status")) {
                        i.second.formal_status = event_to_send["formal_status"].get<int>();
                    } else if (j == dataMap.at("scout_status")) {
                        i.second.scout_status = event_to_send["scout_status"].get<int>();
                    } else if (j == dataMap.at("trade_volume")) {
                        i.second.trade_volume = event_to_send["trade_volume"].get<int>();
                    } else if (j == dataMap.at("scout_trigger_times")) {
                        i.second.scout_trigger_times = event_to_send["scout_trigger_times"].get<int>();
                    } else if (j == dataMap.at("formal_trigger_times")) {
                        i.second.formal_trigger_times = event_to_send["formal_trigger_times"].get<int>();
                    }else if(j==dataMap.at("volume_before_strate")){
                        i.second.volume_before_strate=event_to_send["volume_before_strate"].get<double>();
                    }else if(j==dataMap.at("fengban_volume")){
                        i.second.fenban_volume=event_to_send["fengban_volume"].get<double>();
                    }
                }
            }
        }
    }
}

void MainWindow:: InittableWidget(int choice){//初始化表格

    if(choice==0){
        ui->tableWidget->clear();
        ui->tableWidget_5->clear();
        setItem(choice);
        setItem(2);
        ui->tableWidget->setRowCount(Strategy.size());
        int count=0;
        for(auto i:Strategy){
            if(i.Status!=0)count++;
        }
        ui->tableWidget_5->setRowCount(count);
        std::list<strategy>::iterator it=Strategy.begin();
        std::vector<strategy> vecStrategy(Strategy.begin(), Strategy.end());

        // 使用 std::sort 对 vector 进行排序
        std::sort(vecStrategy.begin(), vecStrategy.end(),
                  [](const strategy& a, const strategy& b) {
                      int aID = std::stoi(a.ID);
                      int bID = std::stoi(b.ID);
                      return aID < bID;
                  });

        // 将排序后的 vector 复制回 std::list
        Strategy.assign(vecStrategy.begin(), vecStrategy.end());
        int len=-1;
        for(int i=0;i<Strategy.size();i++){
            if(it->Count!=0)len++;
            createTableRow(i,*it,choice,len);
            it++;
        }
        uiHasBeenDisplayed=true;
        createTableRow({dataMap["formal_status"],dataMap["volume_before_strate"],dataMap["fengban_volume"],dataMap["formal_trigger_times"],dataMap["scout_status"],dataMap["order_trigger_time"]});
    }
    else{
        ui->tableWidget_5->clear();
        setItem(choice);
        ui->tableWidget_5->setRowCount(removeStrategy.size());
        std::list<strategy>::iterator it=removeStrategy.begin();
        std::vector<strategy> vecStrategy(removeStrategy.begin(), removeStrategy.end());

        // 使用 std::sort 对 vector 进行排序
        std::sort(vecStrategy.begin(), vecStrategy.end(),
                  [](const strategy& a, const strategy& b) {
                      int aID = std::stoi(a.ID);
                      int bID = std::stoi(b.ID);
                      return aID < bID;
                  });

        // 将排序后的 vector 复制回 std::list
        removeStrategy.assign(vecStrategy.begin(), vecStrategy.end());
        for(int i=0;i<removeStrategy.size();i++){
            createTableRow(i,*it,choice);
            it++;
        }
    }
}


void MainWindow::on_refresh_table_clicked()
{
    json son_message;
    son_message["request_type"]="check_running_strategy";
    son_message["payload"]=nlohmann::json::array();
    logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());
    CL.send(son_message);
}
void MainWindow::on_pushButton_3_clicked()//发送remove包
{
    json son_message;
    son_message["request_type"]="group_remove_strategy";
    son_message["payload"]=nlohmann::json::array();
    std::vector<std::string>count;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if(ui->tableWidget->item(row,0)->checkState()){
            for(auto &temporary_data:Strategy){
                if(temporary_data.ID==ui->tableWidget->item(row,1)->text().toStdString()){
                    count.push_back(temporary_data.ID);
                    std::string SecurityID;//证券代码 1
                    std::string ExchangeID;//交易所 1
                    std::string ID;//策略编号 1
                    json data;
                    data["SecurityID"]=temporary_data.SecurityID;
                    data["ExchangeID"]=std::to_string(temporary_data.ExchangeID=="SSE" ?1:2);
                    data["S_id"]=stoi(temporary_data.ID);
                    son_message["payload"].push_back(data);
                }
            }
        }
    }
    for (int row = 0; row < ui->tableWidget_5->rowCount(); ++row) {
        if(ui->tableWidget_5->item(row,0)->checkState()){
            for(auto &temporary_data:Strategy){
                if(temporary_data.ID==ui->tableWidget_5->item(row,1)->text().toStdString()){
                    if([](std::vector<std::string>a,std::string b)->bool{
                            for(const auto &i:a){
                                if(i==b)return true;
                            }
                            return false;
                        }(count,temporary_data.ID)){
                        continue;
                    }
                    std::string SecurityID;//证券代码 1
                    std::string ExchangeID;//交易所 1
                    std::string ID;//策略编号 1
                    json data;
                    data["SecurityID"]=temporary_data.SecurityID;
                    data["ExchangeID"]=std::to_string(temporary_data.ExchangeID=="SSE" ?1:2);
                    data["S_id"]=stoi(temporary_data.ID);
                    son_message["payload"].push_back(data);
                }
            }
        }
    }
    logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());
    CL.send(son_message);
}


void MainWindow::show_txt(strategy_* st){//展示动态策略的查看按钮
    QStringList headerText;
    st->print(headerText);
    NewWindow *newWindow = new NewWindow(nullptr);
    newWindow->show_one(headerText);
    newWindow->show();
}

void MainWindow::on_pushButton_8_clicked()//查找策略表格
{
    std::string String=ui->lineEdit->text().toStdString();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    int size=0;
    setItem(0);
    for(auto i:Strategy){
        if(String==""||i.SecurityID==String){
            ui->tableWidget->setRowCount(size+1);
            createTableRow(size,i,0);
            ++size;
        }
    }
    createTableRow({dataMap["formal_status"],dataMap["volume_before_strate"],dataMap["fengban_volume"],dataMap["formal_trigger_times"],dataMap["scout_status"],dataMap["order_trigger_time"]});
}
void MainWindow::on_pushButton_11_clicked()//增加策略模板
{
    QStringList headerText;
    NewWindow *newWindow = new NewWindow(nullptr);
    strategy_1::print_chiness(headerText);
    newWindow->show_newwindows(headerText,Strategy_,std::bind(&MainWindow::showstrategy_,this));
    newWindow->show();
}


void MainWindow::on_action_triggered()//打开文件
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("选择 CSV 文件"), "",tr("CSV Files (*.csv)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        std::vector<strategy_*>V;
        bool is_one=true;
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                std::string  str = in.readLine().toStdString();
                char delimiter = ',';
                // 使用 lambda 表达式分割字符串，并显式指定 getline 的模板参数
                auto tokens = [&str, delimiter]() {
                    std::vector<std::string> result;
                    std::istringstream tokenStream(str);
                    std::string token;
                    // 显式指定模板参数为 std::string
                    while (getline(tokenStream, token, delimiter)) {
                        result.push_back(token);
                    }
                    return result;
                }();
                if(is_one){
                    is_one=false;
                    continue;
                }
                //0           1           2                   3               4               5               6                       7                       8               9               10                     11                       12              13              14
                //SecurityID	ExchangeID	BuyTriggerVolume	CancelVolume	MaxTriggerTimes	LowerTimeLimit	ScoutBuyTriggerCashLim	ScoutMonitorDuration	Cond2Percent	Cond2HighTime	Cond2TrackDuration	CancelTriggerVolumeLarge	Cond4LowTime	Cond4HighTime	Position
                strategy_1*stra=new strategy_1(
                    tokens[1], // exchangeID
                    std::stoi(tokens[2]), // buyTriggerVolume
                    std::stoi(tokens[3]), // cancelVolume
                    std::stoi(tokens[14]), // position
                    0, // targetPosition, 假设默认值为0
                    0, // currPosition, 假设默认值为0
                    std::stoi(tokens[4]), // maxTriggerTimes
                    "0", // id, 假设SecurityID用作id
                    0, // status, 假设默认值为0
                    "", // orderID, 假设默认为空字符串
                    "", // securityName, 假设默认为空字符串
                    std::stoi(tokens[6]), // scoutBuyTriggerCashLim
                    std::stof(tokens[8]), // cond2Percent
                    std::stoi(tokens[11]), // cancelTriggerVolumeLarge
                    0, // scoutStatus, 假设默认值为0
                    std::stoll(tokens[5]), // lowerTimeLimit
                    std::stoll(tokens[7]), // scoutMonitorDuration
                    std::stoll(tokens[9]), // cond2HighTime
                    std::stoll(tokens[10]), // cond2TrackDuration
                    std::stoll(tokens[12]), // cond4LowTime
                    std::stoll(tokens[13])  // cond4HighTime
                    );
                stra->SecurityID=tokens[0];
                V.push_back(stra);
            }
            NewWindow *newWindow = new NewWindow(nullptr);
            newWindow-> show_table(V,CL);
            //newWindow->showFullScreen();
            newWindow->resize(600,800);
            newWindow-> show();
            file.close();
        } else {
            qDebug() << "无法打开文件";
        }
        for(auto i:V){
            i->sout();
        }
    }

}

void MainWindow::on_action_2_triggered()//关闭文件
{

    // 设置默认文件名和过滤器
    QString defaultFileName = "newtext.txt";
    QString filter = "Text Files (*.txt);;All Files (*)";
    // 弹出保存文件对话框，并指定默认文件名和过滤器
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Save As",
        QDir::homePath() + QDir::separator() + defaultFileName,
        filter
        );
    // 检查用户是否取消了对话框
    if (fileName.isEmpty()) {
        qDebug() << "Save operation canceled by user.";
        return;
    }

    // 如果用户没有指定文件名，则使用默认文件名
    if (fileName.contains(defaultFileName) && !fileName.contains(QDir::separator())) {
        fileName = QDir::homePath() + QDir::separator() + defaultFileName;
    }

    // 检查文件是否已存在
    QFile file(fileName);
    if (file.exists()) {
        // 如果文件存在，可以提示用户文件将被覆盖
        // 这里简单打印一条消息，实际应用中可能需要更复杂的逻辑
        qDebug() << "The file already exists and will be overwritten.";
    }

    // 打开文件进行写入
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 写入数据
        QTextStream out(&file);
        QString S="";
        out<<"运行策略\n";
        /*for(auto i:Strategy){
            out<<i;
        }*/
        // 遍历所有行
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            // 遍历所有列
            for (int column = 1; column < ui->tableWidget->columnCount(); ++column) {
                // 获取当前单元格的项
                QTableWidgetItem *item = ui->tableWidget->item(row, column);
                if (item) {
                    // 打印当前单元格的文本
                    S+=item->text();
                    S+=' ';
                }
            }
            S+='\n';
        }
        out << S;

        // 关闭文件
        file.close();
        qDebug() << "File saved successfully:" << fileName;
    } else {
        // 打开文件失败
        qDebug() << "Failed to open the file for writing:" << fileName;
    }


}

void MainWindow::getstrategy(json data)
{

    Strategy.clear();
    for (auto& item : data["payload"]) {
        std::string secID = item["SecurityID"].get<std::string>();
        // 用类似的方式获取其他字段的值
        std::string exID = item["ExchangeID"].get<std::string>();
        std::string ordID = item["OrderID"].get<std::string>();
        std::string secName = item["SecurityName"].get<std::string>();
        std::string stratID = item["ID"].get<std::string>();
        int buyVol = item["BuyTriggerVolume"].get<int>();
        int canVol = item["CancelVolume"].get<int>();
        int pos = item["Position"].get<int>();
        int targPos = item["TargetPosition"].get<int>();
        int currPos = item["CurrPosition"].get<int>();
        int lowTimeLim = item["LowerTimeLimit"].get<int>();
        int maxTrigTimes = item["MaxTriggerTimes"].get<int>();
        int stat = item["Status"].get<int>();
        int cnt = item["MaxTriggerTimes"].get<int>(); // 假设Count是存在的字段
        int scoutStat = item["ScoutStatus"].get<int>();
        int scoutBuyTrigCashLim = item["ScoutBuyTriggerCashLim"].get<int>();
        long long int scoutMonDur = item["ScoutMonitorDuration"].get<long long int>();
        float cond2Perc = item["Cond2Percent"].get<float>();
        long long int cond2HighTime = item["Cond2HighTime"].get<long long int>();
        long long int cond2TrackDur = item["Cond2TrackDuration"].get<long long int>();
        int canTrigVolLrg = item["CancelTriggerVolumeLarge"].get<int>();
        long long int cond4LowTime = item["Cond4LowTime"].get<long long int>();
        long long int cond4HighTime = item["Cond4HighTime"].get<long long int>();
        std::string formal=item["FormalOrderAcptTime"].get<std::string>();
        strategy newStrategy(
            secID, exID, ordID, secName, stratID,
            buyVol, canVol, pos, targPos, currPos,
            lowTimeLim, maxTrigTimes, stat, cnt,
            scoutStat, scoutBuyTrigCashLim, scoutMonDur,cond2Perc,cond2HighTime,cond2TrackDur, canTrigVolLrg,cond4LowTime,cond4HighTime,formal
            );
        Strategy.push_back(newStrategy);
    }
    InittableWidget(0);
}
void MainWindow:: removestategy(json data){
    removeStrategy.clear();
    for (auto& item : data["payload"]) {
        std::string secID = item["SecurityID"].get<std::string>();
        // 用类似的方式获取其他字段的值
        std::string exID = item["ExchangeID"].get<std::string>();
        std::string ordID = item["OrderID"].get<std::string>();
        std::string secName = item["SecurityName"].get<std::string>();
        std::string stratID = item["ID"].get<std::string>();;
        int buyVol = item["BuyTriggerVolume"].get<int>();
        int canVol = item["CancelVolume"].get<int>();
        int pos = item["Position"].get<int>();
        int targPos = item["TargetPosition"].get<int>();
        int currPos = item["CurrPosition"].get<int>();
        int lowTimeLim = item["LowerTimeLimit"].get<int>();
        int maxTrigTimes = item["MaxTriggerTimes"].get<int>();
        int stat = item["Status"].get<int>();
        int cnt = item["MaxTriggerTimes"].get<int>(); // 假设Count是存在的字段
        int scoutStat = item["ScoutStatus"].get<int>();
        int scoutBuyTrigCashLim = item["ScoutBuyTriggerCashLim"].get<int>();
        long long int scoutMonDur = item["ScoutMonitorDuration"].get<long long int>();
        float cond2Perc = item["Cond2Percent"].get<float>();
        long long int cond2HighTime = item["Cond2HighTime"].get<long long int>();
        long long int cond2TrackDur = item["Cond2TrackDuration"].get<long long int>();
        int canTrigVolLrg = item["CancelTriggerVolumeLarge"].get<int>();
        long long int cond4LowTime = item["Cond4LowTime"].get<long long int>();
        long long int cond4HighTime = item["Cond4HighTime"].get<long long int>();
        std::string formal=item["FormalOrderAcptTime"].get<std::string>();
        strategy newStrategy(
            secID, exID, ordID, secName, stratID,
            buyVol, canVol, pos, targPos, currPos,
            lowTimeLim, maxTrigTimes, stat, cnt,
            scoutStat, scoutBuyTrigCashLim, scoutMonDur,cond2Perc,cond2HighTime,cond2TrackDur, canTrigVolLrg,cond4LowTime,cond4HighTime,formal
            );
        removeStrategy.push_back(newStrategy);
    }
    InittableWidget(1);
}

std::string MainWindow::geturl()
{
    logger->log(get_now_time()+"open ip_file and change ip");
    std::ifstream file("IP.txt");
    if (!file.is_open()) {
        logger->log(get_now_time()+"open ip_file err");
        return std::string("ws://45.125.34.103:8765");
    }
    std::string url;
    file>>url;
    return url;
    logger->log(get_now_time()+"open ip_file and change ip successful");
}
void MainWindow::getFORMAL_ORDER_SUCCESS(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["scout_status"],dataMap["order_trigger_time"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["scout_status"],dataMap["order_trigger_time"]});
}

void MainWindow::getFORMAL_ORDER_CANCELED(json event_to_send)
{
    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["scout_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["scout_status"]});
}
void MainWindow::getSCOUT_ORDER_SUCCESS(json event_to_send){
    updata_event_map(event_to_send,{dataMap["scout_status"]});
    createTableRow({dataMap["scout_status"]});
}

void MainWindow::getSCOUT_ORDER_CANCELED(json event_to_send)
{
    updata_event_map(event_to_send,{dataMap["scout_status"]});
    createTableRow({dataMap["scout_status"]});
}


void MainWindow::getSCOUT_CANCEL_SUCCESS(json event_to_send){
    updata_event_map(event_to_send,{dataMap["scout_status"]});
    createTableRow({dataMap["scout_status"]});
}

void MainWindow::getFORMAL_CANCEL_SUCCESS(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["scout_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["scout_status"]});
}

void MainWindow::getSCOUT_ORDER_ERROR(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_status"]});
    createTableRow({dataMap["formal_status"]});
}

void MainWindow::getFORMAL_ORDER_ERROR(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["scout_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["scout_status"]});
}

void    MainWindow::getSCOUT_CANCEL_ERROR(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_status"]});
    createTableRow({dataMap["formal_status"]});
}

void    MainWindow::getFORMAL_CANCEL_ERROR(json event_to_send){
    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["scout_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["scout_status"]});
}

void    MainWindow::getFORMAL_PART_TRADE(json event_to_send){

    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["formal_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["formal_status"]});
}

void    MainWindow::getFORMAL_FULLY_TRADE(json event_to_send){

    updata_event_map(event_to_send,{dataMap["formal_trigger_times"],dataMap["formal_status"]});
    createTableRow({dataMap["formal_trigger_times"],dataMap["formal_status"]});
}

void   MainWindow::getSCOUT_TRADE(json event_to_send){
    updata_event_map(event_to_send,{dataMap["scout_status"]});
    createTableRow({dataMap["scout_status"]});
}
void MainWindow::saveurl()
{
    std::ofstream file("IP.txt");
    if (!file.is_open()) {
        logger->log(get_now_time()+"ip file save err");
        return;
    }
    file<<CL.url;
    file.close();
    logger->log(get_now_time()+"ip file save successful");
}
void MainWindow::on_refresh_table_3_clicked()
{
    json son_message;
    son_message["request_type"]="check_running_strategy";
    son_message["payload"]=nlohmann::json::array();
    logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());

    CL.send(son_message);
}
void MainWindow::on_pushButton_28_clicked()
{
    std::string String=ui->lineEdit_5->text().toStdString();
    ui->tableWidget_5->clear();
    ui->tableWidget_5->setRowCount(0);
    int size=0;
    setItem(0);
    for(auto i:Strategy){
        if(String==""||i.SecurityID==String){
            if(i.Status!=0){
                ui->tableWidget_5->setRowCount(size+1);
                createTableRow(size,i,2,size);
                ++size;
            }
        }
    }
}
QMap<QString, QString> strategy_1::column_config= {
    {"ExchangeID", "交易所"},
    {"BuyTriggerVolume", "封单额"},
    {"CancelVolume", "撤单额"},
    {"Position", "目标仓位（元）"},
    {"TargetPosition", "目标仓位（股）"},
    {"CurrPosition", "已买仓位（股）"},
    // 这里需要添加Count的定义
    {"maxTriggerTimes", "最大触发次数"},
    {"ID", "策略编号"},
    {"Status", "策略状态"},
    {"OrderID", "策略委托"},
    {"LowerTimeLimit", "延迟触发"},
    {"SecurityName", "股票名称"},
    // Timed logic
    {"ScoutStatus", "保护单状态"},
    {"ScoutBuyTriggerCashLim", "保护单触发金额"},
    {"ScoutMonitorDuration", "保护单监控区间"},
    {"Cond2Percent", "撤单动量比例"},
    {"Cond2HighTime", "撤单动量监控时间"},
    {"Cond2TrackDuration", "撤单动量时间区间"},
    {"CancelTriggerVolumeLarge", "大单大撤单金额"},
    {"Cond4LowTime", "大单大撤单起始时间"},
    {"Cond4HighTime", "大单大撤单结束时间"}
};

void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked){
        for(int i=0;i<ui->tableWidget->rowCount();i++){
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
        }
    }
    else{
        for(int i=0;i<ui->tableWidget->rowCount();i++){
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        }
    }

}


void MainWindow::on_action_3_triggered()
{

    // 设置默认文件名和过滤器
    QString defaultFileName = "newtext.txt";
    QString filter = "Text Files (*.txt);;All Files (*)";
    // 弹出保存文件对话框，并指定默认文件名和过滤器
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Save As",
        QDir::homePath() + QDir::separator() + defaultFileName,
        filter
        );
    // 检查用户是否取消了对话框
    if (fileName.isEmpty()) {
        qDebug() << "Save operation canceled by user.";
        return;
    }

    // 如果用户没有指定文件名，则使用默认文件名
    if (fileName.contains(defaultFileName) && !fileName.contains(QDir::separator())) {
        fileName = QDir::homePath() + QDir::separator() + defaultFileName;
    }

    // 检查文件是否已存在
    QFile file(fileName);
    if (file.exists()) {
        // 如果文件存在，可以提示用户文件将被覆盖
        // 这里简单打印一条消息，实际应用中可能需要更复杂的逻辑
        qDebug() << "The file already exists and will be overwritten.";
    }

    // 打开文件进行写入
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 写入数据
        QTextStream out(&file);
        QString S="";
        out<<"运行策略\n";
        /*for(auto i:Strategy){
            out<<i;
        }*/
        // 遍历所有行
        for (int row = 0; row < ui->tableWidget_5->rowCount(); ++row) {
            // 遍历所有列
            for (int column = 1; column < ui->tableWidget_5->columnCount(); ++column) {
                // 获取当前单元格的项
                QTableWidgetItem *item = ui->tableWidget_5->item(row, column);
                if (item) {
                    // 打印当前单元格的文本
                    S+=item->text();
                    S+=' ';
                }
            }
            S+='\n';
        }
        out << S;

        // 关闭文件
        file.close();
        qDebug() << "File saved successfully:" << fileName;
    } else {
        // 打开文件失败
        qDebug() << "Failed to open the file for writing:" << fileName;
    }

}


void MainWindow::on_action_IP_triggered()
{
    NewWindow *newWindow = new NewWindow(nullptr);
    newWindow->age_IP(CL.url,[&]()->std::string&{
                 return CL.url;
    });
    newWindow->show();
}

std::string MainWindow::get_now_time()
{
    auto now = std::chrono::system_clock::now();
    // 转换为 time_t 类型
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    // 转换为 tm 结构，以获取本地时间
    std::tm now_tm = *std::localtime(&now_c);

    // 输出小时、分钟和秒
    std::stringstream ss;
    ss
              << std::setfill('0') << std::setw(2) << now_tm.tm_hour << ":"
              << std::setfill('0') << std::setw(2) << now_tm.tm_min << ":"
              << std::setfill('0') << std::setw(2) << now_tm.tm_sec <<" ";
    return ss.str();
}


void MainWindow::on_radioButton_clicked()
{

}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if(checked){
        for(int i=0;i<ui->tableWidget_5->rowCount();i++){
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
        }
    }
    else{
        for(int i=0;i<ui->tableWidget_5->rowCount();i++){
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        }
    }
}


void MainWindow::on_pushButton_9_clicked()
{
    json son_message;
    son_message["request_type"]="manuel_send_cancel";
    son_message["payload"]=nlohmann::json::array();
    for (int row = 0; row < ui->tableWidget_5->rowCount(); ++row) {
        if(ui->tableWidget_5->item(row,0)->checkState()){
            for(auto &temporary_data:Strategy){
                if(temporary_data.ID==ui->tableWidget_5->item(row,1)->text().toStdString()){
                    std::string ID;//策略编号 1
                    json data;
                    data["S_id"]=stoi(temporary_data.ID);
                    son_message["payload"].push_back(data);
                }
            }
        }
    }
    logger->log(get_now_time()+" send "+son_message["request_type"].get<std::string>());
    CL.send(son_message);
}

