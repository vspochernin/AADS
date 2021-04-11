#include "algorithms.hpp"

#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <vector>
#include <iostream>
#include <iomanip> // Красивый вывод.
#include <chrono>
#include <math.h>

void fillVector(std::vector<int>& vec, const size_t count, const int min, const int max)
{
  vec.clear();
  srand(time(0)); // Рандомизация.
  for (size_t i = 0; i < count; i++)
  {
    vec.push_back(rand() % (max - min + 1) + min); // Случайные числа из отрезка [min; max].
  }
}

void printVector(const std::vector<int>& vec, std::ostream& out)
{
  out << "----------------------vector----------------------\n";
  for (size_t i = 0; i < vec.size(); i++)
  {
    out << std::setw(4) << vec[i] << " "; // std::setw, чтобы каждый элемент был друг под другом.
    // Переводим строчки через каждые 10 элементов для красивого вывода.
    // Если строка последняя - её переводить не надо.
    if ((((i + 1) % 10) == 0) && ((i + 1) != vec.size()))
    {
      out << "\n";
    }
  }
  out << "\n--------------------------------------------------\n";
}

bool isVectorSorted(const std::vector<int>& vec)
{
  for (size_t i = 1; i < vec.size(); i++)
  {
    if (vec[i - 1] > vec[i])
    {
      return false;
    }
  }
  return true;
}

// Бинарный поиск самого левого элемента, который надо передвинуть.
// left - индекс крайнего левого элемента.
// right - индекс крайнего правого элемента.
size_t binarySearchPlace(const std::vector<int>& vec, const int element, size_t left, size_t right)
{
  while (left < right) // Ищем, пока отрезок поиска не сократится до одного элемента.
  {
    size_t mid = (left + right) / 2; // Вычисляем номер элемента по середине. При четном количестве, элемент будет левее середины.
    if (element < vec[mid]) // Если искомый элемент меньше элемента по середине...
    {
      right = mid; // ...будем смотреть отрезок [left; mid].
    }
    else // Иначе...
    {
      left = mid + 1; // ...будем смотреть отрезок [mid + 1; right].
    }
  }
  return left; // Получим индекс самого левого элемента, который нужно передвинуть.
  // И этот индекс будет "самым правым самым левым" элементом, который надо передвинуть.
  // Т.е., сортировка будет устойчивой, так как передвигаться будут элементы максимально правые.
}

void insertionBinarySort(std::vector<int>& vec)
{
  for (size_t i = 1; i < vec.size(); i++) // Цикл по всем неотсортированным элементам.
  {
    if (vec[i] >= vec[i-1]) // Если элемент уже на своем месте...
    {
      continue; // ...ничего не делаем.
    }
    int insertValue = vec[i]; // Запоминаем вставляемый элемент.
    size_t mostLeftIndex = binarySearchPlace(vec, vec[i], 0, i - 1); // Ищем индекс самого левого элемента, который нужно передвинуть.
    for (size_t j = i; j > mostLeftIndex; j--) // Сдвигаем элементы.
    {
      vec[j] = vec[j - 1];
    }
    vec[mostLeftIndex] = insertValue; // Ставим вставляемый элемент на свое место.
  }
}

int power10(const int power)
{
  int result = 1;
  for (int i = 0; i < power; i++)
  {
    result *= 10;
  }
  return result;
}

int getDigit(const int number, const int digit)
{
  int absNumber = std::abs(number); // Исключаем минус из вычислений.
  return (absNumber % power10(digit)) / power10(digit - 1);
}

int getTheLongestNumberLength(const std::vector<int>& vec)
{
  if (vec.empty())
  {
    return 0;
  }
  else
  {
    int maxAbs = std::abs(vec[0]); // Самое "длинное" по модулю число.
    for (size_t i = 1; i < vec.size(); i++)
    {
      maxAbs = std::max(maxAbs, std::abs(vec[i])); // Находим самое "длинное" по модулю число.
    }
    int result = 0;
    while (maxAbs != 0) // Находим "длинну" этого числа.
    {
      result++;
      maxAbs /= 10;
    }
    return result;
  }
}

