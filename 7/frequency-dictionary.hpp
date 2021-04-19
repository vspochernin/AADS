#ifndef FREQUENCY_DICTIONARY_HPP
#define FREQUENCY_DICTIONARY_HPP

#include <string>

#include "double-linked-list.hpp"
#include "functions.hpp"

class FrequencyDictionary
{
public:
  FrequencyDictionary();

  explicit FrequencyDictionary(size_t size);

  ~FrequencyDictionary();

  void insertWord(const std::string& str);
  size_t searchWord(const std::string& str);
  void deleteWord(const std::string& str);

private:
  size_t size_; // Размер массива двусвязных списков.
  size_t count_; // Количество записей (слов).
  DoubleLinkedList* data_; // Массив двусвязных списков.
};

#endif
