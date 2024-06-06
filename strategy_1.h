#ifndef STRATEGY_1_H
#define STRATEGY_1_H
#include "strategy_.h"
#include <string>
#include <json.hpp>
#include <QMap>
class strategy_1:public strategy_
{
private:
    static QMap<QString, QString> column_config;
public:
    std::string ExchangeID;
    int BuyTriggerVolume;
    int CancelVolume;
    int Position;
    int TargetPosition;
    int CurrPosition;
    int MaxTriggerTimes;
    std::string ID;
    int Status;
    std::string OrderID;
    std::string SecurityName;
    int ScoutBuyTriggerCashLim;
    float Cond2Percent;
    int CancelTriggerVolumeLarge;
    int ScoutStatus;
    long long int LowerTimeLimit; // 修改为 long long int
    long long int ScoutMonitorDuration; // 修改为 long long int
    long long int Cond2HighTime; // 修改为 long long int
    long long int Cond2TrackDuration; // 修改为 long long int
    long long int Cond4LowTime; // 修改为 long long int
    long long int Cond4HighTime; // 修改为 long long int
    std::string SecurityID;
    strategy_1(){}
    bool create(){return true;}
    strategy_1( std::string exchangeID, int buyTriggerVolume, int cancelVolume,
               int position, int targetPosition, int currPosition, int maxTriggerTimes, std::string id,
               int status, std::string orderID, std::string securityName, int scoutBuyTriggerCashLim,
               float cond2Percent, int cancelTriggerVolumeLarge, int scoutStatus, long long int lowerTimeLimit,
               long long int scoutMonitorDuration, long long int cond2HighTime, long long int cond2TrackDuration,
               long long int cond4LowTime, long long int cond4HighTime);
    std::ostream& operator<<(std::ostream& os);
    static void print_chiness(QStringList &List);
    void print(QStringList &List);
    void sout();
    nlohmann::json  to_json(std::string SecurityID);//将此策略模板发送至网络
};

#endif // STRATEGY_1_H
