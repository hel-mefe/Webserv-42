#ifndef POST_HPP
# define POST

# include "../MethodHandler.hpp"

class Post : public MethodHandler
{
    private:

    public:
        Post();
        Post(const Post &p);
        Post& operator=(const Post &p);
        ~Post();
} ;

#endif