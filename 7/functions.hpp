#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

size_t getCharCode(char ch); // Получение кода символа (с этим проблемы из-за разных кодировок).
size_t hashByDivision(const std::string& str, size_t size); // Хеш-функция методом деления.
#endif
