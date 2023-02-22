# include "Ast.hpp"

Ast::Ast()
{
    return ;
}

Ast::Ast(std::string _id, std::vector<std::string> _lines);
{
    identifier = _id;
    lines = _lines; 
}

Ast::~Ast()
{
    return ;
}

void    Ast::set_lines(std::vector<std::string> _lines)
{
    lines = _lines ;
}

void    Ast::set_id(std::string _id)
{
    identifier = _id;
}

void    buld
