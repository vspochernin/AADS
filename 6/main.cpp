#include <iostream>
#include <vector>

#include "algorithms.hpp"

int main()
{
  std::vector<int> insertionVec;
  std::vector<int> radixVec;
  std::vector<int> mergeVec;
  fillVector(insertionVec, 10000, -1000, 1000);
  fillVector(radixVec, 10000, -1000, 1000);
  fillVector(mergeVec, 10, -1000, 1000);
  //printVector(insertionVec, std::cout);
  //printVector(radixVec, std::cout);
  insertionBinarySort(insertionVec);
  radixSort(radixVec);
  mergeIterativeSort(mergeVec);
  std::cout << (isVectorSorted(insertionVec) ? "Вектор отсортирован вставками.\n" : "Вектор !!!НЕ!!! отсортирован вставками.\n");
  std::cout << (isVectorSorted(radixVec) ? "Вектор отсортирован поразрядно.\n" : "Вектор !!!НЕ!!! отсортирован поразрадно.\n");
  std::cout << (isVectorSorted(mergeVec) ? "Вектор отсортирован слиянием.\n" : "Вектор !!!НЕ!!! отсортирован слиянием.\n");
  //printVector(insertionVec, std::cout);
  //printVector(radixVec, std::cout);
  printVector(mergeVec, std::cout);
}
