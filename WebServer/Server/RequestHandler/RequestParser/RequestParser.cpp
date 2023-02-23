# include "RequestParser.hpp"

# define BUFFER_SIZE 2048

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
    std::vector<std::string> res = new std::vector<std::string>();

    while (true)
    {
        char *line = get_next_line(fd);
        std::string l = line;
        free(line);
        if (l == "\r\n")
            break ;
        res->push_back(l);
    }
    return (res);
}

void    RequestParser::set_identifier_value(header *request, std::string &id, std::string &value)
{
    if (id == "Content-length")
        request->content_length = std::stoi(value);
    else if (id == "Connection")
        request->connection = value;
}

void    RequestParser::set_header_line(header *request, std::string &res)
{
    std::string     id;
    std::string     value;
    int split_point = 0;

    while (split_point < sz(res) && res[split_point] != ':') // suppose you find the ':' character
        split_point++;
    if (split_point == sz(res))
        return ;
    split_point++;
    id = res.substr(0, split_point);
    value = res.substr(split_point, sz(res) - split_point + 1);
    set_identifier_value(request, id, value);
}

header* RequestParser::get_request_header(std::vector<std::string> &res)
{
    header *res = new header();

    for (int i = 0; i < sz(res); i++)
        set_header_line(header, res[i]);
    return (header);
}

header* RequestParser::parse_request(int fd)
{
    std::vector<std::string>    *request;
    header                      *result;

    request = get_request_as_vector(fd); // every request will be broken down into a vector
    result = get_request_header(request); // from that vector we can extract all the data into a struct named header
    return (result);
}