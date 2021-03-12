#include <iostream>
#include <vector>

#include "algorithms.hpp"

int main()
{
  std::vector<int> testVec;
  fillVector(testVec, 100);
  printVector(testVec, std::cout);
  std::cout << "Вектор отсортирован? " << (isVectorSorted(testVec) ? "Да!\n" : "Нет!\n");
}
