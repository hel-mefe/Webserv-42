# include "RequestParser.hpp"

RequestParser::RequestParser()
{
    return ;
}

RequestParser::RequestParser(const RequestParser &r)
{
    return ;
}

RequestParser& RequestParser::operator=(const RequestParser &r)
{
    return (*this) ;
}

RequestParser::~RequestParser()
{
    return ;
}


std::vector<std::string>* RequestParser::get_request_as_vector(int fd)
{
    std::vector<std::string> *res = new std::vector<std::string>();

    while (true)
    {
        char *line = get_next_line(fd);
        if (!line)
            break ;
        std::string l = line;
        free(line);
        if (l == "\r\n")
            break ;
        res->push_back(l);
    }
    return (res);
}

void    RequestParser::set_identifier_value(t_request *req, std::string &id, std::string &value)
{
    if (id == "Content-length")
        req->content_length = std::stoi(value);
    else if (id == "Connection")
        req->connection = value;
}

void    RequestParser::set_request_line(t_request *req, std::string &res)
{
    std::string     id;
    std::string     value;
    int split_point = 0;

    while (split_point < sz(res) && res[split_point] != ':') // suppose you find the ':' character
        split_point++;
    if (split_point == sz(res))
        return ;
    id = res.substr(0, split_point);
    split_point++;
    while (split_point < sz(res) && isspace(res[split_point]))
        split_point++;
    value = res.substr(split_point, sz(res) - split_point - (res[sz(res) - 1] == '\n'));
    set_identifier_value(req, id, value);
}

void    RequestParser::parse_first_line(t_request *req, std::string &line)
{
    std::string method;
    std::string path;
    std::string http_version;
    int i;

    for (i = 0; i < sz(line) && !isspace(line[i]); i++)
        method += line[i];
    for (; i < sz(line) && isspace(line[i]); i++);
    for (; i < sz(line) && !isspace(line[i]); i++)
        path += line[i];
    for (; i < sz(line) && isspace(line[i]); i++);
    for (; i < sz(line) && !isspace(line[i]); i++)
        http_version += line[i];
    req->method = method;
    req->path = path;
    req->http_version = http_version;
}

t_request* RequestParser::get_request(std::vector<std::string> &res)
{
    t_request *req = new t_request();

    if (!sz(res))
        return (req);
    parse_first_line(req, res[0]);
    for (int i = 1; i < sz(res); i++)
        set_request_line(req, res[i]);
    return (req);
}

void    print_vector(std::vector<std::string> &vec)
{
    std::cout << " ******** This is the request vector ****** " << std::endl;
    for (int i = 0; i < sz(vec); i++)
    {
        std::cout << vec[i] << std::endl;
    }
    std::cout << " ******** End of vector ****** " << std::endl;
}

t_request* RequestParser::parse_request(int fd)
{
    std::vector<std::string>    *reqs;
    t_request                     *result;

    reqs = get_request_as_vector(fd); // every request will be broken down into a vector
    print_vector(*reqs);
    result = get_request(*reqs); // from that vector we can extract all the data into a struct named header
    delete reqs;
    return (result);
}