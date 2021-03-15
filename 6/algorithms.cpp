#include "algorithms.hpp"

#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <vector>
#include <iostream>
#include <iomanip> // Красивый вывод.

void fillVector(std::vector<int>& vec, const size_t count, const int min, const int max)
{
  vec.clear();
  srand(time(0));
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
    out << std::setw(4) << vec[i] << " ";
    // Переводим строчки через каждые 10 элементов для красивого вывода.
    // Если строка последняя - её переводить не надо.
    if ((((i + 1) % 10) == 0) && ((i + 1) != vec.size()))
    {
      out << "\n";
    }
  }
  out << "\n--------------------------------------------------\n";
}

// Проверка, отсортирован ли вектор по неубыванию.
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

// Бинарный поиск места вставки элемента для сортировки вставками.
// left - индекс крайнего левого элемента.
// right - индекс крайнего правого элемента.
size_t binarySearchPlace(const std::vector<int>& vec, int element, size_t left, size_t right)
{
  while (left < right)
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
}

void insertionBinarySort(std::vector<int>& vec)
{
  for (size_t i = 1; i < vec.size(); i++) // Цикл по всем неотсортированным элементам.
  {
    if (vec[i] >= vec[i-1]) // Если элемент уже на своем месте...
    {
      continue; // ...ничего не делаем.
    }
    int insertValue = vec[i];
    size_t mostLeftIndex = binarySearchPlace(vec, vec[i], 0, i - 1); // Индекс самого левого элемента, который нужно передвинуть.
    for (size_t j = i; j > mostLeftIndex; j--)
    {
      vec[j] = vec[j - 1];
    }
    vec[mostLeftIndex] = insertValue;
  }
}

int power10(int power)
{
  int result = 1;
  for (int i = 0; i < power; i++)
  {
    result *= 10;
  }
  return result;
}

int getDigit(int number, int digit)
{
  int absNumber = std::abs(number);
  return (absNumber % power10(digit)) / power10(digit - 1);
}

int getTheLongestNumberLength(const std::vector<int>& vec)
{
  if (vec.size() == 0)
  {
    return 0;
  }
  else
  {
    int maxAbs = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
      maxAbs = std::max(maxAbs, std::abs(vec[i])); // Находим большое длинное по модулю число.
    }
    int result = 0;
    while (maxAbs != 0)
    {
      result++;
      maxAbs /= 10;
    }
    return result;
  }
}

void radixSort(std::vector<int>& vec)
{
  int startOfPositive = 0; // Индекс, на котором начинаются положительные числа.
  for (int i = 0; i < vec.size(); i++) // Делаем так, чтобы сначала в векторе шли отрицательные числа.
  {
    if (vec[i] < 0)
    {
      std::swap(vec[i], vec[startOfPositive]);
      startOfPositive++;
    }
  }

  // Находим "длинну" самого длинного числа.
  int longestLength = getTheLongestNumberLength(vec);
  std::vector<int> digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Вектор для сортировки подсчетом каждого разряда.
  std::vector<int> secondVec = vec; // Второй вектор для сортировки подсчетом каждого разряда.
  // Сортировка отрицательных чисел по убыванию их модулей (т.е. по возрастанию самих чисел).
  for (int sortingDigit = 1; sortingDigit <= longestLength; sortingDigit++)
  {
    digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
      secondVec[digitVec[getDigit(vec[i], sortingDigit)] - 1] = vec[i];
      digitVec[getDigit(vec[i], sortingDigit)]--;
    }
    for (int i = 0; i < startOfPositive; i++) // Переносим результат в основной вектор.
    {
      vec[i] = secondVec[i];
    }
  }
  // Сортировка положительных чисел по возрастанию.
  for (int sortingDigit = 1; sortingDigit <= longestLength; sortingDigit++)
  {
    digitVec = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (size_t i = startOfPositive; i < vec.size(); i ++)
    {
      digitVec[getDigit(vec[i], sortingDigit)]++;
    }
    for (int i = 1; i <= 9; i++)
    {
      digitVec[i] += digitVec[i - 1];
    }
    for (int i = vec.size() - 1; i >= startOfPositive; i--)
    {
      secondVec[digitVec[getDigit(vec[i], sortingDigit)] - 1 + startOfPositive] = vec[i];
      digitVec[getDigit(vec[i], sortingDigit)]--;
    }
    for (int i = startOfPositive; i < vec.size(); i++)
    {
      vec[i] = secondVec[i];
    }
  }
}
