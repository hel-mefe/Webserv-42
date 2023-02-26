#ifndef HEADER_HPP
# define HEADER_HPP

# include <iostream>
# include <vector>
# include <utility>
# include <list>
# include <unordered_map>
# include <unordered_set>
# include <queue>
# include <stack>
# include <map>
# include <set>
# include <fstream>
# include <ios>
# include <string>
# include <exception>

/*** Sockets dependencies ***/

# include <sys/socket.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <netdb.h>
# include <sys/event.h>

// # define cout std::cout
// # define cin std::cin
// # define fstream std::fstream
// # define ifstream std::ifstream
// # define string std::string
// # define vector std::vector
// # define list std::list
// # define map std::map
// # define set std::set
// # define unordered_map std::unordered_map
// # define unordered_set std::unordered_set

# define PORT short int
# define SOCKET int
# define HashMap std::unordered_map
# define HashSet std::unordered_set

# define SA struct sockaddr
# define SA_IN struct sockaddr_in
# define SOCKET_NOT_DEFINED 0

typedef struct kevent k_event;

# define sz(x) ((int)x.size())

enum TOKEN
{
    SHORT_INT,
    INT,
    DIRECTORY,
    STRING,
    STRING_VECTOR,
    METHOD,
    METHOD_VECTOR,
    ON_OFF,
    CONNECTION 
} ;

enum MULTIPLEXER
{
    KQUEUE,
    POLL,
    SELECT,
    EPOLL
} ;

// std::string PARSING_ERROR;
# endif