void radixSort(std::vector<int>& vec)
{
  // Сортировку будем выполнять так:
  // Сначала разделим массив на положительные и отрицательные числа, поместив отрицательные в начало.
  // Затем отдельно отсортируем отрицательные числа по убыванию модулей, а положительные по возрастанию.

  // Итак, для начала поместим отрицательные числа в начала вектора и запомним, где начинаются положительные.
  int startOfPositive = 0; // Индекс, на котором начинаются положительные числа.
  for (int i = 0; i < static_cast<int>(vec.size()); i++) // Делаем так, чтобы сначала в векторе шли отрицательные числа.
  {
    if (vec[i] < 0)
    {
      std::swap(vec[i], vec[startOfPositive]); // Меняем местами встретившееся отрицательное число и первое положительное.
      startOfPositive++; // И увеличиваем счетчик.
    }
  }

  // Далее находим "длинну" самого длинного числа. Будем смотреть разряды до количества разрядов в нем.
  int longestLength = getTheLongestNumberLength(vec);

  // Создаем два вспомогательных вектора для сортировки каждого разряда.
  std::vector<int> digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Вектор, который покажет, на какое место вектора secondVec надо ставить число.
  std::vector<int> secondVec = vec; // Вспомогательный "буфер", куда мы сначала будем вставлять, а потом переносить его в основной вектор.

  // Сортировка отрицательных чисел по убыванию их модулей (т.е. по возрастанию самих чисел).
  for (int sortingDigit = 1; sortingDigit <= longestLength; sortingDigit++)
  {
    digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Обнуляем вспомогательный вектор перед каждой итерацией сортировки подсчетом.
    for (int i = 0; i < startOfPositive; i++) // Шаг (а) из презентации.
    {
      digitVec[getDigit(vec[i], sortingDigit)]++; // Заполняем вспомогательный вектор количеством вхождений чисел.
    }
    for (int i = 8; i >= 0; i--) // Шаг (b) из презентации.
    {
      digitVec[i] += digitVec[i + 1]; // Делаем так, чтобы вспомогательный вектор показывал, куда поставить число.
    }
    for (int i = startOfPositive - 1; i >= 0; i--) // Ставим числа на свои места.
    {
      secondVec[digitVec[getDigit(vec[i], sortingDigit)] - 1] = vec[i]; // Ставим сортируемое число на свое место в secondVec.
      digitVec[getDigit(vec[i], sortingDigit)]--; // Уменьшаем значение индекса, куда соответствующее число поставить.
    }
    for (int i = 0; i < startOfPositive; i++) // Переносим результат в основной вектор.
    {
      vec[i] = secondVec[i];
    }
  }

  // Сортировка положительных чисел по возрастанию.
  for (int sortingDigit = 1; sortingDigit <= longestLength; sortingDigit++)
  {
    digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Обнуляем вспомогательный вектор перед каждой итерацией сортировки подсчетом.
    for (size_t i = startOfPositive; i < vec.size(); i ++) // Шаг (а) из презентации.
    {
      digitVec[getDigit(vec[i], sortingDigit)]++; // Заполняем вспомогательный вектор количеством вхождений чисел.
    }
    for (int i = 1; i <= 9; i++) // Шаг (b) из презентации.
    {
      digitVec[i] += digitVec[i - 1]; // Делаем так, чтобы вспомогательный вектор показывал, куда поставить число.
    }
    for (int i = static_cast<int>(vec.size()) - 1; i >= startOfPositive; i--) // Ставим числа на свои места.
    {
      secondVec[digitVec[getDigit(vec[i], sortingDigit)] - 1 + startOfPositive] = vec[i]; // Ставим сортируемое число на свое место в secondVec.
      digitVec[getDigit(vec[i], sortingDigit)]--; // Уменьшаем значение индекса, куда соответствующее число поставить.
    }
    for (int i = startOfPositive; i < static_cast<int>(vec.size()); i++) // Переносим результат в основной вектор.
    {
      vec[i] = secondVec[i];
    }
  }
}

