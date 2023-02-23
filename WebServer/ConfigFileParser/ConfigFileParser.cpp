# include "ConfigFileParser.hpp"

ConfigFileParser::ConfigFileParser()
{
    return ;
}

ConfigFileParser::ConfigFileParser(std::string config_name)
{
    config_file = config_name;
}

ConfigFileParser::ConfigFileParser(const ConfigFileParser& p)
{
    config_file = p.get_config_file();
}

std::string  ConfigFileParser::get_config_file() const
{
    return (config_file);
}

ConfigFileParser::~ConfigFileParser()
{
    return ;
}

void    ConfigFileParser::extract_lines_from_file(std::fstream &f_stream, std::vector<std::string> &lines)
{
    while (f_stream.good())
    {
        std::string line;
    
        std::getline(f_stream, line);
        lines.push_back(line);
    }
}

void    ConfigFileParser::print_vector_lines(std::vector<std::string> &lines)
{
    for (int i = 0; i < (int)lines.size(); i++)
        std::cout << lines[i] << std::endl ;
}

std::vector<std::string>    ConfigFileParser::get_word_vector(std::string &line)
{
    std::vector<std::string> word;
    bool flag = false;
    int last = 0, i = 0;
    for (; i < (int)line.size(); i++)
    {
        if (isspace(line[i]) || line[i] == '}' || line[i] == '{')
        {
            if (flag)
            {
                std::string w = line.substr(last, (i - last));
                word.push_back(w);
                flag = false;
            }
            if (line[i] == '}' || line[i] == '{')
            {
                std::string w;
                w += line[i];
                word.push_back(w);
            }
        }
        else if (!isspace(line[i]) && !flag)
            flag = true, last = i;
    }
    if (flag)
    {
        std::string w = line.substr(last, i - last);
        word.push_back(w);
    }
    return (word);
}

void    ConfigFileParser::print_words(std::vector<std::vector<std::string> > words)
{
    for (int i = 0; i < (int)words.size(); i++)
    {
        std::cout << "[" ;
        for (int j = 0; j < (int)words[i].size(); j++)
            std::cout << words[i][j] << " " ;
        std::cout << "]" << std::endl ;
    }
}

void    ConfigFileParser::extract_words_from_lines(std::vector<std::vector<std::string> > &words)
{
    std::vector<std::string> word;

    // std::cout << "LINES VEC = " << lines.size() << std::endl ;
    for (int i = 0; i < (int)lines.size(); i++)
    {
        word = get_word_vector(lines[i]);
        if (word.size()) // if the line is empty it will get ignored
            words.push_back(word);
        word.clear();
    }
    // print_words(words);
}

bool is_brackets_correct(std::vector<std::vector<std::string> > &words)
{
    std::stack<char> st;

    for (int i = 0; i < sz(words); i++)
    {
        for (int j = 0; j < sz(words[i]); j++)
        {
            if (words[i][j] == "{")
                st.push('{');
            else if (words[i][j] == "}")
            {
                if (st.empty() || st.top() != '{')
                    return false ;
                st.pop();
            }
        }
    }
    return st.empty();
}

bool is_bracket(std::string &s)
{
    return (s == "{" || s == "}");
}

void    ConfigFileParser::build_brackets_queue()
{
    for (int i = 0; i < sz(words); i++)
    {
        for (int j = 0; j < sz(words[i]); j++)
        {
            if (is_bracket(words[i][j]))
            {
                brackets_q.push_back(std::make_pair(words[i][j], std::make_pair(i, j)));
                // std::cout << words[i][j] << " " << i << " " << j << std::endl ;
            }
        }
    }
}

std::string ConfigFileParser::get_str(std::vector<std::vector<std::string> > &vec, int i, int end_i, int j, int end_j)
{
    std::string res;
    while (i <= end_i)
    {
        while (j < sz(words[i]))
        {
            if (i == end_i && j > end_j)
                break ;
            res += words[i][j];
            j++;
        }
        j = 0;
        i++;
    }

    return (res);
}

