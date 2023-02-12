#ifndef SERVER_HPP
# define SERVER_HPP

# include "../../Includes/Header.hpp"
# include "../../Includes/Structures.hpp"
# include "RequestHandler/RequestHandler.hpp"
# include "ResponseHandler/ResponseHandler.hpp"

class Server
{
    private:
        RequestHandler  *Request;
        ResponseHandler *Response;
        ServerAttr      *Attr;
    public:
        Server();
        Server& operator=(const Server&);
        Server(const Server&);
        ~Server();

        // Getters
        RequestHandler*     getRequestHandler() const;
        ResponseHandler*    getResponseHandler() const;
        ServerAttr*         getServerAttr() const;

} ;

# endif