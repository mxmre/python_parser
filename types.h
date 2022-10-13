#pragma once
#include <cstdint>

struct position_in_file
{
	size_t line_number, inline_begin, inline_end;
};

enum class lexeme_type
{
	undefined,
	identifier,					//Идентификатор
	keyword,					//Ключевое слово
	oper,						//Оператор
	literal,					//Литерал
	single_separator,			//Одиночный разделитель
	double_separator_begin,		//Двойной разделитель (начальный)
	double_separator_end,		//Двойной разделитель (конечный)
	comment						//Комментарий
};
struct lexeme
{
	std::string name;
	position_in_file pos;
	lexeme_type type;
};


