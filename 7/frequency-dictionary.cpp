#include "frequency-dictionary.hpp"

const size_t defaultSize = 1511; // Рандомное простое число.

FrequencyDictionary::FrequencyDictionary():
  size_(defaultSize),
  count_(0),
  data_(new DoubleLinkedList[defaultSize])
{}

FrequencyDictionary::FrequencyDictionary(size_t size):
  size_(size),
  count_(0),
  data_(new DoubleLinkedList[size])
{}

FrequencyDictionary::~FrequencyDictionary()
{
  delete[] data_;
}

void FrequencyDictionary::insertWord(const std::string& str)
{
  // Одновременно добавляем элемент в таблицу
  // и проверяем, произошло добавление или просто увеличение счетчика.
  if (data_[hashByDivision(str, size_)].insertItem(str))
  {
    count_++;
  }
}

size_t FrequencyDictionary::searchWord(const std::string& str)
{
  // Ищем значение по ключу str в сответствующем двусвязном списке.
  // Если слова в хеш таблице нет - просто получим 0.
  return data_[hashByDivision(str, size_)].searchItem(str);
}

void FrequencyDictionary::deleteWord(const std::string& str)
{
  // Одновременно производим попытку удаления
  // и уменьшение счетчика, если удаление произошло.
  if (data_[hashByDivision(str, size_)].deleteItem(str))
  {
    count_--;
  }
}

