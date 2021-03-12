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
// При этом надо помнить, что если искомых элементов несколько, надо будет выбрать позицию за ними.
// Этого буду добиваться уже в алгоритме сортировки.
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
