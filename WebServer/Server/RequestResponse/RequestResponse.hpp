#ifndef REQUEST_RESPONSE_HPP
# define REQUEST_RESPONSE_HPP

# include "RequestParser/RequestParser.hpp"
# include "ResponseBuilder/ResponseBuilder.hpp"
# include "../../../Includes/Structures.hpp"
# include "MethodHandler/MethodHandler.hpp"

class RequestResponse
{
    private:
        RequestParser                               *request_parser; // parses the request and returns t_request
        ResponseBuilder                             *response_builder; // takes t_response and builds the response from it
        MethodHandler                               *method_handler; // each request has a method and has a function that handles it here
        t_http_configs                              *http_configs;
        t_server_configs                            *server_configs;
        HashMap<std::string, t_location_configs>    *dir_configs;
        HashMap<int, std::string>                   status_codes;
        HashMap<std::string, TOKEN>                 token_types;
    public:
        RequestResponse();
        RequestResponse(t_http_configs *h, t_server_configs *s, HashMap<std::string, t_location_configs> *d_c);
        RequestResponse(const RequestResponse& r);
        RequestResponse& operator=(const RequestResponse& r);
        ~RequestResponse();

        void        init_status_codes();
        void        init_token_types();
        // t_request   *parse_request(int fd);
        // t_request   *parse_client_request(t_socket *client);
        // t_response  *get_response(t_request *req);

        void    read_request(SOCKET fd, t_request *req);
        void    parse_line(std::string &s, t_request *req);
        void    parse_client_request(t_socket *client);
        void    print_request(t_request *req);

        void    build_response();
} ;

# endif