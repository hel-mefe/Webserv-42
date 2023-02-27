#ifndef GET_HPP
# define GET

# include "../MethodHandler.hpp"

class Get : public MethodHandler
{
    private:

    public:
        Get();
        Get(const Get &p);
        Get& operator=(const Get &p);
        ~Get();
} ;

#endif