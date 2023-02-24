#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include "Header.hpp"

class PortAlreadyUsed : public std::exception
{
    public:
        const char *what() const _NOEXCEPT
        {
            return ("Port is already been used by another server");
        }
} ;

class InvalidMethod : public std::exception
{
    public:
        const char *what() const _NOEXCEPT
        {
            return ("Invalid method has been provided in the configuration file");
        }
} ;

class InvalidHttpToken : public std::exception
{
    public:
        const char *what() const _NOEXCEPT
        {
            return ("Invalid http token has been provided in the configuration file");
        }
} ;


# endif