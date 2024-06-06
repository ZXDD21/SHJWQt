#ifndef STRATEGY_H
#define STRATEGY_H
#include <string>
class strategy
{
public:
    std::string SecurityID;//证券代码 1
    std::string ExchangeID;//交易所 sendto:char 1,2
    std::string OrderID;//策略委托
    std::string SecurityName;//股票名称
    std::string ID;//策略编号 sendto:Int
    int BuyTriggerVolume;//封单额
    int CancelVolume;//撤单额
    int Position;//目标仓位 元
    int TargetPosition;//目标仓位 股
    int CurrPosition;//已买仓位 股
    int LowerTimeLimit;//延迟触发
    int MaxTriggerTimes;//大单延迟时间
    int Status;//策略状态
    int Count;//撤单次数 nullptr
    int ScoutStatus;//保护单状态 nullptr
    int ScoutBuyTriggerCashLim;//保护单触发金额 nullptr
    long long int ScoutMonitorDuration;//保护单监控区间 nullptr
    float Cond2Percent;//撤单动量比例 nullptr
    long long int Cond2HighTime;//撤单动量监控时间 nullptr
    long long int Cond2TrackDuration;//撤单动量时间区间 nullptr
    int CancelTriggerVolumeLarge;//大单大撤单金额 nullptr
    long long int Cond4LowTime;//大单大撤单起始时间 nullptr
    long long int Cond4HighTime;//大单大撤单结束时间 nullptr
public:
    strategy(
        const std::string& secID, const std::string& exID, const std::string& ordID,
        const std::string& secName, const std::string& stratID,
        int buyVol, int canVol, int pos, int targPos, int currPos,
        int lowTimeLim, int maxTrigTimes, int stat, int cnt,
        int scoutStat, int scoutBuyTrigCashLim, long long int scoutMonDur,
        float cond2Perc, long long int cond2HighTime, long long int cond2TrackDur,
        int canTrigVolLrg, long long int cond4LowTime, long long int cond4HighTime)
        : SecurityID(secID), ExchangeID(exID), OrderID(ordID), SecurityName(secName),
        ID(stratID), BuyTriggerVolume(buyVol), CancelVolume(canVol), Position(pos),
        TargetPosition(targPos), CurrPosition(currPos), LowerTimeLimit(lowTimeLim),
        MaxTriggerTimes(maxTrigTimes), Status(stat), Count(cnt), ScoutStatus(scoutStat),
        ScoutBuyTriggerCashLim(scoutBuyTrigCashLim), ScoutMonitorDuration(scoutMonDur),
        Cond2Percent(cond2Perc), Cond2HighTime(cond2HighTime), Cond2TrackDuration(cond2TrackDur),
        CancelTriggerVolumeLarge(canTrigVolLrg), Cond4LowTime(cond4LowTime), Cond4HighTime(cond4HighTime) {}


    // 其他成员函数...
};

#endif // STRATEGY_H
