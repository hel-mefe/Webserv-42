# include "WebServer.hpp"

WebServer::WebServer()
{
    Parser = new ConfigFileParser();
    GlobalHttpConfigs = new HttpConfigs();
    return ;
}

WebServer::WebServer(const WebServer& w)
{
    return ;
}

WebServer& WebServer::operator=(const WebServer& w)
{
    return *this;
}

WebServer::~WebServer()
{
    return ;
}