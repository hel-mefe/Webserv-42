# include "Server.hpp"

Server::Server() : Request(0), Response(0), Attr(0)
{
    Attr = new ServerAttr();
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

ServerAttr* Server::getServerAttr() const
{
    return 0;
}

RequestHandler* Server::getRequestHandler() const
{
    return 0;
}

ResponseHandler*    Server::getResponseHandler() const
{
    return 0;
}