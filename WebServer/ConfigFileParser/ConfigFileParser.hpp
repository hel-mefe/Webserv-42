#ifndef CONFIG_FILE_PARSER_HPP
# define CONFIG_FILE_PARSER_HPP

# include "../../Includes/Header.hpp"
# include "../Server/Server.hpp"
# include "TokensChecker.hpp"
# include "Ast.hpp"

typedef struct ast_node
{
    std::string                              id;
    std::vector<std::vector<std::string> >   words;
    std::vector<std::vector<std::string> >   location_blocks;
} t_node;

class ConfigFileParser
{
    private:
        TokensChecker                                               tc; // TokensChecker
        std::string                                                 config_file;
        std::vector<std::string>                                    lines;
        std::vector<std::vector<std::string> >                      words;
        std::vector<std::pair<std::string, std::pair<int, int> > >  brackets_q;
        std::vector<t_node>                                         nodes; // 1st one for http and others for servers
        std::vector<std::vector<std::string> >                                    http_as_words;
        HashMap<std::string, std::string>                           http_configs;
        HashMap<std::string, TOKEN>                                 http_tokens; // token string mapped to the type of answer it accepts
        HashMap<std::string, TOKEN>                                 server_tokens; // same as above map
        HashMap<std::string, TOKEN>                                 location_tokens;
        // Ast                                     a_tree;
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
        void    build_brackets_queue();
        void    build_with_vector(std::vector<std::string> &vec, int i, int j);
        std::string get_str(std::vector<std::vector<std::string> > &vec, int i, int end_i, int j, int end_j);

        std::string     get_identifier(std::pair<int, int> &start, std::pair<int, int> &end);
        void            fill_words(std::vector<std::vector<std::string> > &n_words, \
        std::pair<int, int> &start, std::pair<int, int> &end);
        void            push_node(std::pair<int, int> prev, std::pair<int, int> &mid, std::pair<int, int> &end);
        void            print_nodes();

        void            parse_words(int a, int b);
        void            parse_server(int &i, int &j);
        void            parse_server_location(t_node &node, int &i, int &j);
        void            parse_http_configs(int &i, int &j);

        void    print_http_words();
        void    print_nodes1();
        void    print_all();

        void        fill_http_hashmap();
        void        fill_server_hashmap();
        // bool fill_global_http_configs(HttpConfigs *configs);
        void        fill_location_hashmap();
        void        fill_tokens();

        bool is_http_valid();
        bool is_http_line_valid(int row);
        bool is_servers_valid();
        bool is_server_line_valid(std::vector<std::string> &_words);
        bool parse_http();
        bool parse_http_line(int &i, int &j);
        bool    is_location_block_valid(std::vector<std::string> &block);
        // bool parse_http_token(HttpConfig *configs, std::string token, int &i, int &j);

        bool    fill_servers_data(std::vector<Server *> *servers);
        bool    fill_http_data(httpConfigs *http_data);
        void    fill_server_attributes(serverAttr &attr, int i);
        void    fill_location_attributes(locationConfigs &l_configs, int i);
        // data parsing getters;
        bool                        get_auto_indexing(std::vector<std::string> &line);
        bool                        get_connection(std::vector<std::string> &line);
        int                         get_port(std::vector<std::string> &line);
        std::vector<std::string>    get_vector_of_data(std::vector<std::string> &line); 
        HashSet<std::string>        vector_to_hashset(std::vector<std::string> &vec);

        bool    parse_config_file(httpConfigs *http_data, std::vector<Server *> *servers);

} ;

# endif