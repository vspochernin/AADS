#include "functions.hpp"

#include <cassert>
#include <ctime>
#include <iostream>
#include <fstream>

#include "frequency-dictionary.hpp"

size_t getCharCode(char ch)
{
  int temp = static_cast< int >(ch);
  if (temp >= 0)
  {
    return static_cast< size_t >(temp);
  }
  else
  {
    assert(temp > -256); // Если код <= -256 - значит что-то не так.
    return static_cast<size_t >(256 + temp);
  }
}

size_t hashByDivision(const std::string& str, size_t size)
{
  unsigned long long k = 0; // Число, в которое мы переведем нашу строку.
  unsigned long long factor = 1; // Степени 4-ки (на них будем умножать код каждого символа строки.
  for (int i = static_cast< int >(str.size()) - 1; i >= 0; i--) // Преобразуем строку в число, умножая каждый символ на соответсвующую степень 4-ки.
  {
    k += getCharCode(str[i]) * factor;
    factor *= 4;
  }
  return k % size; // Берем остаток от деления получившегося числа на размер хеш-таблицы.
}

void clearWord(std::string& str)
{
  std::string::iterator i = str.begin();
  while (i != str.end())
  {
    if (!(isRussianLetter(*i) || isEnglishLetter(*i))) // Если очередной символ - не буква...
    {
      i = str.erase(i); // ...удаляем его, присваивая итератору следующее положение.
    }
    else
    {
      i++; // Иначе просто передвигаем итератор вперед.
    }
  }
}

bool isRussianLetter(char ch)
{
  size_t firstUpperCode = 192; // Код буквы 'А'.
  size_t lastUpperCode = 223; // Код буквы 'Я'.
  size_t firstLowerCode = 224; // Код буквы 'а'.
  size_t lastLowerCode = 255; // Код буквы 'я'.
  size_t code = getCharCode(ch); // Код подаваемой на вход буквы.
  return (((code >= firstUpperCode) && (code <= lastUpperCode)) || ((code >= firstLowerCode) && (code <= lastLowerCode)));
}

bool isEnglishLetter(char ch)
{
  size_t firstUpperCode = 65; // Код буквы 'A'.
  size_t lastUpperCode = 90; // Код буквы 'Z'.
  size_t firstLowerCode = 97; // Код буквы 'a'.
  size_t lastLowerCode = 122; // Код буквы 'z'.
  size_t code = getCharCode(ch); // Код подаваемой на вход буквы.
  return (((code >= firstUpperCode) && (code <= lastUpperCode)) || ((code >= firstLowerCode) && (code <= lastLowerCode)));
}

bool isWord(const std::string& str)
{
  if (str.empty())
  {
    return false; // Пустая строка - не слово.
  }

  bool isRussian = true; // true - слово русское, false - английское.
  if (isRussianLetter(str[0]))
  {
    isRussian = true; // Первая буква русская => все слово должно быть русским.
  }
  else if (isEnglishLetter(str[0]))
  {
    isRussian = false; // Первая буква английская => все слово должно быть английским.
  }
  else
  {
    return false; // Если первая буква не прошла две предыдущие проверки, значит там не буква из алфавита.
  }

  // Проверка, чтобы все буквы слова были того же языка, что и первая.
  // При этом, автоматически фильтруются лишние символы.
  for (size_t i = 1; i < str.size(); i++)
  {
    if (isRussian)
    {
      if (!isRussianLetter(str[i]))
      {
        return false;
      }
    }
    else
    {
      if (!isEnglishLetter(str[i]))
      {
        return false;
      }
    }
  }

  return true; // true - так как пройдены все проверки.
}

void toLower(std::string& str)
{
  if (!isWord(str)) // На вход должно поступать русское/английское слово.
  {
    throw ("Incorrect word!");
  }

  if (isRussianLetter(str[0])) // Если слово русское...
  {
    size_t firstUpperCode = 192; // Код буквы 'А'.
    size_t lastUpperCode = 223; // Код буквы 'Я'.
    size_t firstLowerCode = 224; // Код буквы 'а'.
    for (size_t i = 0; i < str.size(); i++)
    {
      size_t code = getCharCode(str[i]);
      if ((code >= firstUpperCode) && (code <= lastUpperCode))
      {
        // ...заменяем каждую заглавную русскую букву прописной.
        str[i] = static_cast< char >(code + (firstLowerCode - firstUpperCode));
      }
    }
  }
  else // Если слово английское...
  {
    size_t firstUpperCode = 65; // Код буквы 'A'.
    size_t lastUpperCode = 90; // Код буквы 'Z'.
    size_t firstLowerCode = 97; // Код буквы 'a'.
    for (size_t i = 0; i < str.size(); i ++)
    {
      size_t code = getCharCode(str[i]);
      if ((code >= firstUpperCode) && (code <= lastUpperCode))
      {
        // ...заменяем каждую заглавную английскую букву прописной.
        str[i] = static_cast< char >(code + (firstLowerCode - firstUpperCode));
      }
    }
  }
}