void mergeVector(std::vector<int>& vec, size_t left, size_t middle, size_t right)
{
  std::vector<int> leftVec; // Вспомогательный вектор, хранящий элементы из левого отрезка.
  std::vector<int> rightVec; // Вспомогательный вектор, хранящий элементы из правого отрезка.
  // И соответственно заполняем их.
  for (size_t i = left; i <= middle; i++)
  {
    leftVec.push_back(vec[i]);
  }
  for (size_t i = middle + 1; i <= right; i++)
  {
    rightVec.push_back(vec[i]);
  }

  size_t leftIndex = 0; // Переменная-указатель на левый вектор.
  size_t rightIndex = 0; // Переменная-указатель на правый вектор.
  size_t mainIndex = left; // Переменная-указатель на основной вектор.
  while ((leftIndex < leftVec.size()) && (rightIndex < rightVec.size())) // Пока мы не исчерпаем один из векторов...
  {
    // ...записываем в основной вектор элементы во возрастанию.
    if (leftVec[leftIndex] <= rightVec[rightIndex])
    {
      vec[mainIndex] = leftVec[leftIndex];
      leftIndex++; // Увеличиваем указатель на левый вектор (если добавили оттуда).
    }
    else
    {
      vec[mainIndex] = rightVec[rightIndex];
      rightIndex++; // Увеличиваем указатель на правый вектор (если добавили оттуда).
    }
    mainIndex++; // Соответственно, увеличиваем указатель на основной вектор.
  }

  // Добавляем в основной вектор оставшиеся элементы из левого (если таковые остались).
  while (leftIndex < leftVec.size())
  {
    vec[mainIndex] = leftVec[leftIndex];
    leftIndex++;
    mainIndex++;
  }

  // Добавляем в основной вектор оставшиеся элементы из правого (если таковые остались).
  while (rightIndex < rightVec.size())
  {
    vec[mainIndex] = rightVec[rightIndex];
    rightIndex++;
    mainIndex++;
  }
}

void mergeIterativeSort(std::vector<int>& vec)
{
  // Будем сливать подвектора размерами от 1 элемента,
  // увеличивая размер в 2 раза за каждую итерацию.

  // Цикл по размерам сливаемых векторов.
  for (size_t sizeOfMergeVec = 1; sizeOfMergeVec < vec.size(); sizeOfMergeVec *= 2)
  {
    // Цикл по left-индексам в этих векторах.
    for (size_t left = 0; left < vec.size() - 1; left += 2 * sizeOfMergeVec)
    {
      // Определяем middle-индекс (если он выходит за пределы вектора - делаем его последним элементом)
      size_t middle = std::min(left + sizeOfMergeVec - 1, vec.size() - 1);
      // Определяем right-индекс (если он выходит за пределы вектора - делаем его последним элементом)
      size_t right = std::min(left + (2 * sizeOfMergeVec) - 1, vec.size() - 1);
      // Сливаем подвектора.
      mergeVector(vec, left, middle, right);
    }
  }
}

