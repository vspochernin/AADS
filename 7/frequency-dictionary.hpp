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
  FrequencyDictionary(); // Конструктор "по умолчанию" - создание словаря с размером "по умолчанию".

  explicit FrequencyDictionary(size_t size); // Консутрктор словаря с конкретным размером.

  ~FrequencyDictionary(); // Деструктор словаря.

  void insertWord(const std::string& str); // Добавление слова или увеличение счетчика его вхождений.
  size_t searchWord(const std::string& str) const; // Поиск количества вхождений слова.
  bool deleteWord(const std::string& str); // Удаление слова.
  void readFile(const std::string& fileName); // Чтение слова из файла в хеш-таблицу.
  void fillVector(std::vector< std::pair< std::string, size_t > >& vec) const; // Заполнение поступающего на вход вектора пар хеш-таблицей.
  std::vector< std::pair < std::string, size_t > > getThreeMost() const; // Получение вектора пар трех чаще всего встречающихся слов.
  void printUnsorted(std::ostream& out) const; // Печать хеш-таблицы в out (в неосортированном виде).
  void printSorted(std::ostream& out) const; // Печать хеш-таблицы в out (в отсортированном виде).
  void printThreeMost(std::ostream& out) const; // Печать трех чаще всего встречающихся слова в out.
  void clear(); // Очищение словаря.
  size_t size(); // Размер словаря.
  size_t count(); // Количество записей в словаре.
  size_t collisions(); // Количество коллизий в словаре.

private:
  size_t size_; // Размер массива двусвязных списков (размер хеш-таблицы).
  size_t count_; // Количество записей (слов, записанных в хеш-таблицу).
  DoubleLinkedList* data_; // Массив двусвязных списков (сама хеш-таблица).
};

#endif
