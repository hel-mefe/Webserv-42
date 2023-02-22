# include "AstBuilder.hpp"

AstBuilder::AstBuilder()
{
    a_tree = nullptr;
    return ;
}

AstBuilder::AstBuilder(std::vector<std::string> &_lines, Ast *_a_tree)
{
    lines = _lines;
    a_tree = _a_tree;
}

AstBuilder::~AstBuilder()
{
    return ;
}

std::vector<std::string> get_block(std::vector<std::string> &lines, int i, int j)
{
    while (i < sz(lines))
    {
        while (j < sz(lines[i]))
        {
            if (lines[i][j] == '}')
                break ;
            j++;
        }
        j = 0;
        i++;
    }
}

bool    AstBuilder::build_ast(std::stack<std::pair<char, std::pair<int, int> > > &brackets_st, \
Ast &parent, Ast &node, int i, int j)
{
    int oldj = j, oldi = i;
    while (i < sz(words))
    {
        while (j < sz(words))
        {
            if (words[i][j] == "{")
            {
                brackets_st.push(std::make_pair(lines[i][j], std::make_pair(i, j)));
                Ast _node;
                if (&parent != &node)
                    parent.add_new_child(node);
                return (build_ast(brackets_st, _node, i, j + 1));
            }
            else if (words[i][j] == "}")
            {
                if (brackets_st.empty() || brackets_st.top().first != "{")
                    return (false);
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (!brackets_st.empty());
}