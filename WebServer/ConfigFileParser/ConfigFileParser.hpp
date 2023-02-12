#ifndef CONFIG_FILE_PARSER_HPP
# define CONFIG_FILE_PARSER_HPP

class ConfigFileParser
{
    private:
        string          config_file;
        vector<string>  lines;
    public:
        ConfigFileParser();
        ConfigFileParser(string config_file);
        ConfigFileParser(const ConfigFileParser& p);
        ConfigFileParser& operator=(const ConfigFileParser& p) ;
        ~ConfigFileParser();

        bool    is_config_file_valid();
        bool    parse_config_file(vector<Server *> &Servers, HttpConfigs &globalConfigs);
} ;

# endif