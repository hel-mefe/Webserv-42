#ifndef SERVER_HPP
# define SERVER_HPP

# include "../../Includes/Header.hpp"
# include "../../Includes/Structures.hpp"
# include "RequestHandler/RequestHandler.hpp"
# include "ResponseHandler/ResponseHandler.hpp"

class Server
{
    private:
        RequestHandler                          *Request;
        ResponseHandler                         *Response;
        serverAttr                              *Attr;
        HashMap<std::string, locationConfigs>   dir_configs; // directory configs (dir -> its configs)
    public:
        Server();
        Server& operator=(const Server&);
        Server(const Server&);
        ~Server();

        // Getters
        RequestHandler*     getRequestHandler() const;
        ResponseHandler*    getResponseHandler() const;
        serverAttr*         getServerAttr() const;
        void                set_server_attr(serverAttr *_Attr);
        void                set_location_map(std::string location_name, locationConfigs &configs);

} ;

# endif