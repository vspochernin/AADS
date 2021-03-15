#include <iostream>
#include <vector>

#include "algorithms.hpp"

int main()
{
  std::vector<int> testVec = {-139, -172};
  //std::vector<int> testVec;
  fillVector(testVec, 10000, -1000, 1000);
  printVector(testVec, std::cout);
  std::cout << "Start sorting\n";
  //insertionBinarySort(testVec);
  radixSort(testVec);
  printVector(testVec, std::cout);
  std::cout << "End sorting\n";
  std::cout << (isVectorSorted(testVec) ? "Да\n" : "Нет\n");
}
