# include "WebServer.hpp"

WebServer::WebServer()
{
    parser = new ConfigFileParser();
    http_configs = new t_http_configs();
    servers = new std::vector<Server *>();
}

WebServer::WebServer(std::string _config_file)
{
    parser = new ConfigFileParser();
    http_configs = new t_http_configs();
    servers = new std::vector<Server *>();
    config_file = _config_file;
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

// Debugging lines to show the data that was parsed

void    WebServer::print_global_http_data()
{
    std::cout << "**** GLOBAL HTTP CONFIGS ****" << std::endl;
    std::cout << "root: " << http_configs->root << std::endl;
    std::cout << "indexes: [ ";
    for (int i = 0; i < sz(http_configs->indexes); i++)
        std::cout << http_configs->indexes[i] << " ";
    std::cout << "]" << std::endl;
    std::cout << "allowed_methods: [ ";
    for (int i = 0; i < sz(http_configs->allowed_methods); i++)
        std::cout << http_configs->allowed_methods[i] << " ";
    std::cout << "]" << std::endl;
}

void    WebServer::print_servers_data()
{
    Server *s;

    std::cout << "**** SERVERS DATA ****" << std::endl;
    for (int i = 0; i < sz((*servers)); i++)
    {
        s = servers->at(i);
        s->print_data();
    }
}

void    WebServer::print_all_data()
{
    print_global_http_data();
    print_servers_data();
}

bool    WebServer::parse_config_file() // call the parser and returns if the config file is valid or not
{
    if (!parser->parse_config_file(config_file, http_configs, servers))
        return (false);
    return (true);
}

void    WebServer::run() // sockets of all servers will run here
{
    for (int i = 0; i < sz((*servers)); i++)
    {
        Server *s = servers->at(i);

        s->run();
    }
}