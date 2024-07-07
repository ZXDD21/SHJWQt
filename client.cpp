#include "client.h"

void  Client::on_message( websocketpp::connection_hdl hdl, message_ptr msg){//收到信号的处理
    json data=json::parse(msg->get_payload());
    fc(&data);
}
void Client::Client_Init(std::function<void(void*)>fn){

    //c.set_access_channels(websocketpp::log::alevel::all);

    c.clear_access_channels(websocketpp::log::alevel::all);
    c.init_asio();
    fc=fn;
    c.set_message_handler(bind(&Client::on_message,this,_1,_2));
    websocketpp::lib::error_code ec;
    client::connection_ptr con = c.get_connection(url, ec);
    hdl=con;
    if (ec) {
        std::cout << "could not create connection because: " << ec.message() << std::endl;
    }
    c.connect(con);

    c.run();

}
void Client::send(json json_message)
{
    std::cout<<json_message<<std::endl;
    if (c.get_con_from_hdl(hdl)->get_state() == websocketpp::session::state::open) {
        if( json_message["request_type"].get<std::string>() == "group_add_strategy" )
        {
            std::cout<<json_message<<std::endl;
            c.send(hdl,json_message.dump().c_str(), websocketpp::frame::opcode::text);
        }
        else if(json_message["request_type"].get<std::string>()=="group_remove_strategy"){
            c.send(hdl,json_message.dump().c_str(),websocketpp::frame::opcode::text);
        }
        else if(json_message["request_type"].get<std::string>()=="check_running_strategy"){
            c.send(hdl,json_message.dump().c_str(),websocketpp::frame::opcode::text);
        }
        else if(json_message["request_type"].get<std::string>()=="check_removed_strategy"){
            c.send(hdl,json_message.dump().c_str(),websocketpp::frame::opcode::text);
        }
        else if(json_message["request_type"].get<std::string>()=="cancel_order"){
            c.send(hdl,json_message.dump().c_str(),websocketpp::frame::opcode::text);
        }
        else  c.send(hdl,json_message.dump().c_str(), websocketpp::frame::opcode::text);
    } else {
        std::cout<<"err"<<std::endl;
    }

}



