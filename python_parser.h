#pragma once
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

#include <cstring>

#include "types.h"
#include "other.h"


class python_parser
{
public:
	python_parser(const std::string filepath);
	~python_parser();
	std::list<lexeme> parse();
	void change_filepath(const std::string filepath);
private:
	std::string _filepath;
	//void _post_parsing(std::list<lexeme>& lexeme_list);
	//Статичные инициализаторы лексем
	static std::list<std::string> GET_SINGLE_SEPARATOR_LIST();
	static std::list<std::string> GET_DOUBLE_SEPARATOR_BEGIN_LIST();
	static std::list<std::string> GET_DOUBLE_SEPARATOR_END_LIST();
	static std::list<std::string> GET_COMMENT_LIST();
	static std::list<std::string> GET_KEYWORD_LIST();
	static std::list<std::string> GET_OPERATOR_LIST();

	bool is_literal(const std::string& word);
};

