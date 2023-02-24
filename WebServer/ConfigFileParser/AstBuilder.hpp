#ifndef AST_BUILDER_HPP
# define AST_BUILDER_HPP

# include "../../Includes/Header.hpp"
# include "Ast.hpp"

class AstBuilder
{
    private:
        std::vector<std::string>                lines;
        std::vector<std::vector<std::string> >  words;
        Ast                                     *a_tree;
    public:
        AstBuilder();
        AstBuilder(std::vector<std::string> &_lines, Ast *_a_tree);
        ~AstBuilder();

        bool    build_ast(std::stack<std::pair<char, std::pair<int, int> > > &brackets_st, \
        Ast &parent, Ast &node, int i, int j); // first call parent == node
} ;

#endif