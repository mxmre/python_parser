#include "python_parser.h"

python_parser::python_parser(const std::string filepath) : _filepath(filepath)
{
    
}

python_parser::~python_parser()
{
    
}



std::list<std::string> python_parser::GET_SINGLE_SEPARATOR_LIST()
{
    std::list<std::string> result;
    result.push_back(" ");
    result.push_back("\t");
    result.push_back(".");
    result.push_back(",");
    result.push_back("\"");
    result.push_back("\'");
    result.push_back(":");
    return result;
}

std::list<std::string> python_parser::GET_DOUBLE_SEPARATOR_BEGIN_LIST()
{
    std::list<std::string> result;
    result.push_back("{");
    result.push_back("(");
    result.push_back("[");
    result.push_back("<");
    return result;
}

std::list<std::string> python_parser::GET_DOUBLE_SEPARATOR_END_LIST()
{
    std::list<std::string> result;
    result.push_back("}");
    result.push_back(")");
    result.push_back("]");
    result.push_back(">");
    return result;
}
std::list<std::string> python_parser::GET_COMMENT_LIST()
{
    std::list<std::string> result;
    result.push_back("#");
    result.push_back("\"\"\"");
    return result;
}
std::list<std::string> python_parser::GET_KEYWORD_LIST()
{
    std::list<std::string> result;
    result.push_back("def");
    result.push_back("class");
    result.push_back("return");
    result.push_back("import");
    result.push_back("if");
    result.push_back("from");
    result.push_back("for");
    result.push_back("elif");
    result.push_back("else");
    result.push_back("while");
    result.push_back("do");
    result.push_back("or");
    result.push_back("and");
    result.push_back("not");
    result.push_back("False");
    result.push_back("True");
    result.push_back("None");
    result.push_back("with");
    result.push_back("as");
    result.push_back("assert");
    result.push_back("break");
    result.push_back("continue");
    result.push_back("del");
    result.push_back("except");
    result.push_back("finaly");
    result.push_back("global");
    result.push_back("in");
    result.push_back("is");
    result.push_back("lambda");
    result.push_back("nonlocal");
    result.push_back("pass");
    result.push_back("raise");
    result.push_back("try");
    result.push_back("yield");
    return result;
}
std::list<std::string> python_parser::GET_OPERATOR_LIST()
{
    std::list<std::string> result;
    result.push_back("+");
    result.push_back("-");
    result.push_back("?");
    result.push_back("*");
    result.push_back("/");
    result.push_back("**");
    result.push_back("//");
    result.push_back("%");
    result.push_back("<");
    result.push_back(">");
    result.push_back("<=");
    result.push_back(">=");
    result.push_back("==");
    result.push_back("!=");
    result.push_back("=");
    result.push_back("+=");
    result.push_back("-+");
    result.push_back("*=");
    result.push_back("/=");
    result.push_back("%=");
    result.push_back("**=");
    result.push_back("//="); 
    result.push_back("->");
    return result;
}
bool python_parser::is_literal(const std::string& word)
{
    for (int i = 48; i < 58; ++i)
    {
        if (word[0] == (char)i)
            return true;
    }
    return false;
}
std::list<lexeme> python_parser::parse()
{
    using std::getline;
    std::fstream file(this->_filepath);
    if (!file.is_open())
        throw std::exception();
    std::list<lexeme> lexeme_list;
    //инициализация константных списков лексем языка
    std::list<std::string> single_separators = python_parser::GET_SINGLE_SEPARATOR_LIST();
    std::list<std::string> double_separators_begin = python_parser::GET_DOUBLE_SEPARATOR_BEGIN_LIST();
    std::list<std::string> double_separators_end = python_parser::GET_DOUBLE_SEPARATOR_END_LIST();
    std::list<std::string> operators = python_parser::GET_OPERATOR_LIST();
    std::list<std::string> separators = single_separators + double_separators_begin + double_separators_end;

    std::list<std::string> comments = python_parser::GET_COMMENT_LIST();
    std::list<std::string> keywords = python_parser::GET_KEYWORD_LIST();
    
    for (size_t line_id = 0; !file.eof(); ++line_id)
    {
        std::string line_str;
        getline(file, line_str);
        bool collect_full_str = false;
        for (size_t cur_char_id = 0, begin_char_id = 0; cur_char_id < line_str.size(); ++cur_char_id)
        {
            bool is_operator = false;
            if (!collect_full_str && ((line_str[cur_char_id] == separators)
                || (is_operator = true, line_str[cur_char_id] == operators)))
            {
                lexeme_type inserting_lexeme_type = lexeme_type::identifier;
                if (cur_char_id != begin_char_id)
                {
                    std::string word = line_str.substr(begin_char_id, (cur_char_id - 1) - begin_char_id + 1);
                    if (word == keywords)
                        inserting_lexeme_type = lexeme_type::keyword;
                    else if (this->is_literal(word))
                        inserting_lexeme_type = lexeme_type::literal;
                    lexeme_list.push_back(lexeme{
                        .name = word,
                        .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = cur_char_id - 1},
                        .type = inserting_lexeme_type
                        });
                }
                if (is_operator)
                {
                    size_t add_id = 2;
                    if (line_str.size() - cur_char_id < 2)
                        add_id = line_str.size() - cur_char_id;
                    for (size_t i = cur_char_id + add_id; i >= cur_char_id; --i)
                    {
                        std::string operator_str = line_str.substr(cur_char_id, (i) -cur_char_id + 1);
                        if (operator_str == operators)
                        {
                            inserting_lexeme_type = lexeme_type::oper;
                            lexeme_list.push_back(lexeme{
                                    .name = operator_str,
                                    .pos = {.line_number = line_id, .inline_begin = cur_char_id, .inline_end = i},
                                    .type = inserting_lexeme_type
                                });
                            cur_char_id = i;
                            break;
                        }
                    }
                }
                else
                {
                    if (line_str[cur_char_id] == single_separators)
                    {
                        inserting_lexeme_type = lexeme_type::single_separator;
                        if (line_str[cur_char_id] == '\'' || line_str[cur_char_id] == '\"')
                        {
                            collect_full_str = true;
                        }
                    }
                    else if (line_str[cur_char_id] == double_separators_begin)
                        inserting_lexeme_type = lexeme_type::double_separator_begin;
                    else if (line_str[cur_char_id] == double_separators_end)
                        inserting_lexeme_type = lexeme_type::double_separator_end;
                    lexeme_list.push_back(lexeme{
                            .name = line_str.substr(cur_char_id, 1),
                            .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = begin_char_id},
                            .type = inserting_lexeme_type
                        });
                }
                begin_char_id = cur_char_id + 1;
            }
            else if (collect_full_str && (line_str[cur_char_id] == '\'' || line_str[cur_char_id] == '\"'))
            {
                lexeme_list.push_back(lexeme{
                        .name = line_str.substr(begin_char_id, (cur_char_id - 1) - begin_char_id + 1),
                        .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = cur_char_id - 1},
                        .type = lexeme_type::literal
                    });
                lexeme_list.push_back(lexeme{
                        .name = line_str.substr(cur_char_id, 1),
                        .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = cur_char_id - 1},
                        .type = lexeme_type::single_separator
                    });
                collect_full_str = false;
                begin_char_id = cur_char_id + 1;
            }
            else if (cur_char_id + 1 == line_str.size())
            {
                std::string word;
                if(cur_char_id != begin_char_id)
                    word = line_str.substr(begin_char_id, (cur_char_id - 1) - begin_char_id + 1);
                else
                    word = line_str.substr(cur_char_id, 1);
                if(this->is_literal(word))
                    lexeme_list.push_back(lexeme{
                            .name = word,
                            .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = cur_char_id - 1},
                            .type = lexeme_type::literal
                        });
                else
                {
                    lexeme_list.push_back(lexeme{
                            .name = word,
                            .pos = {.line_number = line_id, .inline_begin = begin_char_id, .inline_end = cur_char_id - 1},
                            .type = lexeme_type::identifier
                        });
                }
            }
        }
    }
    //this->_post_parsing(lexeme_list);
    file.close();
    return lexeme_list;
}
void python_parser::change_filepath(const std::string filepath)
{
    this->_filepath = filepath;
}
