#ifndef RESPONSE_BUILDER_HPP
# define RESPONSE_BUILDER_HPP

class ResponseBuilder
{
    private:
    
    public:
        ResponseBuilder();
        ResponseBuilder(const ResponseBuilder &r);
        ResponseBuilder& operator=(const ResponseBuilder &r);
        ~ResponseBuilder();
};

#endif