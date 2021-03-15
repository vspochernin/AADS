#include <iostream>
#include <vector>

#include "algorithms.hpp"

int main()
{
  std::vector<int> insertionVec;
  std::vector<int> radixVec;
  fillVector(insertionVec, 10000, -1000, 1000);
  fillVector(radixVec, 10000, -1000, 1000);
  //printVector(insertionVec, std::cout);
  //printVector(radixVec, std::cout);
  insertionBinarySort(insertionVec);
  radixSort(radixVec);
  std::cout << (isVectorSorted(insertionVec) ? "Вектор отсортирован вставками.\n" : "Вектор !!!НЕ!!! отсортирован вставками.\n");
  std::cout << (isVectorSorted(radixVec) ? "Вектор отсортирован поразрядно.\n" : "Вектор !!!НЕ!!! отсортирован поразрадно.\n");
  //printVector(insertionVec, std::cout);
  //printVector(radixVec, std::cout);
}
