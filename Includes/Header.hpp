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

// std::string PARSING_ERROR;
# endif