# include "RequestResponse.hpp"

RequestResponse::RequestResponse() : parser(0)
{
    parser = new RequestParser();
}

RequestResponse::RequestResponse(const RequestResponse &r) : parser(0)
{
    parser = new RequestParser();
}

RequestResponse::RequestResponse(t_http_configs *h, t_server_configs *s, \
HashMap<std::string, t_location_configs> *d_c)
{
    this->http_configs = h;
    this->server_configs = s;
    this->dir_configs = d_c;
}

RequestResponse& RequestResponse::operator=(const RequestResponse &r)
{
    return *this ;
}

RequestResponse::~RequestResponse()
{
    if (parser)
        delete parser;
    return ;
}

t_request *RequestResponse::parse_request(int fd)
{
    return (parser->parse_request(fd));
}