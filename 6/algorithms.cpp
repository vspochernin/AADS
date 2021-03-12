#include "algorithms.hpp"

#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <vector>
#include <iostream>
#include <iomanip> // Красивый вывод.

void fillVector(std::vector<int>& vec, const size_t count)
{
  vec.clear();
  srand(time(0));
  for (size_t i = 0; i < count; i++)
  {
    vec.push_back(rand() % (100 - (-100) + 1) + (-100)); // Случайные числа из отрезка [-100; 100].
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
  size_t mid = (left + right) / 2; // Вычисляем номер элемента по середине. При четном количестве, элемент будет левее середины.
  int midValue = vec[mid];
  if (midValue == element) // Если элемент по середине равен искомому...
  {
    return mid; // ... возвращаем его номер.
  }
  if (left == right) // Если элемент по середине не прошел проверку на равенство искомому, при это он остался один...
  {
    return mid; // ... все равно возвращаем его номер. (Если бы искали наличие элемента, а не место, куда поставить, вернули бы -1)
  }
  if (midValue > element) // Если элемент по середине оказался больше искомого...
  {
    return binarySearchPlace(vec, element, left, mid); // ... запускаем бинарный поиск на отрезке [left; mid].
  }
  if (midValue < element) // Если элемент по сеедине оказался меньше искомого...
  {
    return binarySearchPlace(vec, element, mid + 1, right); // ... Запускаем бинарный поиск на отрезке [mid + 1, right].
  }
}
