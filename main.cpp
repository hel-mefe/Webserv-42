# include "Includes/Header.hpp"
# include "WebServer/WebServer.hpp"

void    print_http_configs(httpConfigs &configs)
{
    std::cout << "root -> " << configs.root << std::endl;
    std::cout << "Indexes - " << std::endl;
    std::cout << "[ " ;
    for (int i = 0; i < sz(configs.indexes); i++)
        std::cout << configs.indexes[i] << " " ;
    std::cout << "]" << std::endl;
    std::cout << "auto_indexing -> " << (configs.auto_indexing ? "on" : "off") << std::endl;
    std::cout << "connection -> " << (configs.connection ? "keep-alive" : "closed") << std::endl;
    std::cout << "allowed_methods -> " ;
    for (int i = 0; i < sz(configs.allowed_methods); i++)
        std::cout << configs.allowed_methods[i] << " " ;
}

void    print_servers_data(std::vector<Server *> servers)
{
    for (int i = 0; i < sz(servers); i++)
    {
        std::cout << "SERVER NUM = " << i << std::endl;
        servers[i]->print_data();
    }
}

int main(void)
{
    ConfigFileParser p("config");
    // // if (p.is_config_file_valid())
    // //     std::cout << "YES VALID" << std::endl;
    std::vector<Server *> *servers = new std::vector<Server *>();
    httpConfigs *configs = new httpConfigs();
    if (!p.parse_config_file(configs, servers))
        std::cout << "NOT VALID PARSING" << std::endl;
    else
    {
        print_http_configs(*configs);
        print_servers_data(*servers);
    }
    // if (p.is_config_file_valid())
    //     std::cout << "YES VALID" << std::endl;
}