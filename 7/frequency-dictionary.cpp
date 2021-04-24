#include "frequency-dictionary.hpp"

#include <fstream>

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

void FrequencyDictionary::readFile(const std::string& fileName)
{
  std::ifstream fin(fileName);
  if (!fin)
  {
    throw("File open error!");
  }

  std::string str = "";
  while (!fin.eof())
  {
    fin >> str; // Считываем очередную строку из файла.
    clearWord(str); // Очищаем строку от не букв.
    if (isWord(str)) // Проверяем строку на соответствие слову.
    {
      toLower(str); // Переводим её в нижний регистр.
      insertWord(str); // Записываем её в хеш-таблицу (или увеличиваем счетчик).
    }
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