std::string    ConfigFileParser::get_identifier(std::pair<int, int> &start, std::pair<int, int> &end)
{
    std::string id;

    int i = start.first, end_i = end.first;
    int j = start.second + is_bracket(words[start.first][start.second]), end_j = end.second;
    // while (i <= end_i)
    // {
    //     while (j < sz(words[i]))
    //     {
    //         if (i == end_i && j >= end_j) // end_j is a bracket I don't want to include it in
    //             break ;
    //         id += words[i][j];
    //         j++;
    //     }
    //     j = 0;
    //     i++;
    // }
    i = end_i;
    j = end_j;
    bool found = false;
    while (i >= start.first && !found)
    {
        if (i == end_i)
            j = end_j;
        else
            j = sz(words[i]) - 1;
        while (j >= 0 && !found)
        {
            if (words[i][j] != "{" && words[i][j] != "}")
                id = words[i][j], found = true;
            j--;
        }
        i--;
    }
    return id;
}

void    ConfigFileParser::fill_words(std::vector<std::vector<std::string> > &n_words, \
std::pair<int, int> &start, std::pair<int, int> &end)
{
    int i = start.first, end_i = end.first;
    int j = start.second + 1, end_j = end.second;

    while (i < end.first)
    {
        std::vector<std::string> line_words;
        while (j < sz(words[i]))
        {
            if (i == end.first && j >= end_j)
                break ;
            line_words.push_back(words[i][j]);
            j++;
        }
        if (sz(line_words))
            n_words.push_back(line_words);
        j = 0;
        i++;
    }
}

void    ConfigFileParser::push_node(std::pair<int, int> prev, std::pair<int, int> &mid, std::pair<int, int> &end)
{
    t_node node;

    node.id = get_identifier(prev, mid);
    if (!node.id.length())
    {
        std::cout << "ERROR OF NODE IDENTIFIER" << std::endl;
        exit(2);
    }
    fill_words(node.words, mid, end);
    nodes.push_back(node);
}

void    ConfigFileParser::build_with_vector(std::vector<std::string> &vec, int i, int j)
{
    // int oldi = i, oldj = j;
    // while (i < sz(words))
    // {
    //     while (j < sz(words[i]))
    //     {
    //         if (is_bracket(words[i][j]))
    //         {
    //             if (words[i][j] == "{")
    //             {
    //                 build_with_vector(vec, i, j + 1);
    //                 return ;
    //             }
    //             else
    //             {
    //                 vec.push_back(get_str(words, oldi, i, oldj, j));
    //                 return ;
    //             }
    //         }
    //         j++;
    //     }
    //     j = 0;
    //     i++;
    // }
    // int start_i = brackets_q[0].second.first, end_i = brackets_q[sz(brackets_q) - 1].second.first;
    // int start_j = brackets_q[0].second.second, end_j = brackets_q[sz(brackets_q) - 1].second.second;
    // std::string ss = get_str(words, start_i, end_i, start_j, end_j);
    // vec.push_back(ss);
    std::pair<int, int> first_all = std::make_pair(0, 0);
    push_node(first_all, brackets_q[0].second, brackets_q[sz(brackets_q) - 1].second);
    for (int i = 1; i < sz(brackets_q) - 1; i += 2)
    {
        // start_i = brackets_q[i].second.first, end_i = brackets_q[i + 1].second.first;
        // start_j = brackets_q[i].second.second, end_j = brackets_q[i + 1].second.second;
        push_node(brackets_q[i - 1].second, brackets_q[i].second, brackets_q[i + 1].second);
    }
}

void    ConfigFileParser::print_nodes()
{
    for (int i = 0; i < sz(nodes); i++)
    {
        std::cout << "Identifier: " << nodes[i].id << std::endl;
        std::cout << "NODE WORDLINE FOR NODE (  " << i << " ) => " << std::endl;
        for (int j = 0; j < sz(nodes[i].words); j++)
        {
            for (int k = 0; k < sz(nodes[i].words[j]); k++)
              std::cout << nodes[i].words[j][k] << " " ;
            std::cout << std::endl;
        }
        std::cout << std::endl ;
    }
}