void testSort(SortFunctionPointer sortFunction, bool isPrint)
{
  bool check = true; // Переменная, которая покажет, нормально ли прошли тесты.
  std::vector<int> testVec1; // Пустой вектор.
  std::vector<int> testVec2; // Случайный вектор с переменным размером.
  std::vector<int> testVec3; // Случайный вектор большого размера.
  std::vector<int> testVec4; // Лучший случай.
  std::vector<int> testVec5; // Худший случай.

  // Тест 1: пустой вектор.
  testVec1.clear();
  if(isPrint)
  {
    std::cout << "Тест 1: пустой вектор-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec1, std::cout);
  }
  sortFunction(testVec1);
  if (!isVectorSorted(testVec1))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec1, std::cout);
  }

  // Тест 2: случайный вектор с переменным размером.
  if(isPrint)
  {
    std::cout << "Тест 2: случайный вектор с переменным размером------------------------------------\n";
  }
  for (size_t count = 1; count <= 100; count++)
  {
    fillVector(testVec2, count, -100, 100);
    if (isPrint)
    {
      std::cout << "Размер " << count << ", до сортировки:\n";
      printVector(testVec2, std::cout);
    }
    sortFunction(testVec2);
    if (!isVectorSorted(testVec2))
    {
      check = false;
      if (isPrint)
      {
        std::cout << "!!!ОШИБКА!!!\n";
      }
    }
    if (isPrint)
    {
      std::cout << "После сортировки:\n";
      printVector(testVec2, std::cout);
    }
  }

  // Тест 3: случайный вектор большого размера.
  fillVector(testVec3, 10000, -1000, 1000);
  if(isPrint)
  {
    std::cout << "Тест 3: случайный вектор большого размера-----------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec3, std::cout);
  }
  sortFunction(testVec3);
  if (!isVectorSorted(testVec3))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec3, std::cout);
  }

  // Тест 4: лучший случай.
  for (int i = -100; i <= 100; i++)
  {
    testVec4.push_back(i);
  }
  if(isPrint)
  {
    std::cout << "Тест 4: лучший случай-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec4, std::cout);
  }
  sortFunction(testVec4);
  if (!isVectorSorted(testVec4))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec4, std::cout);
  }

  // Тест 5: худший случай.
  for (int i = 100; i >= -100; i--)
  {
    testVec5.push_back(i);
  }
  if(isPrint)
  {
    std::cout << "Тест 4: худший случай-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec5, std::cout);
  }
  sortFunction(testVec5);
  if (!isVectorSorted(testVec5))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec5, std::cout);
  }

  if (check)
  {
    std::cout << "Тестирование прошло кореектно, все векторы были успешно отсортированы.\n";
  }
  else
  {
    std::cout << "Тестирование прошло !!!НЕ!!! корректно, где-то была !!!ОШИБКА!!!.\n";
  }
}

