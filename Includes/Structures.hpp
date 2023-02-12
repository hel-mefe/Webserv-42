#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP

# include "Header.hpp"

typedef struct ServerAttributes
{
    std::string server_name;
    int port;
}   ServerAttr;

typedef struct HttpConfigs
{
    std::string  root;
    std::vector<std::string> indexes;
    bool    auto_indexing;
}   HttpConfigs;


#endif