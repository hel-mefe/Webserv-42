# include "Server.hpp"

Server::Server() : request_response(0), server_configs(0), http_configs(0), dir_configs(0)
{
    mult = KQUEUE;
    request_response = new RequestResponse();
    server_configs = new t_server_configs();
    http_configs = new t_http_configs();
    dir_configs = new HashMap<std::string, t_location_configs>();
}

Server::Server(MULTIPLEXER _mult)
{
    mult = _mult;
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

SOCKET Server::get_listener_socket(t_socket *listener)
{
    int sockfd, listen_status, bind_status;
    SA_IN *data = &listener->data;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        throw SocketException();
    bzero(data, sizeof(*data));
    data->sin_addr.s_addr = INADDR_ANY;
    data->sin_port = htons(server_configs->port);
    data->sin_family = AF_INET;
    listener->data_len = sizeof(listener->data);
    bind_status = bind(sockfd, (SA *)(data), sizeof(*data));
    if (bind_status < 0)
        throw BindException();
    listen_status = listen(sockfd, server_configs->max_connections);
    if (listen_status < 0)
        throw ListenException();
    return (sockfd);
}

void    Server::add_connection(t_network *manager) // client is a listener socket
{
    if (!sz(manager->clients_indexes))
        return ;
    int index = manager->clients_indexes.front();
    t_socket *listener = (t_socket *) manager->changeList[0].udata; // this t_socket surely will be a listener since add_connection has been called
    manager->clients_indexes.pop();
    SOCKET connection = accept(listener->fd, (SA *)&listener->data, &listener->data_len); // fd of the client
    manager->socket_index.insert(std::make_pair(connection, index));
    EV_SET(manager->changeList + index, connection, EVFILT_READ | EV_EOF, EV_ADD | EV_CLEAR, 0, 0, manager->changeList[index].udata);    
    t_socket *client = (t_socket *) manager->changeList[index].udata;
    client->fd = connection;
    client->is_listener = false;
    std::cout << "Connection working ..." << std::endl;
    manager->num_connections++;
}

// void    Server::parse_client_request(t_socket *client)
// {
//     for (int i = 0; i < )
// }

// void    Server::read_request(t_socket *client)
// {
//     SOCKET  fd = client->fd;
//     char    buff[BUFFER_SIZE];
//     char    *line = get_next_line(fd);
//     int     len;
//     std::string s;
//     bool is_finished = client->is_header_complete;

//     if (!line)
//         return ;
//     s = std::string(line);
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (!line)
//             break ;
//         s = std::string(line);
//         client->request->request_lines.push_back(s);
//         client->request->request_len += sz(s);
//         if (line)
//             free(line);
//         is_finished = (s == "\r\n");
//         if (is_finished)
//             break ;
//     }
//     client->request->is_header_complete = is_finished;
//     if (is_finished)
//     {
//         client->request = request_response->parse_client_request(client->request);
//         client->request->request_len += len;
//     }
// }

void    Server::disconnect_client(t_network *manager, int index)
{
    SOCKET fd = manager->eventList[index].ident;
    index = manager->socket_index[fd]; // I know the fd already exists in the map
    std::cout << "Client disconnected!" << std::endl;
    manager->socket_index.erase(fd);
    close(fd);
    EV_SET(manager->changeList + index, SOCKET_NOT_DEFINED, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, manager->changeList[index].udata);
    manager->clients_indexes.push(index);
    manager->num_connections--;
}

void    Server::serve_client(t_network *manager, int index)
{
    t_socket *client;

    client = (t_socket *) manager->eventList[index].udata;
    if (!client->is_header_complete)
        request_response->parse_client_request(client);
    else
    {
        std::cout << "Request header is complete now!" << std::endl;
        // if (!client->response)
        //     client->response = request_response->get_response(client->request);
        // request_response->set_response_path(client);
    }
}

void    Server::handle_client(t_network *manager, int index)
{
    if (manager->eventList[index].flags & EV_EOF) // the socket has been closed and should be remove from the list
        disconnect_client(manager, index);
    else // read_event which mean we have to read the request
        serve_client(manager, index);
}

void    Server::build_with_kqueue()
{
    t_network   *manager; // Yes boss!!
    t_socket    *sock;

    sock = new t_socket();
    manager = new t_network();
    sock->request = nullptr;
    manager->kq = kqueue();
    manager->changeList = new k_event[server_configs->max_connections]();
    manager->eventList = new k_event[server_configs->max_connections]();
    sock->fd = get_listener_socket(sock);
    sock->is_listener = true;
    manager->socket_index.insert(std::make_pair(sock->fd, 0));
    EV_SET(&manager->eventList[0], sock->fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, sock);
    EV_SET(&manager->changeList[0], sock->fd, EVFILT_READ, EV_ADD | EV_CLEAR, 0, 0, sock);
    for (int i = 1; i < server_configs->max_connections; i++)
    {
        sock = new t_socket();
        sock->is_listener = false;
        sock->request = new t_request();
        EV_SET(&manager->eventList[i], 0, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, sock);
        EV_SET(&manager->changeList[i], 0, EVFILT_USER, EV_ADD | EV_CLEAR, 0, 0, sock);
        manager->clients_indexes.push(i);
    }
    if (kevent(manager->kq, manager->changeList, server_configs->max_connections, NULL, 0, NULL) != 0)
        throw MultiplexerException();
    while (true)
    {
        int ret = kevent(manager->kq, manager->changeList, server_configs->max_connections, manager->eventList, server_configs->max_connections, NULL);
        for (int i = 0; i < ret; i++)
        {
            std::cout << manager->num_connections << std::endl;
            t_socket *client = (t_socket *) manager->eventList[i].udata;
            if (client->is_listener)
                add_connection(manager);
            else
                handle_client(manager, i);
        }
    }
}

void    Server::run() // the runner where the multiplexing will be (kevent, select, poll)
{
    if (mult == KQUEUE)
        build_with_kqueue();
    // int sockfd, listen_status, bind_status;

    // bzero(&data, sizeof(data));
    // data.sin_family = AF_INET;
    // data.sin_port = htons(this->server_configs->port);
    // data.sin_addr.s_addr = INADDR_ANY;
    // sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // if (sockfd < 0)
    //     throw SocketException();
    // bind_status = bind(sockfd, (struct sockaddr *) &data, sizeof(data));
    // if (bind_status < 0)
    //     throw BindException();
    // listen_status = listen(sockfd, this->server_configs->max_connections);
    // if (listen_status < 0)
    //     throw ListenException();
    // while (1)
    // {
    //     unsigned int data_size = sizeof(data);
    //     int acc_conn = accept(sockfd, (struct sockaddr *) &data, &data_size);
    //     t_request *req = parser->parse_request(acc_conn);
    //     print_request(req);
    //     if (req->method == "GET")
    //         handle_get_request(acc_conn, req);
    //     else if (req->method == "POST")
    //         handle_post_request(acc_conn, req);
    //     else if (req->method == "DELETE")
    //         handle_delete_request(acc_conn, req);
    //     delete req;
    // }
}