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

    ServerAttributes() : max_connections(10){}
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
    std::vector<std::string>                        header_lines; // all the lines of the header stored in a  
    HashMap<std::string, std::string>               header_map; // header map (currently working with it)
    HashMap<std::string, int>                       header_map_ints; // header map for elements that accept ints (for future use)
    HashMap<std::string, std::vector<std::string> > header_map_vec; // header map for elements that accept multiple values (for future use)
    std::string                                     method; // by convention uppercased (POST, GET, DELETE)
    std::string                                     path; // self-explained (:D)
    std::string                                     http_version; // by convention uppercased (HTTP/1.1)
    std::string                                     connection; // for future use
    std::string                                     body; // for future use
    std::string                                     accept_content; // for future use
    int                                             content_length; // for future use
    int                                             request_len; // for future use
    bool                                            is_header_complete;
}   t_request;

typedef struct sock
{
    SOCKET      fd;
    SA_IN       data;
    socklen_t   data_len;
    bool        is_listener;
    bool        is_header_complete;
    std::string header;
    std::string body;
    t_request   *request;
    t_response  *response;
}   t_socket;

typedef struct globalVars
{
    HashSet<std::string>        supported_methods_set;
    HashMap<int, std::string>   codes_map;
}   globals;

typedef struct network
{
    int                         kq;
    unsigned int                num_connections;
    k_event                     *changeList;
    k_event                     *eventList;
    HashMap<SOCKET, int>        socket_index;
    std::queue<int>             clients_indexes;
}   t_network;

#endif