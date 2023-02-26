# include "RequestResponse.hpp"

void    RequestResponse::init_status_codes()
{
    // 100 - 199 Informational
    status_codes.insert(std::make_pair(100, "Continue"));
    status_codes.insert(std::make_pair(101, "Switching protocols"));
    status_codes.insert(std::make_pair(102, "Processing"));
    status_codes.insert(std::make_pair(103, "Early Hints"));
    // 200 - 299 Successful
    status_codes.insert(std::make_pair(200, "OK"));
    status_codes.insert(std::make_pair(201, "Created"));
    status_codes.insert(std::make_pair(202, "Accepted"));
    status_codes.insert(std::make_pair(203, "Non-Authoritative Information"));
    status_codes.insert(std::make_pair(204, "No Content"));
    status_codes.insert(std::make_pair(205, "Reset Content"));
    status_codes.insert(std::make_pair(206, "Partial Content"));
    status_codes.insert(std::make_pair(207, "Multi-Status"));
    status_codes.insert(std::make_pair(208, "Already Reported"));
    status_codes.insert(std::make_pair(226, "IM Used"));
    // 300 - 399 Redirection
    status_codes.insert(std::make_pair(300, "Multiple Choices"));
    status_codes.insert(std::make_pair(301, "Moved Permanently"));
    status_codes.insert(std::make_pair(302, "Found"));
    status_codes.insert(std::make_pair(303, "See Other"));
    status_codes.insert(std::make_pair(304, "Not Modified"));
    status_codes.insert(std::make_pair(305, "Use Proxy"));
    status_codes.insert(std::make_pair(306, "Switch Proxy"));
    status_codes.insert(std::make_pair(307, "Temporary Redirect"));
    status_codes.insert(std::make_pair(308, "Permanent Redirect"));
    // 400 - 499 Client Error
    status_codes.insert(std::make_pair(400, "Bad Request"));
    status_codes.insert(std::make_pair(401, "Unauthorized"));
    status_codes.insert(std::make_pair(402, "Payment Required"));
    status_codes.insert(std::make_pair(403, "Forbidden"));
    status_codes.insert(std::make_pair(404, "Not Found"));
    status_codes.insert(std::make_pair(405, "Method Not Allowed"));
    status_codes.insert(std::make_pair(406, "Not Acceptable"));
    status_codes.insert(std::make_pair(407, "Proxy Authentication Required"));
    status_codes.insert(std::make_pair(408, "Request Timeout"));
    status_codes.insert(std::make_pair(409, "Conflict"));
    status_codes.insert(std::make_pair(410, "Gone"));
    status_codes.insert(std::make_pair(411, "Length Required"));
    status_codes.insert(std::make_pair(412, "Precondition Failed"));
    status_codes.insert(std::make_pair(413, "Payload Too Large"));
    status_codes.insert(std::make_pair(414, "URI Too Long"));
    status_codes.insert(std::make_pair(413, "Payload Too Large"));
    status_codes.insert(std::make_pair(414, "URI Too Long"));
    status_codes.insert(std::make_pair(415, "Unsupported Media Type"));
    status_codes.insert(std::make_pair(416, "Range Not Satisfiable"));
    status_codes.insert(std::make_pair(417, "Expectation Failed"));
    status_codes.insert(std::make_pair(418, "I'm a Teapot"));
    status_codes.insert(std::make_pair(421, "Misdirected Request"));
    status_codes.insert(std::make_pair(422, "Unprocessable Entity"));
    status_codes.insert(std::make_pair(423, "Locked"));
    status_codes.insert(std::make_pair(424, "Failed Dependency"));
    status_codes.insert(std::make_pair(425, "Too Early"));
    status_codes.insert(std::make_pair(426, "Upgrade Required"));
    status_codes.insert(std::make_pair(428, "Precondition Required"));
    status_codes.insert(std::make_pair(429, "Too Many Requests"));
    status_codes.insert(std::make_pair(431, "Request Header Fields Too Large"));
    status_codes.insert(std::make_pair(451, "Unavailable For Legal Reasons"));
    // 500 - 511 Server Error
    status_codes.insert(std::make_pair(500, "Internal Server Error"));
    status_codes.insert(std::make_pair(501, "Not Implemented"));
    status_codes.insert(std::make_pair(502, "Bad Gateway"));
    status_codes.insert(std::make_pair(503, "Service Unavailable"));
    status_codes.insert(std::make_pair(504, "Gateway Timeout"));
    status_codes.insert(std::make_pair(505, "HTTP Version Not Supported"));
    status_codes.insert(std::make_pair(506, "Variant Also Negotiates"));
    status_codes.insert(std::make_pair(507, "Insufficient Storage"));
    status_codes.insert(std::make_pair(508, "Loop Detected"));
    status_codes.insert(std::make_pair(510, "Not Extended"));
    status_codes.insert(std::make_pair(511, "Network Authentication Required"));
}
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

// t_request *RequestResponse::parse_request(int fd)
// {
//     return (parser->parse_request(fd));
// }


void    RequestResponse::print_request(t_request *req)
{
    std::cout << "****** printing the request ******\n" << std::endl;
    std::cout << "is header complete: " << ((req->is_header_complete) ? "True" : "False") << std::endl;
    for (auto x : req->request_map)
        std::cout << x.first << " -> " << x.second << std::endl;
    std::cout << "****** end printing the request ******\n" << std::endl;
}

void    RequestResponse::read_request(SOCKET fd, t_request *req)
{
    char    buff[BUFFER_SIZE];
    char    *line = get_next_line(fd);
    int     len;
    std::string s;
    bool    is_header_complete = false;

    if (!line)
        return ;
    s = std::string(line);
    if (s == "\r\n")
    {
        req->is_header_complete = true;
        return ;
    }
    std::cout << "Got here and currently reading" << std::endl;
    while (1)
    {
        line = get_next_line(fd);
        std::cout << line << std::endl;
        if (!line)
            break ;
        s = line;
        std::cout << "string: " << s << std::endl;
        req->request_lines.push_back(s);
        req->request_len += sz(s);
        if (line)
            free(line);
        is_header_complete = (s == "\r\n");
        if (is_header_complete)
            break ;
    }
    std::cout << "   ***************    " << std::endl;
    req->is_header_complete = is_header_complete;
}


void    RequestResponse::parse_line(std::string &s, t_request *req)
{
    int i;
    std::string first;
    std::string second;

    i = 0;
    for (; i < sz(s) && isspace(s[i]); i++); // skipping white spaces at the beginning
    for (; i < sz(s) && s[i] != ':' && !isspace(s[i]) ; i++); // taking till ':'
    first = s.substr(0, i);
    for (int j = 0; j < sz(first); j++) // lowercasing the first string
        first[j] = (isalpha(first[j]) ? tolower(first[j]) : first[j]);
    for (; i < sz(s) && isspace(s[i]); i++); // skipping white spaces
    i += (i < sz(s) && s[i] == ':'); // taking one step forward if i == ':'
    second = s.substr(i, sz(s) - i);
    for (int j = 0; j < sz(second); j++) // lowercasting the second string
        second[j] = (isalpha(second[j]) ? tolower(second[j]) : second[j]); 
    req->request_map.insert(std::make_pair(first, second)); // (first -> second)
}

void    RequestResponse::parse_client_request(t_socket *client)
{
    if (!client->request->is_header_complete)
        read_request(client->fd, client->request);
    if (client->request->is_header_complete)
    {
        std::vector<std::string> *lines = &client->request->request_lines;
        for (int i = 0; i < sz((*lines)); i++)
            parse_line(lines->at(i), client->request);
        print_request(client->request);
    }
}