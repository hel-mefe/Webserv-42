#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP

# include "Header.hpp"

typedef struct ServerAttributes
{
    std::string                         server_name;
    PORT                                port;
    std::string                         root;
    std::vector<std::string>            indexes;
    std::vector<std::string>            allowed_methods;
    std::vector<std::string>            allowed_cgi;
    std::vector<std::string>            locations;
    HashMap<std::string, std::string>   extension_cgi; // <extension, cgi_program_name>
    HashSet<std::string>                allowed_methods_set;
    HashSet<std::string>                allowed_cgi_set;
    HashSet<std::string>                locations_set;
    HashSet<std::string>                indexes_set;
    int                                 max_connections;
    bool                                directory_listing;
    bool                                auto_indexing;
    bool                                connection; // keep-alive or closed

    ServerAttributes() : max_connections(5){}
}   t_server_configs;

typedef struct LocationConfigs
{
    std::string                         root;
    std::vector<std::string>            indexes;
    std::vector<std::string>            allowed_methods;
    std::vector<std::string>            allowed_cgi;
    std::vector<std::string>            locations;
    HashSet<std::string>                indexes_set;
    HashSet<std::string>                allowed_methods_set;
    bool                                auto_indexing;
    bool                                connection;
}   t_location_configs;

typedef struct HttpConfigs
{
    std::string                         root;
    std::vector<std::string>            indexes;
    std::vector<std::string>            allowed_methods;
    std::vector<std::string>            allowed_cgi;
    std::vector<std::string>            locations;
    HashMap<std::string, std::string>   extension_cgi; // <extension, cgi_program_name>
    HashSet<std::string>                allowed_methods_set;
    HashSet<std::string>                allowed_cgi_set;
    HashSet<std::string>                locations_set;
    bool                                directory_listing;
    bool                                auto_indexing;
    bool                                connection; // keep-alive or closed
}   t_http_configs;


typedef struct response
{
    std::string             method;
    std::string             connection;
    std::string             status_line;
    int                     status_code;
    int                     content_length;
}   t_response;

typedef struct Header
{
    std::string     method;
    std::string     connection;
    std::string     path;
    std::string     http_version;
    int             content_length;
}   t_request;

typedef struct globalVars
{
    HashSet<std::string>        supported_methods_set;
    HashMap<int, std::string>   codes_map;
}   globals;

#endif