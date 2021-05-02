#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <vector>

class FrequencyDictionary; // Говорим, что такой класс существует, чтобы использовать его в сигнатурах.

size_t getCharCode(char ch); // Получение кода символа (код русских букв может получаться как "код - 256").
size_t hashByDivision(const std::string& str, size_t size); // Хеш-функция методом деления.

bool isRussianLetter(char ch); // true - если символ - русская буква.
bool isEnglishLetter(char ch); // true - если символ - английская буква.
void clearWord(std::string& str); // Очищение слова от не букв.
bool isWord(const std::string& str); // true - если строка - подходящее нашему определению слово.
void toLower(std::string& str); // Перевод слова в нижний регистр.

void quickSort(std::vector< std::pair< std::string, size_t > >& vec, int l, int r); // Быстрая сортировка вектора пар.
void printVector(const std::vector< std::pair< std::string, size_t > >& vec, std::ostream& out); // Вывод вектора пар в out.

void startProgram(); // Функция выполнения основной программы.
void showHelp(); // Вывод списка команд.
void doInsert(FrequencyDictionary& dictionary); // Добавление слова.
void doSearch(const FrequencyDictionary& dictionary); // Поиск слова.
void doDelete(FrequencyDictionary& dictionary); // Удаление слова.
void doReadFile(FrequencyDictionary& dictionary); // Добавление слова из файла.
void doPrint(FrequencyDictionary& dictionary); // Вывод словаря в консоль.
void doPrintThreeMost(const FrequencyDictionary& dictionary); // Печать трех чаще всего встречающихся слов.
void doWriteFile(const FrequencyDictionary& dictionary); // Запись в файл слов по убыванию их встречаемости.
void doClear(FrequencyDictionary& dictionary); // Очищение словаря.

void testProgram(); // Функция выполнения тестов.
void doDoubleLinkedListTest(); // Тестирование двусвязного списка.
void doFunctionsTest(); // Тестирование вспомогательных функций.
void doFrequencyDictionaryTest(); // Тестирование частотного словаря.

#endif