// bool ConfigFileParser::parse_words()
// {
//     bool is_http_found = false;
//     for (int i = 0; i < sz(words); i++)
//     {
//         for (int j = 0; j < sz(words[i]); j++)
//         {
//             if (words[i][j] == "http" || words[i][j] == "https")
//                 parse_http_line(), is_http_found = true;
//             else if (is_http_found())
//         }
//     }
// }

void    ConfigFileParser::parse_http_configs(int &i, int &j)
{
    if (i >= sz(words))
        return ;
    int http_index = sz(http_as_words);
    while (i < sz(words))
    {
        std::vector<std::string> line_words;
        http_as_words.push_back(line_words);
        while (j < sz(words[i]) && !is_bracket(words[i][j]))
        {
            if (j < sz(words[i]) - 1 && words[i][j + 1] == "{")
                break ;
            else if (i < sz(words) && words[i + 1][0] == "{")
                break ;
            http_as_words[http_index].push_back(words[i][j]);
            j++;
        }
        if (!sz(http_as_words[sz(http_as_words) - 1]))
            http_as_words.pop_back() ;
        // if (!sz(line_words) && sz(http_as_words))
        //     http_as_words.pop_back();
        if ((j < sz(words[i]) && is_bracket(words[i][j])) || \
        (j < sz(words[i]) - 1 && is_bracket(words[i][j + 1])))
            break ;
        j = 0;
        http_index++;
        i++;
    }
    // http_as_words.pop_back();
    // parse_http_words(http_words);
}

void    ConfigFileParser::parse_server_location(t_node &node, int &i, int &j)
{
    while (i < sz(words))
    {
        std::vector<std::string>    location_block;
        while (j < sz(words[i]) && !is_bracket(words[i][j]))
        {
            location_block.push_back(words[i][j]);
            j++;
        }
        if (sz(location_block))
            node.location_blocks.push_back(location_block);
        if (j < sz(words[i]) && words[i][j] == "}")
            break ;
        j = 0;
        i++;
    }
    // node.location_blocks.push_back(location_block);
}

void    ConfigFileParser::parse_server(int &i, int &j)
{
    t_node node;
    std::string id;

    bool flag = true;
    int a = i, b = j;
    if (!is_bracket(words[i][j]))
        id = words[i][j], j += 1;
    else
    {
        while (a >= 0 && flag)
        {
            b = sz(words[a]) - 1;
            while (b >= 0 && flag)
            {
                if (!is_bracket(words[a][b]))
                    id = words[a][b], flag = false;
                b--;
            }
            b = 0;
            a--;
        }
    }
    while (i < sz(words))
    {
        std::vector<std::string> line_words;
        while (j < sz(words[i]) && words[i][j] != "}")
        {
            if (words[i][j] == "location")
                parse_server_location(node, i, j);
            if (!is_bracket(words[i][j]))
            {
                if (!sz(node.id))
                    node.id = id;
                line_words.push_back(words[i][j]);
            }
            j++;
        }
        if (sz(line_words))
            node.words.push_back(line_words);
        if (j < sz(words[i]) && words[i][j] == "}")
            break ;
        i++;
        j = 0;
    }
    if (sz(node.id))
        nodes.push_back(node);
}

void    ConfigFileParser::parse_words(int a, int b)
{
    bool is_http = true, is_server = false, is_location = false;
    int i = 0, j = 0;
    if (!sz(words))
        return ;
    if (sz(words[i]) > 1)
        i = 1, j = 0;
    else if (sz(words[i]) == 1)
        i = 1, j = 1;
    // while (i < sz(words) && words[i][j] != "{")
    // {
    //     j = 0;
    //     while (j < sz(words[i]))
    //     {
    //         if (!words[i][j].compare("}"))
    //             break ;
    //         j++;
    //     }
    //     if (j < sz(words[i]) && words[i][j] == "{")
    //         break ;
    //     i++;
    // }
    // j++;
    while (i < sz(words))
    {
        while (j < sz(words[i]))
        {
            while (j < sz(words[i]) && is_bracket(words[i][j]))
                j++;
            parse_http_configs(i, j);
            // while (j < sz(words[i]) && is_bracket(words[i][j]))
            //     j++;
            if (i >= sz(words))
                break ;
            parse_server(i, j);
            if (i >= sz(words))
                break ;
            while (j < sz(words[i]) && is_bracket(words[i][j]))
                j++;
            j++;
        }
        j = 0;
        i++;
    }
}

