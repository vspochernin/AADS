#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

class FrequencyDictionary;

size_t getCharCode(char ch); // Получение кода символа (код русских букв может получаться как код - 256).
size_t hashByDivision(const std::string& str, size_t size); // Хеш-функция методом деления.

void clearWord(std::string& str); // Очистить слово от не букв.
bool isRussianLetter(char ch); // true - если символ - английская буква.
bool isEnglishLetter(char ch); // true - если символ - русская буква.
bool isWord(const std::string& str); // true - если строка - подходящее слово.
void toLower(std::string& str); // Переводит слово в нижний регистр.

void quickSort(std::vector< std::pair< std::string, size_t > >& vec, int l, int r); // Быстрая сортировка вектора пар.
void printVector(const std::vector< std::pair< std::string, size_t > >& vec, std::ostream& out); // Вывести вектор пар в out.

void startProgram(); // Функция выполнения основной программы.
void showHelp(); // Вывести список команд.
void doInsert(FrequencyDictionary& dictionary); // Добавить слово.
void doSearch(const FrequencyDictionary& dictionary); // Найти слово.
void doDelete(FrequencyDictionary& dictionary); // Удалить слово.
void doReadFile(FrequencyDictionary& dictionary); // Добавить слова из файла.
void doPrintThreeMost(const FrequencyDictionary& dictionary); // Напечатать три чаще всего встречающихся слова.
void doWriteFile(const FrequencyDictionary& dictionary); // Записать в файл слова по убыванию их встречаемости.

void testProgram(); // Функция выполнения тестов.
void doDoubleLinkedListTest();

#endif
