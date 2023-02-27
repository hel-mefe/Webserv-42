#ifndef REQUEST_PARSER_HPP
# define REQUEST_PARSER_HPP

# include "../../../../Includes/Header.hpp"
# include "../../../../Includes/Structures.hpp"
# include "../../../gnl/get_next_line.h"

/****
 * All the work of the parsing will go here
 * Take your fuuuuuull liberty to add anything useful just keep it in the context
 * of request parsing
*/

class RequestParser
{
    private:
        HashMap<std::string, TOKEN> token_types;
    public:
        RequestParser();
        RequestParser(const RequestParser& );
        RequestParser& operator=(const RequestParser&);
        ~RequestParser();

        // std::vector<std::string>*   get_request_as_vector(int fd);
        // void                        set_identifier_value(t_request *request, std::string &id, std::string &value);
        // void                        set_request_line(t_request *request, std::string &res);
        // void                        parse_first_line(t_request *request, std::string &line);
        
        // t_request *get_request(std::vector<std::string> &res);
        // t_request *parse_request(int fd);

        void    print_header(t_request *req);
        void    read_request(SOCKET fd, t_request *req);
        void    parse_line(std::string &s, t_request *req);
        void    parse_request(t_socket *client);
        void    print_request(t_request *req);

        void    init_token_types();
        void    parse_first_line(std::string &first_line, t_request *req);

        void    parse_string_vector_token(t_request *req, std::string &first, std::string &second, char splitter);
        void    parse_string_token(t_request *req, std::string &first, std::string &second);
        void    parse_int_token(t_request *req, std::string &first, std::string &second);

} ;

#endif