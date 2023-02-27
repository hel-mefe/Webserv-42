#ifndef DELETE_HPP
# define DELETE

# include "../MethodHandler.hpp"

class Delete : public MethodHandler
{
    private:

    public:
        Delete();
        Delete(const Delete &p);
        Delete& operator=(const Delete &p);
        ~Delete();
} ;

#endif