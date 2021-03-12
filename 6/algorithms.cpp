#include "algorithms.hpp"

#include <time.h> // time
#include <stdlib.h> // srand, rand
#include <vector>
#include <iostream>
#include <iomanip> // Красивый вывод

void fillVector(std::vector<int>& vec, size_t count)
{
  vec.clear();
  srand(time(0));
  for (size_t i = 0; i < count; i++)
  {
    vec.push_back(rand() % (100 - (-100) + 1) + (-100));
  }
}

void printVector(const std::vector<int>& vec, std::ostream& out)
{
  out << "----------------------vector----------------------\n";
  for (size_t i = 0; i < vec.size(); i++)
  {
    out << std::setw(4) << vec[i] << " ";
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
      // TODO ДОДЕЛАТЬ И ПРОВЕРИТЬ ВЕСЬ КОД
    }
  }
}
