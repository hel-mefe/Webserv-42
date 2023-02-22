# include "Includes/Header.hpp"
# include "WebServer/WebServer.hpp"

void    print_http_configs(httpConfigs &configs)
{
    std::cout << "root -> " << configs.root << std::endl;
    std::cout << "Indexes - " << std::endl;
    std::cout << "[ " << std::endl;
    for (int i = 0; i < sz(configs.indexes); i++)
        std::cout << configs.indexes[i] << " " ;
    std::cout << "]" << std::endl;
    std::cout << "auto_indexing -> " << (configs.auto_indexing ? "on" : "off") << std::endl;
    std::cout << "connection -> " << (configs.connection ? "keep-alive" : "closed") << std::endl;
}

int main(void)
{
    ConfigFileParser p("config");
    // if (p.is_config_file_valid())
    //     std::cout << "YES VALID" << std::endl;
    std::vector<Server> *servers = new std::vector<Server>();
    httpConfigs *configs = new httpConfigs();
    if (!p.parse_config_file(configs, servers))
        std::cout << "NOT VALID PARSING" << std::endl;
    else
        print_http_configs(*configs);
}