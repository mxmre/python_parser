#pragma once
#include <cstdint>

struct position_in_file
{
	size_t line_number, inline_begin, inline_end;
};

enum class lexeme_type
{
	undefined,
	identifier,					//�������������
	keyword,					//�������� �����
	oper,						//��������
	literal,					//�������
	single_separator,			//��������� �����������
	double_separator_begin,		//������� ����������� (���������)
	double_separator_end,		//������� ����������� (��������)
	comment						//�����������
};
struct lexeme
{
	std::string name;
	position_in_file pos;
	lexeme_type type;
};


