#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

class FrequencyDictionary; // Говорим, что такой класс существует, чтобы использовать его в сигнатурах.

size_t getCharCode(char ch); // Получение кода символа (код русских букв может получаться как "код - 256").
size_t hashByDivision(const std::string& str, size_t size); // Хеш-функция методом деления.

bool isRussianLetter(char ch); // true - если символ - русская буква.
bool isEnglishLetter(char ch); // true - если символ - английская буква.
void clearWord(std::string& str); // Очистить слово от не букв.
bool isWord(const std::string& str); // true - если строка - подходящее нашему определению слово.
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
void doClear(FrequencyDictionary& dictionary); // Очистить словарь.

void testProgram(); // Функция выполнения тестов.
void doDoubleLinkedListTest(); // Тестирование двусвязного списка.
void doFunctionsTest(); // Тестирование вспомогательных функций.
void doFrequencyDictionaryTest(); // Тестирование частотного словаря.

#endif
