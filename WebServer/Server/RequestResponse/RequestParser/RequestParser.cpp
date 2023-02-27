# include "RequestParser.hpp"

RequestParser::RequestParser()
{
    init_token_types();
    return ;
}

RequestParser::RequestParser(const RequestParser &r)
{
    init_token_types();
    return ;
}

RequestParser& RequestParser::operator=(const RequestParser &r)
{
    init_token_types();
    return (*this) ;
}

RequestParser::~RequestParser()
{
    init_token_types();
    return ;
}

void    RequestParser::init_token_types()
{
    token_types.insert(std::make_pair("connection", STRING));
    token_types.insert(std::make_pair("content-length", INT));
    token_types.insert(std::make_pair("accept", STRING_VECTOR));
    token_types.insert(std::make_pair("host", STRING));
    token_types.insert(std::make_pair("accept-encoding", STRING_VECTOR));
    token_types.insert(std::make_pair("user-agent", STRING));
}

void    RequestParser::parse_string_token(t_request *req, std::string &first, std::string &second)
{
    req->header_map.insert(std::make_pair(first, second));
    req->header_map.insert(std::make_pair(first, second));
}

void    RequestParser::parse_int_token(t_request *req, std::string &first, std::string &second)
{
    req->header_map_ints.insert(std::make_pair(first, std::stoi(second)));
    req->header_map.insert(std::make_pair(first, second));
}

void    RequestParser::parse_string_vector_token(t_request *req, std::string &first, std::string &second, char splitter)
{
    std::vector<std::string>    vec;

    for (int i = 0; i < sz(second); i++)
    {
        int j = i;
        for (;i < sz(second) && second[i] != splitter; i++);
        std::string s = second.substr(j, i - j);
        vec.push_back(s);
        i += (i < sz(second) && second[i] == splitter);
    }
    req->header_map_vec.insert(std::make_pair(first, vec));
    req->header_map.insert(std::make_pair(first, second));
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
    for (auto x : req->header_map)
        std::cout << x.first << " -> " << x.second << std::endl;
    std::cout << "****** end printing the request ******\n" << std::endl;
}

void    RequestParser::read_request(SOCKET fd, t_request *req) // should set true if request header was entirely read
{
    char    buff[BUFFER_SIZE];
    char    *line;
    int     len;
    std::string s;
    bool    is_header_complete = false;

    std::cout << "Got here and currently reading" << std::endl;
    while (1)
    {
        line = get_next_line(fd);
        std::cout << line;
        if (!line)
            break ;
        s = line;
        is_header_complete = (s == "\r\n");
        if (is_header_complete)
            break ;
        req->header_lines.push_back(s);
        req->request_len += sz(s);
        if (line)
            free(line);
    }
    std::cout << "   ***************    " << std::endl;
    req->is_header_complete = is_header_complete;
}


void    RequestParser::parse_line(std::string &s, t_request *req)
{
    int i, j;
    std::string first;
    std::string second;

    i = 0;
    for (i = 0; i < sz(s) && s[i] != ':'; i++);
    if (i == sz(s))
        return ;
    for (j = sz(s) - 1; j >= 0 && isspace(s[j]); j--);
    j++;
    first = s.substr(0, i);
    for (; i < sz(s) && isspace(s[i]); i++);
    second = s.substr(i, j - i);
    for (j = 0; j < sz(first); j++) // lowercasing the first string
        first[j] = (isalpha(first[j]) ? tolower(first[j]) : first[j]);
    for (j = 0; j < sz(second); j++) // lowercasting the second string
        second[j] = (isalpha(second[j]) ? tolower(second[j]) : second[j]);
    req->header_map.insert(std::make_pair(first, second));
    // TOKEN type = token_types[first];
    // // req->header_map.insert(std::make_pair(first, second));
    // if (type == STRING)
    //     parse_string_token(req, first, second);
    // else if (type == INT)
    //     parse_int_token(req, first, second);
    // else if (type == STRING_VECTOR)
    //     parse_string_vector_token(req, first, second, ',');
}

void    RequestParser::parse_first_line(std::string &first_line, t_request *req)
{
    std::string method;
    std::string path;
    std::string http_version;
    int i = 0, j = 0;

    for (; i < sz(first_line) && isspace(first_line[i]); i++);
    j = i;
    for (; i < sz(first_line) && !isspace(first_line[i]); i++);
    method = first_line.substr(j, i - j);
    for (; i < sz(first_line) && isspace(first_line[i]); i++);
    j = i;
    for (; i < sz(first_line) && !isspace(first_line[i]); i++);
    path = first_line.substr(j, i - j);
    for (; i < sz(first_line) && isspace(first_line[i]); i++);
    j = i;
    for (; i < sz(first_line) && !isspace(first_line[i]); i++);
    http_version = first_line.substr(j, i - j);
    for (i = 0; i < sz(method); i++)
        method[i] = (isalpha(method[i]) ? toupper(method[i]) : method[i]);
    for (i = 0; i < sz(http_version); i++)
        http_version[i] = (isalpha(http_version[i]) ? toupper(http_version[i]) : http_version[i]);
    req->method = method;
    req->path = path;
    req->http_version = http_version;
}

void    RequestParser::print_header(t_request *req)
{
    std::cout << " **** start request header **** " << std::endl;
    std::cout << "Method: " << req->method << std::endl;
    std::cout << "Path: " << req->path << std::endl;
    std::cout << "Http_Version: " << req->http_version << std::endl;
    std::cout << "    ---- START HEADER LINES ----";
    for (auto x: req->header_map)
        std::cout << x.first << ": " << x.second << std::endl;
    std::cout << "    ---- END HEADER LINES ----";
    std::cout << " **** end request header   **** " << std::endl;
}

void    RequestParser::parse_request(t_socket *client) // main function in this class 
{
    if (!client->request->is_header_complete)
        read_request(client->fd, client->request);
    if (client->request->is_header_complete)
    {
        std::vector<std::string> *lines = &client->request->header_lines;
        for (int i = 0; i < sz((*lines)); i++)            
            ((i == 0) ? parse_first_line(lines->at(i), client->request) : parse_line(lines->at(i), client->request));
        print_header(client->request);
    }
}