void testSortComplex()
{
  std::cout << "Тестирование сортировки вставками. Предполагаемая сложность: O(n^2).*************\n";
  size_t n1 = 1000;
  size_t n2 = 10000;
  size_t n3 = 100000;
  std::vector<int> testVec1;
  std::vector<int> testVec2;
  std::vector<int> testVec3;
  fillVector(testVec1, n1, -10000, 10000);
  fillVector(testVec2, n2, -10000, 10000);
  fillVector(testVec3, n3, -10000, 10000);
  std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
  insertionBinarySort(testVec1);
  std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
  insertionBinarySort(testVec2);
  std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point begin3 = std::chrono::steady_clock::now();
  insertionBinarySort(testVec3);
  std::chrono::steady_clock::time_point end3 = std::chrono::steady_clock::now();
  std::cout << "Количество элементов 1: " << n1 << ".\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::seconds>(end1 - begin1).count() << " секунд.\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " микросекунд.\n";
  std::cout << "Количество элементов 2: " << n2 << ".\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2).count() << " секунд.\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " микросекунд.\n";
  std::cout << "Количество элементов 3: " << n3 << ".\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::seconds>(end3 - begin3).count() << " секунд.\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " микросекунд.\n";
  std::cout << "Ожидаемая разница во времени между 1 и 2 сортировкой: " << (n2/n1)*(n2/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 2 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";
  std::cout << "Ожидаемая разница во времени между 2 и 3 сортировкой: " << (n3/n2)*(n3/n2) << ".\n";
  std::cout << "Реальная разница во времени между 2 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) << ".\n";
  std::cout << "Ожидаемая разница во времени между 1 и 3 сортировкой: " << (n3/n1)*(n3/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";

  std::cout << "Тестирование сортировки слиянием. Предполагаемая сложность: O(nlog(n)).*************\n";
  n1 = 10000;
  n2 = 100000;
  n3 = 1000000;
  fillVector(testVec1, n1, -10000, 10000);
  fillVector(testVec2, n2, -10000, 10000);
  fillVector(testVec3, n3, -10000, 10000);
  begin1 = std::chrono::steady_clock::now();
  mergeIterativeSort(testVec1);
  end1 = std::chrono::steady_clock::now();
  begin2 = std::chrono::steady_clock::now();
  mergeIterativeSort(testVec2);
  end2 = std::chrono::steady_clock::now();
  begin3 = std::chrono::steady_clock::now();
  mergeIterativeSort(testVec3);
  end3 = std::chrono::steady_clock::now();
  std::cout << "Количество элементов 1: " << n1 << ".\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::seconds>(end1 - begin1).count() << " секунд.\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " микросекунд.\n";
  std::cout << "Количество элементов 2: " << n2 << ".\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2).count() << " секунд.\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " микросекунд.\n";
  std::cout << "Количество элементов 3: " << n3 << ".\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::seconds>(end3 - begin3).count() << " секунд.\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " микросекунд.\n";
  std::cout << "Ожидаемая разница во времени между 1 и 2 сортировкой: " << (n2/n1)*log10(n2/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 2 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";
  std::cout << "Ожидаемая разница во времени между 2 и 3 сортировкой: " << (n3/n2)*log10(n3/n2) << ".\n";
  std::cout << "Реальная разница во времени между 2 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) << ".\n";
  std::cout << "Ожидаемая разница во времени между 1 и 3 сортировкой: " << (n3/n1)*log10(n3/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";

  std::cout << "Тестирование Поразрядной сортировки. Предполагаемая сложность: O(n).*************\n";
  n1 = 100000;
  n2 = 1000000;
  n3 = 10000000;
  fillVector(testVec1, n1, -10000, 10000);
  fillVector(testVec2, n2, -10000, 10000);
  fillVector(testVec3, n3, -10000, 10000);
  begin1 = std::chrono::steady_clock::now();
  radixSort(testVec1);
  end1 = std::chrono::steady_clock::now();
  begin2 = std::chrono::steady_clock::now();
  radixSort(testVec2);
  end2 = std::chrono::steady_clock::now();
  begin3 = std::chrono::steady_clock::now();
  radixSort(testVec3);
  end3 = std::chrono::steady_clock::now();
  std::cout << "Количество элементов 1: " << n1 << ".\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::seconds>(end1 - begin1).count() << " секунд.\n";
  std::cout << "Время сортировки 1: " << std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1).count() << " микросекунд.\n";
  std::cout << "Количество элементов 2: " << n2 << ".\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::seconds>(end2 - begin2).count() << " секунд.\n";
  std::cout << "Время сортировки 2: " << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2).count() << " микросекунд.\n";
  std::cout << "Количество элементов 3: " << n3 << ".\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::seconds>(end3 - begin3).count() << " секунд.\n";
  std::cout << "Время сортировки 3: " << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3).count() << " микросекунд.\n";
  std::cout << "Ожидаемая разница во времени между 1 и 2 сортировкой: " << (n2/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 2 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";
  std::cout << "Ожидаемая разница во времени между 2 и 3 сортировкой: " << (n3/n2) << ".\n";
  std::cout << "Реальная разница во времени между 2 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end2 - begin2) << ".\n";
  std::cout << "Ожидаемая разница во времени между 1 и 3 сортировкой: " << (n3/n1) << ".\n";
  std::cout << "Реальная разница во времени между 1 и 3 сортировкой: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end3 - begin3) / std::chrono::duration_cast<std::chrono::microseconds>(end1 - begin1) << ".\n";
}
