#ifndef REQUEST_RESPONSE_HPP
# define REQUEST_RESPONSE_HPP

# include "RequestParser/RequestParser.hpp"
# include "ResponseBuilder/ResponseBuilder.hpp"

class RequestResponse
{
    private:
        RequestParser                               *parser; // parses the request and returns t_request
        ResponseBuilder                             *builder; // takes t_response and builds the response from it
        t_http_configs                              *http_configs;
        t_server_configs                            *server_configs;
        HashMap<std::string, t_location_configs>   *dir_configs;
    public:
        RequestResponse();
        RequestResponse(t_http_configs *h, t_server_configs *s, HashMap<std::string, t_location_configs> *d_c);
        RequestResponse(const RequestResponse& r);
        RequestResponse& operator=(const RequestResponse& r);
        ~RequestResponse();

        t_request   *parse_request(int fd);
        t_response  *get_response(t_request *req);
} ;

# endif