#include "frequency-dictionary.hpp"

#include <fstream>
#include <exception>

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
  std::string word = str; // Слово, которое непосредственно будем добавлять.
  clearWord(word); // Очищаем слово от не букв.

  if (isWord(word)) // Проверяем на соответствие слову.
  {
    toLower(word); // Переводим слово в нижний регистр.
    // Одновременно добавляем элемент в таблицу
    // и проверяем, произошло добавление или просто увеличение счетчика.
    if (data_[hashByDivision(word, size_)].insertItem(word))
    {
      count_++;
    }
  }
  else
  {
    throw (std::invalid_argument("Некооректное слово при добавлении!"));
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

void FrequencyDictionary::readFile(const std::string& fileName)
{
  std::ifstream fin(fileName);
  if (!fin)
  {
    throw(std::runtime_error("Ошибка открытия файла!"));
  }

  std::string str = "";
  while (!fin.eof())
  {
    fin >> str; // Считываем очередную строку из файла.
    try
    {
      insertWord(str);
    }
    catch (const std::invalid_argument & error)
    {}
  }
}

void FrequencyDictionary::printUnsorted(std::ostream& out)
{
  for (size_t i = 0; i < size_; i++)
  {
    data_[i].print(out);
  }
}

void FrequencyDictionary::fillVector(std::vector < std::pair< std::string, size_t > > &vec)
{
  vec.clear();
  for (size_t i = 0; i < size_; i++)
  {
    data_[i].fillVector(vec);
  }
}

void FrequencyDictionary::printSorted(std::ostream &out)
{
  std::vector< std::pair< std::string, size_t > > vec;
  fillVector(vec);
  quickSort(vec, 0, vec.size() - 1);
  for (size_t i = 0; i < vec.size(); i++)
  {
    out << vec[i].first << ": " << vec[i].second << "\n";
  }
}

std::vector< std::pair< std::string, size_t > > FrequencyDictionary::getThreeMost()
{
  std::vector< std::pair< std::string, size_t > > vec;
  std::pair< std::string, size_t > emptyPair;
  emptyPair.first = "";
  emptyPair.second = 0;
  for (size_t i = 0; i < 3; i++)
  {
    vec.push_back(emptyPair);
  }

  for (size_t i = 0; i < size_; i++)
  {
    data_[i].fillThreeMost(vec);
  }

  return vec;
}

void FrequencyDictionary::printThreeMost(std::ostream& out)
{
  std::vector< std::pair< std::string, size_t > > vec = getThreeMost();
  for (size_t i = 0; i < vec.size(); i++)
  {
    out << vec[i].first << ": " << vec[i].second << "\n";
  }
}

