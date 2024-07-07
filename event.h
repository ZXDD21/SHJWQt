#ifndef EVENT_H
#define EVENT_H
#include <string>
#include <json.hpp>
using json = nlohmann::json;
class Event
{
public:
    std::string e_type;
    int formal_status;
    int scout_status;
    int trade_volume;
    int scout_trigger_times;
    int formal_trigger_times;
    double volume_before_strate;
    double fenban_volume;
    std::string order_trigger_time;
    std::string S_id;
    // 全参构造函数
    Event(const std::string& event_type, int formal_stat, int scout_stat, int trade_vol, int scout_trig_times, int formal_trig_times,
          double vol_before_strat, double fenban_vol, const std::string& order_trig_time, const std::string& s_id)
        : e_type(event_type), formal_status(formal_stat), scout_status(scout_stat), trade_volume(trade_vol),
        scout_trigger_times(scout_trig_times), formal_trigger_times(formal_trig_times),
        volume_before_strate(vol_before_strat), fenban_volume(fenban_vol),
        order_trigger_time(order_trig_time), S_id(s_id)
    {
    }
    // 默认构造函数
    Event() :
        e_type(""),
        formal_status(0),
        scout_status(0),
        trade_volume(0),
        scout_trigger_times(0),
        formal_trigger_times(0),
        volume_before_strate(0.0),
        fenban_volume(0.0),
        order_trigger_time(""),
        S_id("")
    {
    }
    Event(const json& j)
    {
        e_type = j["e_type"].get<std::string>();
        formal_status = j["formal_status"].get<int>();
        scout_status = j["scout_status"].get<int>();
        trade_volume = j["trade_volume"].get<int>();
        scout_trigger_times = j["scout_trigger_times"].get<int>();
        formal_trigger_times = j["formal_trigger_times"].get<int>();
        volume_before_strate = j["volume_before_strate"].get<double>();
        fenban_volume = j["fenban_volume"].get<double>();
        order_trigger_time = j["order_trigger_time"].get<std::string>();
        S_id = j["S_id"].get<std::string>();
    }
};

#endif // EVENT_H
