EXEC = Webserv
CPP_VERSION = -std=c++98 -fsanitize=address
SRCS = main.cpp WebServer/WebServer.cpp WebServer/ConfigFileParser/TokensChecker.cpp WebServer/ConfigFileParser/ConfigFileParser.cpp \
WebServer/Server/Server.cpp WebServer/Server/RequestResponse/RequestResponse.cpp \
WebServer/Server/RequestResponse/RequestParser/RequestParser.cpp WebServer/Server/RequestResponse/ResponseBuilder/ResponseBuilder.cpp  \
WebServer/gnl/get_next_line.cpp WebServer/gnl/get_next_line_utils.cpp WebServer/Server/Methods/get.cpp WebServer/Server/Methods/post.cpp \
WebServer/Server/Methods/delete.cpp

ALL: $(EXEC)

$(EXEC): $(SRCS)
	@c++ $(CPP_VERSION) $(SRCS) -o $(EXEC)

fclean:
	@rm -rf $(EXEC)

re: fclean ALL

