#include <iostream>
#include <vector>

#include "algorithms.hpp"

int main()
{
  std::vector<int> testVec;
  fillVector(testVec, 1000, -100, 100);
  printVector(testVec, std::cout);
  insertionBinarySort(testVec);
  printVector(testVec, std::cout);
  std::cout << (isVectorSorted(testVec) ? "Да\n" : "Нет\n");
}