void    ConfigFileParser::print_http_words()
{
    std::cout << "**** HTTP AS WORDS **** " << std::endl;
    std::cout << "[";
    for (int i = 0; i < sz(http_as_words); i++)
    {
        std::cout << "[";
        for(int j = 0; j < sz(http_as_words[i]); j++)
            std::cout << http_as_words[i][j] << ", ";
        std::cout << "]" << std::endl;
    }
    std::cout << "------------------------------" << std::endl;
}

void    ConfigFileParser::print_nodes1()
{
    std::cout << "**** NODES DATA **** " << std::endl;
    for (int i = 0; i < sz(nodes); i++)
    {
        std::cout << "Identifier: " << nodes[i].id << std::endl;
        std::cout << "WORDS: " << std::endl;
        print_words(nodes[i].words);
        std::cout << "Location Blocks: " << std::endl;
        print_words(nodes[i].location_blocks);
    }
    std::cout << "----------------------------------" << std::endl;
}

void    ConfigFileParser::print_all()
{
    print_http_words();
    print_nodes1();
}

void    ConfigFileParser::fill_http_hashmap()
{
    http_tokens.insert(std::make_pair("auto_indexing", ON_OFF));
    http_tokens.insert(std::make_pair("allowed_methods", METHOD_VECTOR));
    http_tokens.insert(std::make_pair("root", DIRECTORY));
}

void    ConfigFileParser::fill_server_hashmap()
{
    server_tokens.insert(std::make_pair("root", DIRECTORY));
    server_tokens.insert(std::make_pair("auto_indexing", ON_OFF));
    server_tokens.insert(std::make_pair("connection", CONNECTION));
    server_tokens.insert(std::make_pair("server_name", STRING));
    server_tokens.insert(std::make_pair("port", SHORT_INT));
    server_tokens.insert(std::make_pair("location", DIRECTORY));
    server_tokens.insert(std::make_pair("index", STRING_VECTOR));
}

void    ConfigFileParser::fill_location_hashmap()
{
    location_tokens.insert(std::make_pair("root", DIRECTORY));
    location_tokens.insert(std::make_pair("auto_indexing", ON_OFF));
    location_tokens.insert(std::make_pair("connection", CONNECTION));
    location_tokens.insert(std::make_pair("server_name", STRING));
    location_tokens.insert(std::make_pair("port", SHORT_INT));
    location_tokens.insert(std::make_pair("location", DIRECTORY));
    location_tokens.insert(std::make_pair("index", STRING_VECTOR));
}

void    ConfigFileParser::fill_tokens()
{
    fill_http_hashmap();
    fill_server_hashmap();
    fill_location_hashmap();
}

// bool    ConfigFileParser::parse_http_token(HttpConfig *configs, std::string token, int &i, int &j)
// {
//     while (i < sz(http_as_words))
//     {
//         while (j < sz(http_as_words[i]))
//         {
//             if (inHashMap(http_tokens, http_as_words[i][j]))
//                 break ;
//             j++;
//         }
//         j = 0;
//         i++;
//     }
// }

bool    ConfigFileParser::parse_http_line(int &i, int &j) // token already exists
{
    std::string token_word = http_as_words[i][j];
    TOKEN token_type = http_tokens[token_word];

    // if (token_type == DIRECTORY)
    // {
    //     if (is_directory(http))
    // }
    return (true);
}

