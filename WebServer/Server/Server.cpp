# include "Server.hpp"

Server::Server() : Request(0), Response(0), Attr(0)
{
    Attr = new serverAttr();
    Request = new RequestHandler();
    Response = new ResponseHandler();
}

Server::Server(const Server &s) : Request(0), Response(0), Attr(0)
{
    if (Attr)
        delete Attr;
    if (Request)
        delete Request;
    if (Response)
        delete Response;
    *this = s;
}

Server& Server::operator=(const Server &s)
{
    if (Attr)
        delete Attr;
    if (Request)
        delete Request;
    if (Response)
        delete Response;
    Attr = s.getServerAttr();
    Response = s.getResponseHandler();
    Request = s.getRequestHandler();
    return (*this);
}

Server::~Server()
{
    if (Attr)
        delete Attr;
    if (Request)
        delete Request;
    if (Response)
        delete Response;
}

serverAttr* Server::getServerAttr() const
{
    return 0;
}

void    Server::set_server_attr(serverAttr *_Attr)
{
    if (Attr)
        delete Attr;
    Attr = _Attr;
}

void    Server::set_location_map(std::string location_name, locationConfigs &configs)
{
    dir_configs.insert(std::make_pair(location_name, configs));
}

RequestHandler* Server::getRequestHandler() const
{
    return 0;
}

ResponseHandler*    Server::getResponseHandler() const
{
    return 0;
}