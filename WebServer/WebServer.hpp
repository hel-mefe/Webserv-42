#ifndef WEB_SERVER_HPP
# define WEB_SERVER_HPP

# include "../Includes/Header.hpp"
# include "../Includes/Structures.hpp"
# include "Server/Server.hpp"
# include "ConfigFileParser/ConfigFileParser.hpp"

class WebServer
{
    private:
        std::vector<Server *>           *servers;
        t_http_configs                  *http_configs;
        ConfigFileParser                *parser;
        HashMap<int, std::string>       *codes;
        std::string                     config_file;
    public:
        WebServer();
        WebServer(std::string);
        WebServer(const WebServer& w);
        WebServer& operator=(const WebServer& w);
        ~WebServer();

        bool    parse_config_file();
        void    run();

        // Debugging lines to check the data that was parsed
        void    print_global_http_data();
        void    print_servers_data();
        void    print_all_data();
} ;

# endif