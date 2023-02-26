#ifndef REQUEST_PARSER_HPP
# define REQUEST_PARSER_HPP

# include "../../../../Includes/Header.hpp"
# include "../../../../Includes/Structures.hpp"
# include "../../../gnl/get_next_line.h"

class RequestParser
{
    private:
    
    public:
        RequestParser();
        RequestParser(const RequestParser& );
        RequestParser& operator=(const RequestParser&);
        ~RequestParser();

        std::vector<std::string>*   get_request_as_vector(int fd);
        void                        set_identifier_value(t_request *request, std::string &id, std::string &value);
        void                        set_request_line(t_request *request, std::string &res);
        void                        parse_first_line(t_request *request, std::string &line);
        
        t_request *get_request(std::vector<std::string> &res);
        t_request *parse_request(int fd);
} ;

#endif