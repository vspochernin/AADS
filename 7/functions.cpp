#include "functions.hpp"

#include <cassert> // Для assert.
#include <ctime> // Для рандомизации.
#include <iostream>
#include <fstream>
#include <iomanip> // Для красивого вывода.

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
    assert(temp > -256); // Если код <= -256 - значит что-то не так. Так не должно быть впринципе.
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
  std::string::iterator i = str.begin(); // Итератор на начало слова.
  while (i != str.end()) // Пока мы не дошли до конца слова...
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
  size_t additionalUpperCode = 168; // Код буквы 'Ё'.
  size_t additionalLowerCode = 184; // Код буквы 'ё'.
  size_t code = getCharCode(ch); // Код подаваемой на вход буквы.
  return (((code >= firstUpperCode) && (code <= lastUpperCode)) ||
          ((code >= firstLowerCode) && (code <= lastLowerCode)) ||
          (code == additionalUpperCode) ||
          (code == additionalLowerCode));
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
    throw (std::invalid_argument("На вход поступило не слово!"));
  }

  if (isRussianLetter(str[0])) // Если слово русское...
  {
    size_t firstUpperCode = 192; // Код буквы 'А'.
    size_t lastUpperCode = 223; // Код буквы 'Я'.
    size_t firstLowerCode = 224; // Код буквы 'а'.
    size_t additionalUpperCode = 168; // Код буквы 'Ё'.
    size_t additionalLowerCode = 184; // Код буквы 'ё'.
    for (size_t i = 0; i < str.size(); i++)
    {
      size_t code = getCharCode(str[i]);
      if ((code >= firstUpperCode) && (code <= lastUpperCode))
      {
        // ...заменяем каждую заглавную русскую букву прописной.
        str[i] = static_cast< char >(code + (firstLowerCode - firstUpperCode));
      }
      else if (code == additionalUpperCode) // Не забываем про букву 'Ё'.
      {
        str[i] = static_cast < char >(additionalLowerCode);
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
      std::cout << "Введите команду: ";
      std::cin >> input;
      if (std::cin.fail() || std::cin.peek() != 10)
      {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        throw (std::invalid_argument("Некорректная команда!"));
      }
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
      else if (input == "print")
      {
        doPrint(dictionary);
      }
      else if (input == "printThreeMost")
      {
        doPrintThreeMost(dictionary);
      }
      else if (input == "writeFile")
      {
        doWriteFile(dictionary);
      }
      else if (input == "clear")
      {
        doClear(dictionary);
      }
      else if (input == "exit")
      {
        break;
      }
      else
      {
        throw (std::invalid_argument("Некорректная команда!"));
      }
    }
    catch (const std::exception& error)
    {
      std::cout << "Ошибка: " << error.what() << "\n";
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
            << "\"print\" - вывести весь словарь\n"
            << "\"printThreeMost\" - вывести три чаще всего встречающихся слова\n"
            << "\"writeFile\" - записать в файл слова по убыванию их встречаемости\n"
            << "\"clear\" - очистить словарь\n"
            << "------------------------------------------------------\n";
}

void doInsert(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите добавить: ";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректное слово!"));
  }
  dictionary.insertWord(str);
  std::cout << "Успешно.\n";
}

void doSearch(const FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите найти: ";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректное слово!"));
  }
  size_t count = dictionary.searchWord(str);
  std::cout << "Слово \"" << str << "\" встречается " << count << " раз.\n";
}

void doDelete(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите слово, которое хотите удалить: \n";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректное слово!"));
  }
  if (dictionary.deleteWord(str))
  {
    std::cout << "Слово успешно удалено.\n";
  }
  else
  {
    std::cout << "Удаление не произошло, слова в словаре не было.\n";
  }
}

void doReadFile(FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите имя файла, который хотите прочитать: ";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректное имя файла!"));
  }
  dictionary.readFile(str);
  std::cout << "Успешно.\n";
}

void doPrint(FrequencyDictionary& dictionary)
{
  dictionary.printSorted(std::cout);
}

void doPrintThreeMost(const FrequencyDictionary& dictionary)
{
  std::cout << "Три чаще всего встречающихся слова:\n";
  dictionary.printThreeMost(std::cout);
}

