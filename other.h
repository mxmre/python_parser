#pragma once
#include <list>
#include <string>
#include<iostream>

#include "types.h"

bool operator==(const char& lhs, const std::list<std::string>& rhs);
bool operator==(const std::string& lhs, const std::list<std::string>& rhs);
std::list<std::string> operator+(const std::list<std::string>& lhs, const std::list<std::string>& rhs);
std::ostream& operator<<(std::ostream& out, const lexeme& lexeme_to_out);