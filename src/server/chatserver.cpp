#include<chatserver.hpp>
#include<functional>
#include"json.hpp"
#include"chatservice.hpp"
using namespace std;
using namespace placeholders;   //placeholders 占位符
using json = nlohmann::json;


//初始化聊天服务器对象
ChatServer::ChatServer(EventLoop *loop, const InetAddress& listenAddr, const string& nameArg) : _server(loop,listenAddr,nameArg), _loop(loop) //初始化成员变量_server、_loop
{
    //注册链接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    //注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    //设置线程数量 1个I/O线程,3个worker线程
    _server.setThreadNum(4);
}

//启动服务
void ChatServer::start()
{
    _server.start();
}

//上报链接相关信息的回调函数
void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    //客户端断开链接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
//上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据的反序列化 解码
    json js = json::parse(buf);
    //目的：完全解耦网络模块的代码和业务模块的代码
    //通过js["msgid"]获取对应业务模块的handler
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());    // js["msgid"].get<int>() 把js["msgid"]转换成int
    // 回调消息绑定好的事件处理器，来执行相应的业务处理
    msgHandler(conn,js,time);


}