void doWriteFile(const FrequencyDictionary& dictionary)
{
  std::string str;
  std::cout << "Введите имя файла, в который хотите записать: ";
  std::cin >> str;
  if (std::cin.fail() || std::cin.peek() != 10)
  {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
    throw (std::invalid_argument("Некорректное имя файла!"));
  }
  std::ofstream fout(str);
  if (!fout)
  {
    throw(std::runtime_error("Ошибка открытия файла!"));
  }
  dictionary.printSorted(fout);
  std::cout << "Успешно.\n";
  fout.close();
}

void doClear(FrequencyDictionary& dictionary)
{
  dictionary.clear();
  std::cout << "Словарь успешно очищен.\n";
}

void testProgram()
{
  doDoubleLinkedListTest();
  doFunctionsTest();
  doFrequencyDictionaryTest();
}

void doDoubleLinkedListTest()
{
  std::cout << "---------------------------------ТЕСТИРОВАНИЕ ДВУСВЯЗНОГО СПИСКА---------------------------------\n";
  std::cout << "-----------------ТЕСТ 1: ПУСТОЙ СПИСОК-----------------\n";
  DoubleLinkedList list;
  std::cout << "Количество элементов: " << list.count() << "\n";
  std::cout << "Сам список: \n";
  list.print(std::cout);

  std::cout << "Слово \"test\" встречается в списке " << list.searchItem("test") << " раз.\n";

  std::cout << "Удаление слова \"test\": " << (list.deleteItem("test") ? "произошло." : "не произошло.") << "\n";
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
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("programming");
  list.insertItem("programming");
  list.insertItem("student");
  list.insertItem("student");
  list.insertItem("student");
  list.insertItem("teacher");
  std::cout << "Количество элементов: " << list.count() << "\n";
  std::cout << "Сам список: \n";
  list.print(std::cout);

  std::cout << "Слово \"test\" встречается в списке " << list.searchItem("test") << " раз.\n";
  std::cout << "Слово \"deadline\" встречается в списке " << list.searchItem("deadline") << " раз.\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "-----------------ТЕСТ 3: УДАЛЕНИЕ ЭЛЕМЕНТОВ------------\n";
  std::cout << "Список до удаления элементов:\n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);

  std::cout << "Удаление слова \"test\": " << (list.deleteItem("test") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"deadline\": " << (list.deleteItem("deadline") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"student\": " << (list.deleteItem("student") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"test\": " << (list.deleteItem("test") ? "произошло." : "не произошло.") << "\n";

  std::cout << "Список после удаления элементов:\n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 4: ЗАПОЛНЕНИЕ ВЕКТОРОВ------------\n";
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("test");
  list.insertItem("language");
  list.insertItem("language");
  list.insertItem("language");
  list.insertItem("language");
  list.insertItem("language");
  list.insertItem("law");
  std::cout << "Сам список: \n";
  std::cout << "Количество элементов: " << list.count() << "\n";
  list.print(std::cout);

  list.fillVector(vec);
  std::cout << "Вектор, заполненный списком:\n";
  printVector(vec, std::cout);

  list.fillThreeMost(vec3);
  std::cout << "Вектор трех чаще всего встречающихся слов:\n";
  printVector(vec3, std::cout);

  vec.clear();
  std::cout << "Вектор, заполненный пустым списокм:\n";
  printVector(vec, std::cout);
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 5: ОЧИСТКА СПИСКА-----------------\n";
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

void doFunctionsTest()
{
  std::cout << "---------------------------------ТЕСТИРОВАНИЕ ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ---------------------------------\n";
  std::cout << "----------------ТЕСТ 1: getCharCode()-----------------\n";
  std::ifstream finRussianLetters("russianLetters.txt"); // Берём их из файла, потому что должна быть другая кодировка (в IDE UTF-8).
  std::string russianLetters = "";
  finRussianLetters >> russianLetters;
  finRussianLetters.close();
  std::string englishLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::string randomSymbols = "!@#$%^&*()_-+=";

  std::cout << "Русские буквы:\n";
  for (size_t i = 0; i < russianLetters.size(); i++)
  {
    std::cout << russianLetters[i] << ": " << std::setw(4) << getCharCode(russianLetters[i]) << ", ";
    if ((i != 0) && (i % 7 == 0))
    {
      std::cout << "\n";
    }
  }

  std::cout << "Английские буквы:\n";
  for (size_t i = 0; i < englishLetters.size(); i++)
  {
    std::cout << englishLetters[i] << ": " << std::setw(4) << getCharCode(englishLetters[i]) << ", ";
    if ((i != 0) && (i % 7 == 0))
    {
      std::cout << "\n";
    }
  }

  std::cout << "Случайные символы:\n";
  for (size_t i = 0; i < randomSymbols.size(); i++)
  {
    std::cout << randomSymbols[i] << ": " << std::setw(4) << getCharCode(randomSymbols[i]) << ", ";
    if ((i != 0) && (i % 7 == 0))
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 2: hashByDivision()---------------\n";
  std::cout << "Пусть размер таблицы - простое число 23.\n";
  std::cout << "Слово \"test\": " << hashByDivision("test", 23) << "\n";
  std::cout << "Слово \"programmer\": " << hashByDivision("programmer", 23) << "\n";
  std::cout << "Слово \"deadline\": " << hashByDivision("deadline", 23) << "\n";
  std::cout << "Слово \"student\": " << hashByDivision("student", 23) << "\n";
  std::cout << "Слово \"teacher\": " << hashByDivision("teacher", 23) << "\n";
  std::cout << "Слово \"language\": " << hashByDivision("language", 23) << "\n";

  std::cout << "Еще раз (чтобы проверить неизменность хешей).\n";
  std::cout << "Слово \"test\": " << hashByDivision("test", 23) << "\n";
  std::cout << "Слово \"programmer\": " << hashByDivision("programmer", 23) << "\n";
  std::cout << "Слово \"deadline\": " << hashByDivision("deadline", 23) << "\n";
  std::cout << "Слово \"student\": " << hashByDivision("student", 23) << "\n";
  std::cout << "Слово \"teacher\": " << hashByDivision("teacher", 23) << "\n";
  std::cout << "Слово \"language\": " << hashByDivision("language", 23) << "\n";

  std::cout << "А теперь пусть размер таблицы - простое число 137.\n";
  std::cout << "Слово \"test\": " << hashByDivision("test", 137) << "\n";
  std::cout << "Слово \"programmer\": " << hashByDivision("programmer", 137) << "\n";
  std::cout << "Слово \"deadline\": " << hashByDivision("deadline", 137) << "\n";
  std::cout << "Слово \"student\": " << hashByDivision("student", 137) << "\n";
  std::cout << "Слово \"teacher\": " << hashByDivision("teacher", 137) << "\n";
  std::cout << "Слово \"language\": " << hashByDivision("language", 137) << "\n";

  std::cout << "Еще раз (чтобы проверить неизменность хешей).\n";
  std::cout << "Слово \"test\": " << hashByDivision("test", 137) << "\n";
  std::cout << "Слово \"programmer\": " << hashByDivision("programmer", 137) << "\n";
  std::cout << "Слово \"deadline\": " << hashByDivision("deadline", 137) << "\n";
  std::cout << "Слово \"student\": " << hashByDivision("student", 137) << "\n";
  std::cout << "Слово \"teacher\": " << hashByDivision("teacher", 137) << "\n";
  std::cout << "Слово \"language\": " << hashByDivision("language", 137) << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 3: isRussianLetter()--------------\n";
  std::cout << "Пройдемся по всем русским буквам.\n";
  for (size_t i = 0; i < russianLetters.size(); i++)
  {
    std::cout << russianLetters[i] << ": " << std::setw(4) << (isRussianLetter(russianLetters[i]) ? "Да" : "Нет") << ", ";
    if ((i != 0) && (i % 7 == 0))
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  std::cout << "Q" << ": " << std::setw(4) << (isRussianLetter('Q') ? "Да" : "Нет") << "\n";
  std::cout << "r" << ": " << std::setw(4) << (isRussianLetter('r') ? "Да" : "Нет") << "\n";
  std::cout << "!" << ": " << std::setw(4) << (isRussianLetter('!') ? "Да" : "Нет") << "\n";
  std::cout << " " << ": " << std::setw(4) << (isRussianLetter(' ') ? "Да" : "Нет") << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 4: isEnglishLetter()--------------\n";
  std::cout << "Пройдемся по всем английским буквам.\n";
  for (size_t i = 0; i < englishLetters.size(); i++)
  {
    std::cout << englishLetters[i] << ": " << std::setw(4) << (isEnglishLetter(englishLetters[i]) ? "Да" : "Нет") << ", ";
    if ((i != 0) && (i % 7 == 0))
    {
      std::cout << "\n";
    }
  }
  std::cout << "\n";
  std::cout << ";" << ": " << std::setw(4) << (isEnglishLetter(';') ? "Да" : "Нет") << "\n";
  std::cout << "-" << ": " << std::setw(4) << (isEnglishLetter('-') ? "Да" : "Нет") << "\n";
  std::cout << "!" << ": " << std::setw(4) << (isEnglishLetter('!') ? "Да" : "Нет") << "\n";
  std::cout << " " << ": " << std::setw(4) << (isEnglishLetter(' ') ? "Да" : "Нет") << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 5: clearWord()--------------------\n";
  std::string word = "Hello,";
  std::cout << "\"" << word << "\": ";
  clearWord(word);
  std::cout << "\"" << word << "\"\n";

  word = "@#@q&^w&^&*e&^&*r^%&t^&%&^y#@#";
  std::cout << "\"" << word << "\": ";
  clearWord(word);
  std::cout << "\"" << word << "\"\n";

  word = "O0neMo0reTest";
  std::cout << "\"" << word << "\": ";
  clearWord(word);
  std::cout << "\"" << word << "\"\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 6: isWord()-----------------------\n";
  std::cout << "Сначала пройдемся по случайным русским словам.\n";
  std::ifstream finRussianWords("russianWords.txt"); // Берём их из файла, потому что должна быть другая кодировка (в IDE UTF-8).
  while (!finRussianWords.eof())
  {
    finRussianWords >> word;
    std::cout << "\"" << word << "\": " << (isWord(word) ? "Да\n" : "Нет\n");
  }
  finRussianWords.close();

  std::cout << "Теперь по английским.\n";
  std::cout << "\"" << "dog" << "\": " << (isWord("dog") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "function" << "\": " << (isWord("function") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "quality" << "\": " << (isWord("quality") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "Member" << "\": " << (isWord("Member") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "WeATHeR" << "\": " << (isWord("WeATHeR") ? "Да\n" : "Нет\n");

  std::cout << "Теперь по НЕ словам.\n";
  std::cout << "\"" << "do!g" << "\": " << (isWord("do!g") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "@function" << "\": " << (isWord("@function") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "quality#" << "\": " << (isWord("quality#") ? "Да\n" : "Нет\n");
  std::cout << "\"" << "$@$@$@" << "\": " << (isWord("$@$@$@") ? "Да\n" : "Нет\n");
  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 7: toLower()----------------------\n";
  std::cout << "Сначала пройдемся по русским словам.\n";
  finRussianWords.open("russianWords.txt");
  while(!finRussianWords.eof())
  {
    finRussianWords >> word;
    std::cout << "\"" << word << "\": ";
    toLower(word);
    std::cout << "\"" << word << "\"\n";
  }
  finRussianWords.close();

  std::cout << "Теперь по английским.\n";
  word = "DOG";
  std::cout << "\"" << word << "\": ";
  toLower(word);
  std::cout << "\"" << word << "\"\n";

  word = "fUnCtIoN";
  std::cout << "\"" << word << "\": ";
  toLower(word);
  std::cout << "\"" << word << "\"\n";

  word = "QuAlItY";
  std::cout << "\"" << word << "\": ";
  toLower(word);
  std::cout << "\"" << word << "\"\n";

  std::cout <<"Теперь проверим возникновение исключеня, если передать функции не слово.\n";
  word = "Hel!@@#!lo";
  std::cout << "\"" << word << "\": ";
  try
  {
    toLower(word);
    std::cout << "\"" << word << "\"\n";
  }
  catch (const std::exception& error)
  {
    std::cout << error.what() << "\n";
  }

  std::cout << "-------------------------------------------------------\n";

  std::cout << "----------------ТЕСТ 8: quickSort() и printVector()----\n";
  std::vector< std::pair< std::string, size_t > > vec;
  std::cout << "Пустой вектор до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Пустой вектор после сортировки:\n";
  printVector(vec, std::cout);

  vec.push_back(std::make_pair("test", 1));
  std::cout << "Вектор с одним элементом до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Вектор с одним элементом после сортировки:\n";
  printVector(vec, std::cout);

  vec.push_back(std::make_pair("programmer", 42));
  std::cout << "Вектор с двумя элементами до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Вектор с двумя элементами после сортировки:\n";
  printVector(vec, std::cout);

  vec.push_back(std::make_pair("deadline", 422));
  std::cout << "Вектор с тремя элементами до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Вектор с тремя элементами после сортировки:\n";
  printVector(vec, std::cout);

  vec.clear();
  vec.push_back(std::make_pair("test", 422));
  vec.push_back(std::make_pair("student", 300));
  vec.push_back(std::make_pair("programmer", 150));
  vec.push_back(std::make_pair("teacher", 43));
  vec.push_back(std::make_pair("language", 2));
  std::cout << "Лучший случай до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Лучший случай после сортировки:\n";
  printVector(vec, std::cout);

  vec.clear();
  vec.push_back(std::make_pair("test", 2));
  vec.push_back(std::make_pair("student", 42));
  vec.push_back(std::make_pair("programmer", 34));
  vec.push_back(std::make_pair("teacher", 150));
  vec.push_back(std::make_pair("language", 1));
  std::cout << "Средний случай до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Средний случай после сортировки:\n";
  printVector(vec, std::cout);

  vec.clear();
  vec.push_back(std::make_pair("test", 1));
  vec.push_back(std::make_pair("student", 23));
  vec.push_back(std::make_pair("programmer", 242));
  vec.push_back(std::make_pair("teacher", 1234));
  vec.push_back(std::make_pair("language", 4444));
  std::cout << "Худший случай до сортировки:\n";
  printVector(vec, std::cout);
  quickSort(vec, 0, vec.size() - 1);
  std::cout << "Худший случай после сортировки:\n";
  printVector(vec, std::cout);
  std::cout << "-------------------------------------------------------\n";
  std::cout << "------------------------------------------------------------------------------------------------------\n";
}

void doFrequencyDictionaryTest()
{
  std::cout << "---------------------------------ТЕСТИРОВАНИЕ ЧАСТОТНОГО СЛОВАРЯ--------------------------------------\n";
  std::cout << "Перед началом тестов хочу отметить, что функции fillVector() и getThreeMost()\n"
            << "тестируются неявно, так как они являются ключевыми в printSorted() и printThreeMost().\n";
  std::cout << "------------ТЕСТ 1: ТАБЛИЦА С НУЛЕВЫМ РАЗМЕРОМ--------\n";
  try
  {
    FrequencyDictionary zeroSizedDictionary(0);
  }
  catch(const std::exception& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "-------------------------------------------------------\n";

  std::cout << "------------ТЕСТ 2: ПУСТОЙ СЛОВАРЬ---------------------\n";
  FrequencyDictionary dictionary;
  std::cout << "Размер пустого словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в пустом словаре: " << dictionary.count() << "\n";
  std::cout << "Пустой словарь в неотсортированном виде:\n";
  dictionary.printUnsorted(std::cout);
  std::cout << "Пустой словарь в отсортированном виде:\n";
  dictionary.printSorted(std::cout);
  std::cout << "Три чаще всего встречающихся слова пустого словаря:\n";
  dictionary.printThreeMost(std::cout);

  std::cout << "Слово \"test\" встречается в списке " << dictionary.searchWord("test") << " раз.\n";

  std::cout << "Удаление слова \"test\": " << (dictionary.deleteWord("test") ? "произошло." : "не произошло.") << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "------------ТЕСТ 3: ДОБАВЛЕНИЕ, ВЫВОД И ПОИСК----------\n";
  std::cout << "Вручную я буду добавлять только английские слова из-за кодировки IDE.\n";
  dictionary.insertWord("test");
  dictionary.insertWord("test");
  dictionary.insertWord("student");
  dictionary.insertWord("student");
  dictionary.insertWord("student");
  dictionary.insertWord("student");
  dictionary.insertWord("teacher");
  dictionary.insertWord("teacher");
  dictionary.insertWord("teacher");
  dictionary.insertWord("teacher");
  dictionary.insertWord("teacher");
  dictionary.insertWord("deadline");
  std::cout << "Размер словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << dictionary.count() << "\n";
  std::cout << "Словарь в неотсортированном виде:\n";
  dictionary.printUnsorted(std::cout);
  std::cout << "Словарь в отсортированном виде:\n";
  dictionary.printSorted(std::cout);
  std::cout << "Три чаще всего встречающихся слова:\n";
  dictionary.printThreeMost(std::cout);
  std::cout << "Слово \"test\" встречается в списке " << dictionary.searchWord("test") << " раз.\n";
  std::cout << "Слово \"teacher\" встречается в списке " << dictionary.searchWord("teacher") << " раз.\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "------------ТЕСТ 4: УДАЛЕНИЕ СЛОВ----------------------\n";
  std::cout << "Размер словаря до удаления: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре до удаления: " << dictionary.count() << "\n";
  std::cout << "Словарь в отсортированном виде до удаления:\n";
  dictionary.printSorted(std::cout);

  std::cout << "Слово \"test\" встречается в списке " << dictionary.searchWord("test") << " раз.\n";
  std::cout << "Удаление слова \"test\": " << (dictionary.deleteWord("test") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"deadline\": " << (dictionary.deleteWord("deadline") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Слово \"test\" встречается в списке " << dictionary.searchWord("test") << " раз.\n";

  std::cout << "Словарь в отсортированном виде после удаления:\n";
  dictionary.printSorted(std::cout);
  std::cout << "Размер словаря после удаления: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре после удаления: " << dictionary.count() << "\n";
  std::cout << "Удаление слова \"student\": " << (dictionary.deleteWord("student") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Удаление слова \"teacher\": " << (dictionary.deleteWord("teacher") ? "произошло." : "не произошло.") << "\n";
  std::cout << "Словарь в отсортированном виде после удаления:\n";
  dictionary.printSorted(std::cout);
  std::cout << "Размер словаря после удаления: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре после удаления: " << dictionary.count() << "\n";
  std::cout << "-------------------------------------------------------\n";

  std::cout << "------------ТЕСТ 5: ЧТЕНИЕ ФАЙЛА----------------------\n";
  std::cout << "В качестве примера будет прочитана первая глава Капитанской дочки Пушкина.\n";
  std::cout << "Скорее всего, тесты будут запускаться на linux терминале, где не видна кодировка русских слов словаря.\n";
  std::cout << "В связи с этим на консоль я выведу только три чаще всего встречающихся слова, "
            << "а весь словарь в отсортированном виде выведу в файл sampleOutput.txt.\n";
  dictionary.readFile("sampleInput.txt");
  std::cout << "Размер словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << dictionary.count() << "\n";
  std::cout << "Три чаще всего встречающихся слова:\n";
  dictionary.printThreeMost(std::cout);
  std::ofstream fout("sampleOutput.txt");
  dictionary.printSorted(fout);
  fout.close();
  std::cout << "Словарь в отсортированном виде напечатан в файл sampleOutput.txt\n";

  std::cout << "Теперь проверим возникновение исключения при попытке открыть несуществующий файл.\n";
  try
  {
    dictionary.readFile("awdadadwa.awdawdadaw");
  }
  catch(const std::exception& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "-------------------------------------------------------\n";

  std::cout << "------------ТЕСТ 6: ОЧИЩЕНИЕ СЛОВАРЯ-------------------\n";
  std::cout << "Размер словаря до очищения: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре до очищения: " << dictionary.count() << "\n";
  std::cout << "Очищение словаря.\n";
  dictionary.clear();
  std::cout << "Размер словаря после очищения: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре после очищения: " << dictionary.count() << "\n";
  std::cout << "-------------------------------------------------------\n";
  std::cout << "------------ТЕСТ 7: КОЛЛИЗИИ---------------------------\n";
  std::cout << "Проверим возникновение коллизий в словаре\n";
  std::cout << "Изначально имеем пустой словарь.\n";
  std::cout << "Размер словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << dictionary.count() << "\n";
  std::cout << "Количество коллизий в словаре: " << dictionary.collisions() << "\n";
  std::cout << "Добавим в словарь 1 элемент.\n";
  dictionary.insertWord("test");
  std::cout << "Размер словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << dictionary.count() << "\n";
  std::cout << "Количество коллизий в словаре: " << dictionary.collisions() << "\n";
  std::cout << "Прочитаем в словарь наш файл\n";
  dictionary.readFile("sampleInput.txt");
  std::cout << "Размер словаря: " << dictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << dictionary.count() << "\n";
  std::cout << "Количество коллизий в словаре: " << dictionary.collisions() << "\n";
  std::cout << "Создадим словарь размера 46933 и прочитаем в него наш файл\n";
  FrequencyDictionary bigDictionary(46933);
  bigDictionary.readFile("sampleInput.txt");
  std::cout << "Размер словаря: " << bigDictionary.size() << "\n";
  std::cout << "Количество элементов в словаре: " << bigDictionary.count() << "\n";
  std::cout << "Количество коллизий в словаре: " << bigDictionary.collisions() << "\n";
  std::cout << "-------------------------------------------------------\n";
  std::cout << "------------------------------------------------------------------------------------------------------\n";
}
