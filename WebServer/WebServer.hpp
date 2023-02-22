#ifndef WEB_SERVER_HPP
# define WEB_SERVER_HPP

# include "../Includes/Header.hpp"
# include "../Includes/Structures.hpp"
# include "Server/Server.hpp"
# include "ConfigFileParser/ConfigFileParser.hpp"

class WebServer
{
    private:
        std::vector<Server>  *servers;
        httpConfigs          *globalHttpConfigs;
        ConfigFileParser     *parser;
    public:
        WebServer();
        WebServer(const WebServer& w);
        WebServer& operator=(const WebServer& w);
        ~WebServer();
} ;

# endif