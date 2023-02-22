# include "WebServer.hpp"

WebServer::WebServer()
{
    parser = new ConfigFileParser();
    globalHttpConfigs = new httpConfigs();
    servers = new std::vector<Server>();
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