void quickSort(std::vector< std::pair< std::string, size_t > >& vec, int l, int r)
{
  srand(time(0)); // Рандомизация.

  if (l < r) // Массив из 1 или 0 элементов уже отсортирован.
  {
    int pivotIndex = (rand() % (r - l + 1)) + l; // Выбираем случайный опорный элемент.
    std::pair< std::string, size_t > pivot = vec[pivotIndex];
    std::swap(vec[pivotIndex], vec[r]); // Ставим опорный элемент на последнее место.
    int i = l - 1; // Вспомогательная переменная, чтобы следовать по элементам, которые больше опорного.
                   // Изначально она указывает за левую границу сортируемой части массива.
    for (int j = l; j <= r - 1; j++) // Цикл, который поставит элементы, которые больше или равны опорному в начало.
    {
      if (vec[j].second >= pivot.second) // Если очередной элемент больше или равен опорному...
      {
        i++; // ...увеличиваем вспомогтельню переменную. Теперь она в том месте, где должен стоять этот элемент.
        std::swap(vec[i], vec[j]); // Меняем местами найднный элемент и элемент, на который указывает i.
      }
    }

    // В итоге, в начале массива будут элементы больше или равные опорному.
    // Причем i будет указывать на последний такой элемент.
    std::swap(vec[i + 1], vec[r]); // Переносим опорный элемент на своё место (за последним большим или равным ему).
    pivotIndex = i + 1; // Его индекс, соответственно, стал i + 1.
    quickSort(vec, l, pivotIndex - 1); // Сортируем левую от опорного элемента часть массива.
    quickSort(vec, pivotIndex + 1, r); // Сортируем правую от опорного элемента часть массива.
  }
}

void printVector(const std::vector< std::pair< std::string, size_t > >& vec, std::ostream& out)
{
  for (size_t i = 0; i < vec.size(); i++)
  {
    out << vec[i].first << ": " << vec[i].second << "\n";
  }
}

void startProgram()
{
  FrequencyDictionary dictionary;
  std::cout << "------------------------------------------------------\n"
            << "Началось выполнение программы\n"
            << "\"help\" - посмотреть полный список команд\n"
            << "\"exit\" - выйти из программы\n"
            << "------------------------------------------------------\n";
  std::string input = "";
  while (true)
  {
    try
    {
      std::cin >> input;
      if (input == "help")
      {
        showHelp();
      }
      else if (input == "insert")
      {
        doInsert(dictionary);
      }
      else if (input == "search")
      {
        doSearch(dictionary);
      }
      else if (input == "delete")
      {
        doDelete(dictionary);
      }
      else if (input == "readFile")
      {
        doReadFile(dictionary);
      }
      else if (input == "printThreeMost")
      {
        doPrintThreeMost(dictionary);
      }
      else if (input == "writeFile")
      {
        doWriteFile(dictionary);
      }
      else if (input == "exit")
      {
        break;
      }
      else
      {
        std::cout << "Некорректная команда. Введите команду заново.\n";
      }
    }
    catch (const std::exception& error)
    {
      std::cout << error.what() << "\n" << "Введите команду заново.\n";
    }
  }
}

void showHelp()
{
  std::cout << "------------------------------------------------------\n"
            << "Список команд:\n"
            << "\"help\" - посмотреть полный список команд\n"
            << "\"exit\" - выйти из программы\n"
            << "\"insert\" - добавить слово\n"
            << "\"search\" - найти слово\n"
            << "\"delete\" - удалить слово\n"
            << "\"readFile\" - добавить все слова из файла\n"
            << "\"printThreeMost\" - вывести три чаще всего встречающихся слова\n"
            << "\"writeFile\" - записать в файл слова по убыванию их встречаемости\n"
            << "------------------------------------------------------\n";
}

void doInsert(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите добавить\n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректная строка! Нужно ввести одно слово."));
  }
  dictionary.insertWord(str);
}

void doSearch(const FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите найти\n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректная строка! Нужно ввести одно слово."));
  }
  size_t count = dictionary.searchWord(str);
  std::cout << "Слово \"" << str << "\" встречается " << count << " раз.\n";
}

