EXEC = Webserv
CPP_VERSION = -std=c++98
SRCS = main.cpp WebServer/WebServer.cpp WebServer/ConfigFileParser/ConfigFileParser.cpp WebServer/Server/Server.cpp WebServer/Server/RequestHandler/RequestHandler.cpp WebServer/Server/RequestHandler/RequestParser/RequestParser.cpp WebServer/Server/ResponseHandler/ResponseHandler.cpp

ALL: $(EXEC)

$(EXEC): $(SRCS)
	@c++ $(CPP_VERSION) $(SRCS) -o $(EXEC)

fclean:
	@rm -rf $(EXEC)

re: fclean ALL

