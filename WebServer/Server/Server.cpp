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
    if (this->Attr)
        delete this->Attr;
    this->Attr = _Attr;
}

void    Server::set_location_map(std::string location_name, locationConfigs &configs)
{
    dir_configs.insert(std::make_pair(location_name, configs));
}

void    Server::print_data()
{
    std::cout << "**** SERVER ATTRIBUTES ****" << std::endl;
    std::cout << "server_name -> " << Attr->server_name << std::endl;
    std::cout << "port -> " << Attr->port << std::endl;
    std::cout << "root -> " << Attr->root << std::endl;
    std::cout << "-- Indexes -> ";
    for (int i = 0; i < sz(Attr->indexes); i++)
        std::cout << Attr->indexes[i] << " " ;
    std::cout << std::endl << "-- Allowed methods -> " ;
    for (int i = 0; i < sz(Attr->allowed_methods); i++)
        std::cout << Attr->allowed_methods[i] << " " ;
    std::cout << std::endl << "directory_listing -> " << (Attr->directory_listing ? "on" : "off") << std::endl;
    std::cout << "auto_indexing -> " << (Attr->auto_indexing ? "on" : "off") << std::endl;
    std::cout << "connection -> " << (Attr->connection ? "on" : "off") << std::endl;
}

RequestHandler* Server::getRequestHandler() const
{
    return 0;
}

ResponseHandler*    Server::getResponseHandler() const
{
    return 0;
}