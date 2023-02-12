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

    std::cout << "LINES VEC = " << lines.size() << std::endl ;
    for (int i = 0; i < (int)lines.size(); i++)
    {
        word = get_word_vector(lines[i]);
        if (word.size()) // if the line is empty it will get ignored
            words.push_back(word);
        word.clear();
    }
    print_words(words);
}

bool ConfigFileParser::is_config_file_valid() // checks if the config file syntax is valid or not
{
    std::fstream c_stream;

    c_stream.open(config_file, std::ios::in);
    if (!c_stream.good())
        return (false);
    extract_lines_from_file(c_stream, lines);
    // print_vector_lines(lines);
    extract_words_from_lines(words);
    c_stream.close();
    return (true) ;
}
