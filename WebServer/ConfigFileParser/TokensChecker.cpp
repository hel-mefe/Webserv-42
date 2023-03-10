# include "TokensChecker.hpp"

# define MAX_SHORT_INT 65536

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

TokensChecker::TokensChecker()
{
    return ;
}

TokensChecker::TokensChecker(const TokensChecker& c)
{
    return ;
}

TokensChecker& TokensChecker::operator=(const TokensChecker &c)
{
    return *this ;
}

TokensChecker::~TokensChecker()
{
    return ;
}

bool TokensChecker::is_directory(std::string s)
{
    return (sz(s) && s[0] == '/');
}

bool TokensChecker::is_short_int(std::string s)
{
    int i = 0, num = 0;

    if (!is_int(s))
        return (false);
    num = std::stoi(s);
    return (num < MAX_SHORT_INT);
}

bool TokensChecker::is_int(std::string s)
{
    for (int i = 0; i < sz(s); i++)
    {
        if (!is_digit(s[i]))
            return (false);
    }
    return (true);
}

bool TokensChecker::is_method(std::string s)
{
    return (s == "GET" || s == "POST" || s == "DELETE");
}

bool TokensChecker::is_on_off(std::string s)
{
    return (s == "on" || s == "off");
}

bool TokensChecker::is_connection(std::string s)
{
    return (s == "keep-alive" || s == "close");
}