#include <iostream>
#include <string>
#include <list>

#include "types.h"
#include "other.h"
#include "python_parser.h"
using namespace std;

int main()
{
	python_parser parser("test.py");
	auto listik = parser.parse();
	for (lexeme& lex : listik)
	{
		std::cout << lex << endl;
	}
	return 0;
}