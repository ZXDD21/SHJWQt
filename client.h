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
    Client():c(),url(){};
    void Client_Init(std::function<void(void*)>fn);
    void on_message( websocketpp::connection_hdl hdl, message_ptr msg);
    std::queue<std::vector<std::string>>ans;
    //void send(int i,void* ptr);
    void send(json data);
     std::string url;
private:

    client c;
    websocketpp::connection_hdl hdl;//服务器连接句柄
    std::function<void(void*)>fc;//回调函数包装类
};

#endif // CLIENT_H
