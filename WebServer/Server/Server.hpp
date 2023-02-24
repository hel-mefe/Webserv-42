#ifndef SERVER_HPP
# define SERVER_HPP

# include "../../Includes/Header.hpp"
# include "../../Includes/Structures.hpp"
# include "RequestResponse/RequestResponse.hpp"

class Server
{
    private:
        RequestResponse                                     *request_response;
        t_server_configs                                    *server_configs;
        t_http_configs                                      *http_configs;
        HashMap<std::string, t_location_configs>            *dir_configs; // directory configs (dir -> its configs)
    public:
        Server();
        Server& operator=(const Server&);
        Server(const Server&);
        ~Server();

        // Getters
        t_server_configs*   get_server_configs() const;
        void                set_server_configs(t_server_configs *_server_configs);
        void                set_location_map(std::string location_name, t_location_configs &configs);
        void                print_data();

        void    run();
} ;

# endif