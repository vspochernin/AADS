#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

size_t getCharCode(char ch); // Получение кода символа (код русских букв может получаться как код - 256).
size_t hashByDivision(const std::string& str, size_t size); // Хеш-функция методом деления.

bool isRussianLetter(char ch); // true - если символ - английская буква.
bool isEnglishLetter(char ch); // true - если символ - русская буква.
bool isWord(const std::string& str); // true - если строка - подходящее слово.
void toLower(std::string& str); // Переводит слово в нижний регистр.

#endif
