#ifndef SERVER_HPP
# define SERVER_HPP

# include "../../Includes/Header.hpp"
# include "../../Includes/Structures.hpp"
# include "../../Includes/Exceptions.hpp"
# include "RequestResponse/RequestResponse.hpp"

class Server
{
    private:
        MULTIPLEXER                                          mult;
        RequestResponse                                     *request_response;
        t_server_configs                                    *server_configs;
        t_http_configs                                      *http_configs;
        HashMap<std::string, t_location_configs>            *dir_configs; // directory configs (dir -> its configs)
    public:
        Server();
        Server(MULTIPLEXER);
        Server& operator=(const Server&);
        Server(const Server&);
        ~Server();

        // Getters
        t_server_configs*   get_server_configs() const;
        void                set_server_configs(t_server_configs *_server_configs);
        void                set_location_map(std::string location_name, t_location_configs &configs);
        void                print_data();

        void    run();

        // Multiplexers
        void    build_with_kqueue();
        void    build_with_select();
        void    build_with_poll();

        //Network functions
        SOCKET  get_listener_socket(t_socket *listener);
        void    read_request(t_socket *client);
        void    add_connection(t_network *manager);
        void    handle_client(t_network *manager, int index);

        //Method handlers
        void    handle_get_request(int fd, t_request *req);
        void    handle_post_request(int fd, t_request *req);
        void    handle_delete_request(int fd, t_request *req);

        // Handlers
        void    disconnect_client(t_network *manager, int index);
        void    serve_client(t_network *manager, int index);
} ;

# endif