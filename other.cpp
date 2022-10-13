#include "other.h"
bool operator==(const char& lhs, const std::list<std::string>& rhs)
{
	for (auto str : rhs)
	{
		if (lhs == str[0])
			return true;
	}
	return false;
}
bool operator==(const std::string& lhs, const std::list<std::string>& rhs)
{
	for (const std::string& str : rhs)
	{
		if (lhs == str)
			return true;
	}
	return false;
}
std::list<std::string> operator+(const std::list<std::string>& lhs, const std::list<std::string>& rhs)
{
	std::list<std::string> res = lhs;
	for (auto str : rhs)
	{
		res.push_back(str);
	}
	return res;
}
std::ostream& operator<<(std::ostream& out, const lexeme& lexeme_to_out)
{
	out << "(";
	switch (lexeme_to_out.type)
	{
	case lexeme_type::undefined:
		out << "undefined";
		break;
	case lexeme_type::comment:
		out << "comment";
		break;
	case lexeme_type::double_separator_begin:
	case lexeme_type::double_separator_end:
		out << "double separator";
		break;
	case lexeme_type::identifier:
		out << "identifier";
		break;
	case lexeme_type::keyword:
		out << "keyword";
		break;
	case lexeme_type::literal:
		out << "literal";
		break;
	case lexeme_type::oper:
		out << "operator";
		break;
	case lexeme_type::single_separator:
		out << "single separator";
		break;
	}
	out << "): <" << lexeme_to_out.name << "> {line: " << lexeme_to_out.pos.line_number + 1 <<
		"; position[" << lexeme_to_out.pos.inline_begin << "; " << lexeme_to_out.pos.inline_end << "]}";
	return out;
}