// bool    ConfigFileParser::parse_http()
// {
//     int i = 0;
//     while (i < sz(http_as_words))
//     {
//         int j = 0;
//         if (http_tokens.find(http_as_words[i][j]) == http_tokens.end())
//             return (false) ;
//         if (!parse_http_line(i, j))
//             return (false);
//         i++;
//     }
//     return (true);
// }

bool ConfigFileParser::is_http_line_valid(int row)
{
    std::string token_name;
    TOKEN       token_type;

    token_name = http_as_words[row][0];
    if (http_tokens.find(token_name) == http_tokens.end())
        return (false) ;
    token_type = http_tokens[token_name];
    if ((token_type == DIRECTORY || token_type == SHORT_INT || token_type == INT || token_type == ON_OFF ||\
    token_type == METHOD || token_type == STRING) && (sz(http_as_words[row]) != 2))
        return (false);
    else if ((token_type == METHOD_VECTOR || token_type == STRING_VECTOR) && (sz(http_as_words[row]) < 2))
        return (false);
    if (token_type == DIRECTORY)
        return (tc.is_directory(http_as_words[row][1]));
    else if (token_type == SHORT_INT)
        return (tc.is_short_int(http_as_words[row][1]));
    else if (token_type == INT)
        return (tc.is_int(http_as_words[row][1]));
    else if (token_type == METHOD)
        return (tc.is_method(http_as_words[row][1]));
    else if (token_type == METHOD_VECTOR)
    {
        for (int i = 1; i < sz(http_as_words[row]); i++)
        {
            if (!tc.is_method(http_as_words[row][i]))
                return (false);
        }
    }
    else if (token_type == ON_OFF)
        return (tc.is_on_off(http_as_words[row][1]));
    return (true);
}

bool ConfigFileParser::is_http_valid()
{
    int i = 0, j = 0;
    while (i < sz(http_as_words))
    {
        j = 0;
        if (!is_http_line_valid(i))
            return (false) ;
        i++;
    }
    return (true);
}

bool ConfigFileParser::is_server_line_valid(std::vector<std::string> &_words)
{
    std::string token_name = _words[0];
    TOKEN       token_type;

    if (server_tokens.find(token_name) == server_tokens.end())
        return (false);
    token_type = server_tokens[token_name];
    if ((token_type == STRING || token_type == METHOD || token_type == INT || token_type == SHORT_INT \
    || token_type == DIRECTORY || token_type == CONNECTION) && (sz(_words) != 2))
        return (false);
    else if ((token_type == METHOD_VECTOR || token_type == STRING_VECTOR) && (sz(_words) < 2))
        return (false);
    if (token_type == DIRECTORY)
        return (tc.is_directory(_words[1]));
    else if (token_type == SHORT_INT)
        return (tc.is_short_int(_words[1]));
    else if (token_type == INT)
        return (tc.is_int(_words[1]));
    else if (token_type == METHOD)
        return (tc.is_method(_words[1]));
    else if (token_type == CONNECTION)
        return (tc.is_connection(_words[1]));
    else if (token_type == METHOD_VECTOR)
    {
        for (int i = 1; i < sz(_words); i++)
        {
            if (!tc.is_method(_words[i]))
                return (false);
        }
    }
    else if (token_type == ON_OFF)
        return (tc.is_on_off(_words[1]));
    return (true);
}

bool ConfigFileParser::is_location_block_valid(std::vector<std::string> &block)
{
    std::string token_name = block[0];
    TOKEN       token_type;

    if (location_tokens.find(token_name) == location_tokens.end())
        return (false);
    token_type = location_tokens[token_name];
    if ((token_type == STRING || token_type == METHOD || token_type == INT || token_type == SHORT_INT \
    || token_type == DIRECTORY || token_type == CONNECTION) && (sz(block) != 2))
        return (false);
    else if ((token_type == METHOD_VECTOR || token_type == STRING_VECTOR) && (sz(block) < 2))
        return (false);
    if (token_type == DIRECTORY)
        return (tc.is_directory(block[1]));
    else if (token_type == SHORT_INT)
        return (tc.is_short_int(block[1]));
    else if (token_type == INT)
        return (tc.is_int(block[1]));
    else if (token_type == METHOD)
        return (tc.is_method(block[1]));
    else if (token_type == CONNECTION)
        return (tc.is_connection(block[1]));
    else if (token_type == METHOD_VECTOR)
    {
        for (int i = 1; i < sz(block); i++)
        {
            if (!tc.is_method(block[i]))
                return (false);
        }
    }
    else if (token_type == ON_OFF)
        return (tc.is_on_off(block[1]));
    return (true);
}

