#include "strategy_1.h"

strategy_1::strategy_1(
    std::string exchangeID, int buyTriggerVolume, int cancelVolume,
    int position, int targetPosition, int currPosition, int maxTriggerTimes, std::string id,
    int status, std::string orderID, std::string securityName, int scoutBuyTriggerCashLim,
    float cond2Percent, int cancelTriggerVolumeLarge, int scoutStatus, long long int lowerTimeLimit,
    long long int scoutMonitorDuration, long long int cond2HighTime, long long int cond2TrackDuration,
    long long int cond4LowTime, long long int cond4HighTime)
    : SecurityID("0"),ExchangeID(exchangeID), BuyTriggerVolume(buyTriggerVolume),
    CancelVolume(cancelVolume), Position(position), TargetPosition(targetPosition),
    CurrPosition(currPosition), MaxTriggerTimes(maxTriggerTimes), ID(id), Status(status),
    OrderID(orderID), SecurityName(securityName), ScoutBuyTriggerCashLim(scoutBuyTriggerCashLim),
    Cond2Percent(cond2Percent), CancelTriggerVolumeLarge(cancelTriggerVolumeLarge),
    ScoutStatus(scoutStatus), LowerTimeLimit(lowerTimeLimit),
    ScoutMonitorDuration(scoutMonitorDuration), Cond2HighTime(cond2HighTime),
    Cond2TrackDuration(cond2TrackDuration), Cond4LowTime(cond4LowTime), Cond4HighTime(cond4HighTime) {}
std::ostream &strategy_1::operator<<(std::ostream &os)
{

    os << ExchangeID << " "
       << BuyTriggerVolume << " "
       << CancelVolume << " "
       << Position << " "
       << TargetPosition << " "
       << CurrPosition << " "
       << MaxTriggerTimes << " "
       << ID << " "
       << Status << " "
       << OrderID << " "
       << SecurityName << " "
       << ScoutBuyTriggerCashLim << " "
       << Cond2Percent << " "
       << CancelTriggerVolumeLarge << " "
       << ScoutStatus << " "
       << LowerTimeLimit << " "
       << ScoutMonitorDuration << " "
       << Cond2HighTime << " "
       << Cond2TrackDuration << " "
       << Cond4LowTime << " "
       << Cond4HighTime << std::endl;
    return os; // 返回引用以支持连续输出

}

void strategy_1::print(QStringList &List)
{
    List  << "交易所" << QString::fromStdString(ExchangeID)
         << "封单额" << QString::number(BuyTriggerVolume)
         << "撤单额" << QString::number(CancelVolume)
         << "目标仓位（元）" << QString::number(Position)
         << "目标仓位（股）" << QString::number(TargetPosition)
         << "已买仓位（股）" << QString::number(CurrPosition)
         <<"撤单次数"<<QString::number(MaxTriggerTimes)
         << "策略编号" << QString::fromStdString(ID)
         << "策略状态" << QString::number(Status)
         << "策略委托" << QString::fromStdString(OrderID)
         << "延迟触发" << QString::number(LowerTimeLimit)
         << "股票名称" << QString::fromStdString(SecurityName)
         << "保护单状态" << QString::number(ScoutStatus)
         << "保护单触发金额" << QString::number(ScoutBuyTriggerCashLim)
         << "保护单监控区间" << QString::number(ScoutMonitorDuration)
         << "撤单动量比例" << QString::number(Cond2Percent)
         << "撤单动量监控时间" << QString::number(Cond2HighTime)
         << "撤单动量时间区间" << QString::number(Cond2TrackDuration)
         << "大单大撤单金额" << QString::number(CancelTriggerVolumeLarge)
         << "大单大撤单起始时间" << QString::number(Cond4LowTime)
         << "大单大撤单结束时间" << QString::number(Cond4HighTime);
}

void strategy_1::print_chiness(QStringList &List)
{
    List  << "交易所"
         << "封单额"
         << "撤单额"
         << "目标仓位（元）"
         << "目标仓位（股"
         << "已买仓位（股）"
         <<"撤单次数"
         << "策略编号"
         << "策略状态"
         << "策略委托"
         << "延迟触发"
         << "股票名称"
         << "保护单状态"
         << "保护单触发金额"
         << "保护单监控区间"
         << "撤单动量比例"
         << "撤单动量监控时间"
         << "撤单动量时间区间"
         << "大单大撤单金额"
         << "大单大撤单起始时间"
         << "大单大撤单结束时间"<<" " <<" "<<" ";
}
void strategy_1::sout()
{
#include <iostream>
#include <string>
    std::cout
        << ExchangeID << " "
        << BuyTriggerVolume << " "
        << CancelVolume << " "
        << Position << " "
        << TargetPosition << " "
        << CurrPosition << " "
        << MaxTriggerTimes << " "
        << ID << " "
        << Status << " "
        << OrderID << " "
        << SecurityName << " "
        << ScoutBuyTriggerCashLim << " "
        << Cond2Percent << " "
        << CancelTriggerVolumeLarge << " "
        << ScoutStatus << " "
        << LowerTimeLimit << " "
        << ScoutMonitorDuration << " "
        << Cond2HighTime << " "
        << Cond2TrackDuration << " "
        << Cond4LowTime << " "
        << Cond4HighTime << std::endl;


}
nlohmann::json strategy_1::to_json(std::string SecurityID){
    nlohmann::json data =  nlohmann::json{
        {"SecurityID", SecurityID},
        {"ExchangeID", std::to_string(((ExchangeID=="SSE"||ExchangeID=="1")?1:2))},
        {"BuyTriggerVolume", BuyTriggerVolume},
        {"CancelVolume", CancelVolume},
        {"Position", Position},
        {"TargetPosition", TargetPosition},
        {"CurrPosition", CurrPosition},
        {"MaxTriggerTimes", MaxTriggerTimes},
        //{"ID", ID},
        {"Status", Status},
        {"OrderID", OrderID},
        {"SecurityName", SecurityName},
        {"ScoutBuyTriggerCashLim", ScoutBuyTriggerCashLim},
        {"Cond2Percent", Cond2Percent},
        {"CancelTriggerVolumeLarge", CancelTriggerVolumeLarge},
        {"ScoutStatus", ScoutStatus},
        {"LowerTimeLimit", LowerTimeLimit},
        {"ScoutMonitorDuration", ScoutMonitorDuration},
        {"Cond2HighTime", Cond2HighTime},
        {"Cond2TrackDuration", Cond2TrackDuration},
        {"Cond4LowTime", Cond4LowTime},
        {"Cond4HighTime", Cond4HighTime}
    };
    return data;
}
