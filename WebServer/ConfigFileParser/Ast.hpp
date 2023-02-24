#ifndef AST_HPP
# define AST_HPP

# include "../../Includes/Header.hpp"

class Ast // supppsed that the brackets are properly closed
{
    private:
        std::string                                                         identifier;
        std::vector<std::string>                                            lines;
        std::vector<std::vector<std::string> >                              words;
        std::vector<Ast>                                                    childs; // the question is there any danger if this method was used rather than std::vector<Ast *>
        std::queue<std::pair<char, std::pair<int, int> > >                  brackets_queue; // char and pos in the words 2d vector
    public:
        Ast();
        Ast(std::string _id, std::vector<std::string> _lines);
        ~Ast();

        void    set_id(std::string _id);
        void    set_lines(std::vector<std::string> _lines);
        void    add_new_child(Ast &node);
} ;

#endif