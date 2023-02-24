# include "Server.hpp"

Server::Server() : request_response(0), server_configs(0), http_configs(0), dir_configs(0)
{
    request_response = new RequestResponse();
    server_configs = new t_server_configs();
    http_configs = new t_http_configs();
    dir_configs = new HashMap<std::string, t_location_configs>();
}

Server::Server(const Server &s) : request_response(0), server_configs(0), http_configs(0), dir_configs(0)
{
    *this = s;
}

Server& Server::operator=(const Server &s)
{
    return (*this);
}

Server::~Server()
{
    if (request_response)
        delete request_response;
    if (server_configs)
        delete server_configs;
    if (http_configs)
        delete http_configs;
    if (dir_configs)
        delete dir_configs;
}


void    Server::set_server_configs(t_server_configs *_server_configs)
{
    if (this->server_configs)
        delete this->server_configs;
    this->server_configs = _server_configs;
}

void    Server::set_location_map(std::string location_name, t_location_configs &configs)
{
    dir_configs->insert(std::make_pair(location_name, configs));
}

void    Server::print_data()
{
    std::cout << "**** SERVER ATTRIBUTES ****" << std::endl;
    std::cout << "server_name -> " << server_configs->server_name << std::endl;
    std::cout << "port -> " << server_configs->port << std::endl;
    std::cout << "root -> " << server_configs->root << std::endl;
    std::cout << "-- Indexes -> ";
    for (int i = 0; i < sz(server_configs->indexes); i++)
        std::cout << server_configs->indexes[i] << " " ;
    std::cout << std::endl << "-- Allowed methods -> " ;
    for (int i = 0; i < sz(server_configs->allowed_methods); i++)
        std::cout << server_configs->allowed_methods[i] << " " ;
    std::cout << std::endl << "directory_listing -> " << (server_configs->directory_listing ? "on" : "off") << std::endl;
    std::cout << "auto_indexing -> " << (server_configs->auto_indexing ? "on" : "off") << std::endl;
    std::cout << "connection -> " << (server_configs->connection ? "on" : "off") << std::endl;
}

void print_request(t_request *r)
{
    std::cout << "Connection: " << r->connection << std::endl;
    std::cout << "Content-length: " << r->content_length << std::endl;
    std::cout << "Http version: " << r->http_version << std::endl;
    std::cout << "Method: " << r->method << std::endl;
    std::cout << "Path: " << r->path << std::endl;
}

void    handle_get_request()
{
    std::cout << "Handling get request is running ..." << std::endl;
}

void    handle_post_request()
{
    std::cout << "Handling post request is running ..." << std::endl;
}

void    handle_delete_request()
{
    std::cout << "Handling delete request is running ..." << std::endl;
}

void    Server::run()
{
    int sockfd, listen_status, bind_status;
    struct sockaddr_in data;
    RequestParser *parser = new RequestParser(); // just to test the request parser

    bzero(&data, sizeof(data));
    data.sin_family = AF_INET;
    data.sin_port = htons(this->server_configs->port);
    data.sin_addr.s_addr = INADDR_ANY;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind_status = bind(sockfd, (struct sockaddr *) &data, sizeof(data));
    listen_status = listen(sockfd, this->server_configs->max_connections);
    while (1)
    {
        unsigned int data_size = sizeof(data);
        int acc_conn = accept(sockfd, (struct sockaddr *) &data, &data_size);
        t_request *req = parser->parse_request(acc_conn);
        print_request(req);
        if (req->method == "GET")
            handle_get_request();
        else if (req->method == "POST")
            handle_post_request();
        else if (req->method == "DELETE")
            handle_delete_request();
        delete req;
    }
}