#ifndef STRATEGY__H
#define STRATEGY__H
#include <string>
#include <iostream>
#include <json.hpp>
#include <QStringList>
class strategy_
{
public:
    strategy_(){}
    virtual bool create(){return true;}
    virtual std::ostream& operator<<(std::ostream& os)=0;
    //virtual void serializeStrategyconst(const std::string& filename)=0;//从文件中获取此策略的模板
    virtual nlohmann::json  to_json(std::string SecurityID)=0;//将此策略模板发送至网络
    virtual void sout()=0;
    virtual void print(QStringList &List)=0;
    virtual~strategy_(){}
};

#endif // STRATEGY__H