bool ConfigFileParser::is_servers_valid()
{
    for (int i = 0; i < sz(nodes); i++)
    {
        for (int j = 0; j < sz(nodes[i].words); j++)
        {
            if (!is_server_line_valid(nodes[i].words[j]))
            {
                std::cout << "SERVER ERROR -> " << i << std::endl ;
                return (false);
            }
        }
        for (int k = 0; k < sz(nodes[i].location_blocks); k++)
        {
            if (!is_location_block_valid(nodes[i].location_blocks[k]))
            {
                std::cout << "LOCATION ERROR -> " << i << std::endl;
                for (int j = 0; j < sz(nodes[i].location_blocks[k]); j++)
                {
                    std::cout << nodes[i].location_blocks[k][j] << " " ;
                }
                return (false) ;
            }
        }
    }
    return (true);
}

int ConfigFileParser::count_words()
{
    int i = 0, res = 0;
    while (i < sz(words))
    {
        int j = 0;
        while (j < sz(words[i]))
        {
            res++;
            j++;
        }
        i++;
    }
    return (res);
}

bool ConfigFileParser::is_config_file_valid() // checks if the config file syntax is valid or not
{
    std::fstream c_stream;
    bool        is_everything_valid;
    c_stream.open(config_file, std::ios::in);
    if (!c_stream.good())
        return (false);
    fill_tokens();
    extract_lines_from_file(c_stream, lines);
    extract_words_from_lines(words);
    // print_words(words);
    if (!is_brackets_correct(words))
    {
        c_stream.close();
        return (false);
    }
    // std::cout << "BRACKETS ARE COMPLETELY CORRECT!" << std::endl;
    build_brackets_queue();
    std::vector<std::string> k;
    int words_size = count_words();
    if (words_size < 3 || (words_size > 3 && words[0][0] != "http")) // 1 -> http | 2 -> { 3-> }
    {
        c_stream.close();
        return (false) ;
    }
    parse_words(brackets_q.front().second.first, brackets_q.front().second.second);
    // print_http_words();
    // if (!parse_http())
    //     return (false);
    // if (!parse_servers())
    //     return (false);
    // print_all();
    // c_stream.close();
    // print_nodes();

    /**Debugging lines**/
    // if (is_http_valid())
    //     std::cout << "YES HTTP IS VALID" << std::endl;
    // if (is_servers_valid())
    //     std::cout << "YES SERVERS ARE VALID" << std::endl;
    // print_nodes1(); -> print the data of all the servers and their blocks
    is_everything_valid = (is_http_valid() && is_servers_valid());
    c_stream.close();
    return (is_everything_valid) ;
}

void    ConfigFileParser::fill_server_attributes(serverAttr &attr, int i)
{
    for (int j = 0; j < sz(nodes[i].words); j++)
    {
        std::string token_name = nodes[i].words[j][0];
        if (token_name == "auto_indexing")
            attr.auto_indexing = get_auto_indexing(nodes[i].words[j]);
        else if (token_name == "connection")
            attr.connection = get_connection(nodes[i].words[j]);
        else if (token_name == "server_name")
            attr.server_name = nodes[i].words[j][1];
        else if (token_name == "port")
            attr.port = get_port(nodes[i].words[j]);
        else if (token_name == "index")
        {
            attr.indexes = get_vector_of_data(nodes[i].words[j]);
            attr.indexes_set = vector_to_hashset(attr.indexes);
        }
        else if (token_name == "allowed_methods")
        {
            attr.allowed_methods = get_vector_of_data(nodes[i].words[j]);
            attr.allowed_methods_set  = vector_to_hashset(attr.allowed_methods);
        }
        else if (token_name == "root")
            attr.root = nodes[i].words[j][1];
    }
}

