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


// std::vector<std::string>* RequestParser::get_request_as_vector(int fd)
// {
//     std::vector<std::string> *res = new std::vector<std::string>();

//     while (true)
//     {
//         char *line = get_next_line(fd);
//         if (!line)
//             break ;
//         std::string l = line;
//         free(line);
//         if (l == "\r\n")
//             break ;
//         res->push_back(l);
//     }
//     return (res);
// }

// void    RequestParser::set_identifier_value(t_request *req, std::string &id, std::string &value)
// {
//     if (id == "Content-length")
//         req->content_length = std::stoi(value);
//     else if (id == "Connection")
//         req->connection = value;
// }

// void    RequestParser::set_request_line(t_request *req, std::string &res)
// {
//     std::string     id;
//     std::string     value;
//     int split_point = 0;

//     while (split_point < sz(res) && res[split_point] != ':') // suppose you find the ':' character
//         split_point++;
//     if (split_point == sz(res))
//         return ;
//     id = res.substr(0, split_point);
//     split_point++;
//     while (split_point < sz(res) && isspace(res[split_point]))
//         split_point++;
//     value = res.substr(split_point, sz(res) - split_point - (res[sz(res) - 1] == '\n'));
//     set_identifier_value(req, id, value);
// }

// void    RequestParser::parse_first_line(t_request *req, std::string &line)
// {
//     std::string method;
//     std::string path;
//     std::string http_version;
//     int i;

//     for (i = 0; i < sz(line) && !isspace(line[i]); i++)
//         method += line[i];
//     for (; i < sz(line) && isspace(line[i]); i++);
//     for (; i < sz(line) && !isspace(line[i]); i++)
//         path += line[i];
//     for (; i < sz(line) && isspace(line[i]); i++);
//     for (; i < sz(line) && !isspace(line[i]); i++)
//         http_version += line[i];
//     req->method = method;
//     req->path = path;
//     req->http_version = http_version;
// }

// t_request* RequestParser::get_request(std::vector<std::string> &res)
// {
//     t_request *req = new t_request();

//     if (!sz(res))
//         return (req);
//     parse_first_line(req, res[0]);
//     for (int i = 1; i < sz(res); i++)
//         set_request_line(req, res[i]);
//     return (req);
// }

// void    print_vector(std::vector<std::string> &vec)
// {
//     std::cout << " ******** This is the request vector ****** " << std::endl;
//     for (int i = 0; i < sz(vec); i++)
//     {
//         std::cout << vec[i] << std::endl;
//     }
//     std::cout << " ******** End of vector ****** " << std::endl;
// }

// t_request* RequestParser::parse_request(int fd)
// {
//     std::vector<std::string>    *reqs;
//     t_request                     *result;

//     reqs = get_request_as_vector(fd); // every request will be broken down into a vector
//     print_vector(*reqs);
//     result = get_request(*reqs); // from that vector we can extract all the data into a struct named header
//     delete reqs;
//     return (result);
// }

void    RequestParser::print_request(t_request *req)
{
    std::cout << "****** printing the request ******\n" << std::endl;
    std::cout << "is header complete: " << ((req->is_header_complete) ? "True" : "False") << std::endl;
    for (auto x : req->request_map)
        std::cout << x.first << " -> " << x.second << std::endl;
    std::cout << "****** end printing the request ******\n" << std::endl;
}

void    RequestParser::read_request(SOCKET fd, t_request *req)
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


void    RequestParser::parse_line(std::string &s, t_request *req)
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
    // if (token_types.find(first) == token_types.end())
    // {
    //     std::cout << "Token type was not found!" << std::endl;
    //     return ;
    // }
    // TOKEN type = token_types[first];
    req->request_map.insert(std::make_pair(first, second));
    // if (type == STRING)
    //     req->request_map.insert(std::make_pair(first, second)); // (first -> second)
    // else if (type == INT)
    //     req->request_map_ints.insert(std::make_pair(first, std::stoi(second)));
    // else if (type == STRING_VECTOR)
    //     req->request_map_vec.insert(std::make_pair(first, std::vector))
}

void    RequestParser::parse_request(t_socket *client) // main function in this class 
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