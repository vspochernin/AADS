#ifndef FREQUENCY_DICTIONARY_HPP
#define FREQUENCY_DICTIONARY_HPP

#include <string>
#include <iostream>
#include <vector>

#include "double-linked-list.hpp"
#include "functions.hpp"

class FrequencyDictionary
{
public:
  FrequencyDictionary();

  explicit FrequencyDictionary(size_t size);

  ~FrequencyDictionary();

  void insertWord(const std::string& str); // Добавление слова или увеличение счетчика его частотности.
  size_t searchWord(const std::string& str); // Поиск слова (получаем значение - его частотность).
  void deleteWord(const std::string& str); // Удаление слова.
  void readFile(const std::string& fileName); // Прочитать слова из файла в хеш-таблицу.
  void printUnsorted(std::ostream& out); // Напечатать хеш-таблицу в out (в неосортированном виде).
  void fillVector(std::vector< std::pair< std::string, size_t > >& vec); // Заполнить поступающий на вход вектор пар хеш-таблицей.
  void printSorted(std::ostream& out); // Напечатать хеш-таблицу в out (в отсортированном виде).

private:
  size_t size_; // Размер массива двусвязных списков (размер хеш-таблицы).
  size_t count_; // Количество записей (слов, записанных в хеш-таблицу).
  DoubleLinkedList* data_; // Массив двусвязных списков (сама хеш-таблица).
};

#endif
