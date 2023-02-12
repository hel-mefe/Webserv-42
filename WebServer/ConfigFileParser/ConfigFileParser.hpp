#ifndef CONFIG_FILE_PARSER_HPP
# define CONFIG_FILE_PARSER_HPP

# include "../../Includes/Header.hpp"

class ConfigFileParser
{
    private:
        std::string          config_file;
        std::vector<std::string>  lines;
        std::vector<std::vector<std::string> > words;
    public:
        ConfigFileParser();
        ConfigFileParser(std::string config_file);
        ConfigFileParser(const ConfigFileParser& p);
        ConfigFileParser& operator=(const ConfigFileParser& p) ;
        ~ConfigFileParser();

        std::string  get_config_file() const;
        bool    is_config_file_valid();
        // bool    parse_config_file(vector<Server *> &Servers, HttpConfigs &globalConfigs);
        void    extract_lines_from_file(std::fstream &f_stream, std::vector<std::string> &lines);
        void    print_vector_lines(std::vector<std::string> &lines);

        void    print_words(std::vector<std::vector<std::string> > words);
        void    extract_words_from_lines(std::vector<std::vector<std::string> > &words);
        std::vector<std::string> get_word_vector(std::string &line);   
} ;

# endif