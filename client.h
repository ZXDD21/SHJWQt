#ifndef CLIENT_H
#define CLIENT_H
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <string>
#include <queue>
#include <json.hpp>
#include <vector>
#include <functional>
using json = nlohmann::json;
typedef websocketpp::client<websocketpp::config::asio_client> client;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
enum Send_name{
    Sendinput=0//创建新策略
    ,getdata//请求现有策略
    ,Sendchange//改变指定策略
    ,Senddelete//删除指定策略
};
enum Index{
    IndexID=1,//策略编号
    IndexSecurityID,//证券代码
    IndexSecurityName,//股票名称
    IndexExchangeID,//交易所
    IndexBuyTriggerVolume,//封单额
    IndexCancelVolume,//撤单额
    IndexPosition,//目标仓位 元
    IndexTargetPosition,//目标仓位 股
    IndexCurrPosition,//已买仓位 股
    IndexOrderID,//策略委托
    IndexLowerTimeLimit,//延迟触发
    IndexMaxTriggerTimes,//大单延迟时间
    IndexStatus,//策略状态
    IndexCount,//撤单次数 nullptr
    IndexScoutStatus,//保护单状态 nullptr
    IndexScoutBuyTriggerCashLim,//保护单触发金额 nullptr
    IndexScoutMonitorDuration,//保护单监控区间 nullptr
    IndexCond2Percent,//撤单动量比例 nullptr
    IndexCond2HighTime,//撤单动量监控时间 nullptr
    IndexCond2TrackDuration,//撤单动量时间区间 nullptr
    IndexCancelTriggerVolumeLarge,//大单大撤单金额 nullptr
    IndexCond4LowTime,//大单大撤单起始时间 nullptr
    IndexCond4HighTime//大单大撤单结束时间 nullptr
};
class Client
{
public:
    Client():c(),url("ws://45.125.34.103:8765"){};
    void Client_Init(std::function<void(void*)>fn);
    void on_message( websocketpp::connection_hdl hdl, message_ptr msg);
    std::queue<std::vector<std::string>>ans;
    //void send(int i,void* ptr);
    void send(json data);
private:
    client c;
    std::string url;
    websocketpp::connection_hdl hdl;//服务器连接句柄
    std::function<void(void*)>fc;//回调函数包装类
};
// class strategy_{
// public:
//     strategy_(){}
//     ~strategy_(){}
// };
// class strategy_1:public strategy_{
//     std::string SecurityID;//证券代码
//     std::string ExchangeID;//交易所
//     int BuyTriggerVolume;//封单额
//     int CancelVolume;//撤单额
//     int DBVolume;//打板金额
//     int ordercancellationcount;//撤单金额
//     int MaxTriggerTimes;//大单延迟时间
//     int ScoutBuyTriggerCashLim;//保护单触发金额 nullptr
//     int minMonitorTimes;//小单监控时间
//     int Cond2Percent;//撤单动量比例 nullptr
//     int Cond2HighTime;//撤单动量监控时间 nullptr
//     int Cond2TrackDuration;//撤单动量时间区间 nullptr
//     int  MaxBuyTriggerVolume;//大单大封单金额
// };
// struct inputstrategy{
//     std::string SecurityID;//证券代码
//     std::string ExchangeID;//交易所
//     int BuyTriggerVolume;//封单额
//     int CancelVolume;//撤单额
//     int DBVolume;//打板金额
//     int ordercancellationcount;//撤单金额
//     int MaxTriggerTimes;//大单延迟时间
//     int ScoutBuyTriggerCashLim;//保护单触发金额 nullptr
//     int minMonitorTimes;//小单监控时间
//     int Cond2Percent;//撤单动量比例 nullptr
//     int Cond2HighTime;//撤单动量监控时间 nullptr
//     int Cond2TrackDuration;//撤单动量时间区间 nullptr
//     int  MaxBuyTriggerVolume;//大单大封单金额
// };

#endif // CLIENT_H