void doDelete(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите удалить\n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректная строка! Нужно ввести одно слово."));
  }
  if (dictionary.deleteWord(str))
  {
    std::cout << "Слово успешно удалено.\n";
  }
  else
  {
    std::cout << "Удаление не произошло, слова не было.\n";
  }
}

void doReadFile(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите имя файла, который хотите прочитать\n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректная строка! Нужно ввести только имя файла."));
  }
  dictionary.readFile(str);
}

void doPrintThreeMost(const FrequencyDictionary& dictionary)
{
  std::cout << "Три чаще всего встречающихся слова:\n";
  dictionary.printThreeMost(std::cout);
}

void doWriteFile(const FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите имя файла, в который хотите записать\n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректная строка! Нужно ввести только имя файла."));
  }
  std::ofstream fout(str);
  if (!fout)
  {
    throw(std::runtime_error("Ошибка открытия файла!"));
  }
  dictionary.printSorted(fout);
}

void testProgram()
{
  doDoubleLinkedListTest();
}

void doDoubleLinkedListTest()
{
  std::cout << "---------------------------------ТЕСТИРОВАНИЕ ДВУСВЯЗНОГО СПИСКА---------------------------------\n";
  std::cout << "-----------------ТЕСТ 1: ПУСТОЙ СПИСОК-----------------\n";
  DoubleLinkedList list;
  std::cout << "Количество элементов: " << list.count() << "\n";
  std::cout << "Сам список: \n";
  list.print(std::cout);

  std::cout << "Слово \"тест\" встречается в списке " << list.searchItem("тест") << " раз.\n";

  std::cout << "Удаление слова \"тест\": " << (list.deleteItem("тест") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  std::cout << "Сам список: \n";

  list.print(std::cout);
  std::vector< std::pair< std::string, size_t > > vec;
  list.fillVector(vec);
  std::cout << "Вектор, заполненный пустым списокм:\n";
  printVector(vec, std::cout);

  std::vector< std::pair< std::string, size_t > > vec3;
  std::pair< std::string, size_t > emptyPair;
  emptyPair.first = "";
  emptyPair.second = 0;
  for (size_t i = 0; i < 3; i++)
  {
    vec3.push_back(emptyPair);
  }
  list.fillThreeMost(vec3);
  std::cout << "Вектор трех чаще всего встречающихся слов, заполненный пустым списокм:\n";
  printVector(vec3, std::cout);
  std::cout << "-------------------------------------------------------\n";

  std::cout << "-----------------ТЕСТ 2: ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ И ПОИСК--\n";
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("программирование");
  list.insertItem("программирование");
  list.insertItem("студент");
  list.insertItem("студент");
  list.insertItem("студент");
  list.insertItem("преподаватель");
  std::cout << "Количество элементов: " << list.count() << "\n";
  std::cout << "Сам список: \n";
  list.print(std::cout);

  std::cout << "Слово \"тест\" встречается в списке " << list.searchItem("тест") << " раз.\n";
  std::cout << "Слово \"дедлайн\" встречается в списке " << list.searchItem("дедлайн") << " раз.\n";

  std::cout << "-------------------------------------------------------\n";

  std::cout << "-----------------ТЕСТ 3: УДАЛЕНИЕ ЭЛЕМЕНТОВ------------\n";
  std::cout << "Список до удаления элементов:\n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);

  std::cout << "Удаление слова \"тест\": " << (list.deleteItem("тест") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"дедлайн\": " << (list.deleteItem("дедлайн") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"студент\": " << (list.deleteItem("студент") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"тест\": " << (list.deleteItem("тест") ? "произошло." : "не произошло.") << "\n";

  std::cout << "Список после удаления элементов:\n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 3: ЗАПОЛНЕНИЕ ВЕКТОРОВ------------\n";
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("тест");
  list.insertItem("язык");
  list.insertItem("язык");
  list.insertItem("язык");
  list.insertItem("язык");
  list.insertItem("язык");
  list.insertItem("право");
  std::cout << "Сам список: \n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);

  list.fillVector(vec);
  std::cout << "Вектор, заполненный пустым списокм:\n";
  printVector(vec, std::cout);

  list.fillThreeMost(vec3);
  std::cout << "Вектор трех чаще всего встречающихся слов, заполненный пустым списокм:\n";
  printVector(vec3, std::cout);
  std::cout << "-------------------------------------------------------\n";
  std::cout << "----------------ТЕСТ 4: ОЧИСТКА СПИСКА-----------------\n";
  std::cout << "Список до очкстки: \n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);

  list.clear();
  std::cout << "Список после очкстки: \n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);
  std::cout << "-------------------------------------------------------\n";
  std::cout << "-------------------------------------------------------------------------------------------------\n";
}
