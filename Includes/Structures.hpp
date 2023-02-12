#ifndef STRUCTURES_HPP
# define STRUCTURES_HPP

# include "Header.hpp"

typedef struct ServerAttributes
{
    string server_name;
    int port;
}   ServerAttr;

typedef struct HttpConfigs
{
    string  root;
    vector<string> indexes;
    bool    auto_indexing;
}   HttpConfigs;


#endif