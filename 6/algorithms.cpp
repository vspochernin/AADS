#include "algorithms.hpp"

#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <vector>
#include <iostream>
#include <iomanip> // Красивый вывод.

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