bool ConfigFileParser::get_auto_indexing(std::vector<std::string> &line)
{
    return (line[1] == "on");
}

bool ConfigFileParser::get_connection(std::vector<std::string> &line)
{
    return (line[1] == "keep-alive");
}

int ConfigFileParser::get_port(std::vector<std::string> &line)
{
    return (std::stoi(line[1]));
}

std::vector<std::string> ConfigFileParser::get_vector_of_data(std::vector<std::string> &line)
{
    std::vector<std::string> data;
    HashSet<std::string>     keep;

    for (int i = 1; i < sz(line); i++)
    {
        if (keep.find(line[i]) == keep.end())
        {
            data.push_back(line[i]);
            keep.insert(line[i]);
        }
    }
    return (data);
}

HashSet<std::string>    ConfigFileParser::vector_to_hashset(std::vector<std::string> &vec)
{
    HashSet<std::string> res;

    for (int i = 0; i < sz(vec); i++)
        res.insert(vec[i]);
    return (res);
}


void    ConfigFileParser::fill_location_attributes(locationConfigs &l_configs, int i)
{
    for (int j = 1; j < sz(nodes[i].location_blocks); j++)
    {
        std::string token_name = nodes[i].location_blocks[j][0];
        if (token_name == "auto_indexing")
            l_configs.auto_indexing = get_auto_indexing(nodes[i].location_blocks[j]);
        else if (token_name == "connection")
            l_configs.connection = get_connection(nodes[i].location_blocks[j]);
        else if (token_name == "index")
        {
            l_configs.indexes = get_vector_of_data(nodes[i].location_blocks[j]);
            l_configs.indexes_set = vector_to_hashset(l_configs.indexes);
        }
        else if (token_name == "allowed_methods")
        {
            l_configs.allowed_methods = get_vector_of_data(nodes[i].location_blocks[j]);
            l_configs.allowed_methods_set = vector_to_hashset(l_configs.allowed_methods);
        }
        else if (token_name == "root")
            l_configs.root = nodes[i].location_blocks[j][1];
    }
}


bool ConfigFileParser::fill_servers_data(std::vector<Server *> *servers)
{
    HashSet<std::string> already_parsed;

    for (int i = 0; i < sz(nodes); i++)
    {
        Server      *server = new Server();
        serverAttr *attr = new serverAttr();
        locationConfigs l_configs;
        std::string     location_name;
        fill_server_attributes(*attr, i);
        fill_location_attributes(l_configs, i);
        if (sz(nodes[i].location_blocks))
        {
            location_name = nodes[i].location_blocks[0][1];
            server->set_location_map(location_name, l_configs);
        }
        server->set_server_attr(attr);
        servers->push_back(server);
    }
    return (true);
}

bool ConfigFileParser::fill_http_data(httpConfigs *http_data)
{
    HashSet<std::string> already_parsed;

    for (int i = 0; i < sz(http_as_words); i++)
    {
        std::string token_name = http_as_words[i][0];
        if (token_name == "auto_indexing")
            http_data->auto_indexing = get_auto_indexing(http_as_words[i]);
        else if (token_name == "root")
            http_data->root = http_as_words[i][1];
        else if (token_name == "allowed_methods")
        {
            http_data->allowed_methods = get_vector_of_data(http_as_words[i]);
            http_data->allowed_methods_set = vector_to_hashset(http_data->allowed_methods);
        }
    }
    std::cout << "HTTP" << std::endl;
    return (true);
}

bool ConfigFileParser::parse_config_file(httpConfigs *http_data, std::vector<Server *> *servers)
{
    if (!is_config_file_valid()) // O(N) to check if the file is valid or not
        return (false);
    // if (!DataExtractor.extract_data(http_data, servers)) // O(N) to extract the data
    //     return (false) ;
    // return (true) ;
    return (fill_http_data(http_data) && fill_servers_data(servers));
}