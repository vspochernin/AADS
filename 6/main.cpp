#include <iostream>
#include <vector>
#include "algorithms.hpp"

// Определения типа указателя на сортирующую функцию.
typedef void (*SortFunctionPointer) (std::vector<int>&);

int main()
{
  SortFunctionPointer insertionBinarySortPointer = &insertionBinarySort;
  SortFunctionPointer radixSortPointer = &radixSort;
  SortFunctionPointer mergeIterativeSortPointer = &mergeIterativeSort;

  // Если к тестирующей функции добавить параметр true - включится отрисовка в консоль.
  std::cout << "Сортировка вставками с двоичным поиском-------------------------------------------------------------\n";
  testSort(insertionBinarySortPointer);
  std::cout << "\n";

  std::cout << "Поразрядная сортировка------------------------------------------------------------------------------\n";
  testSort(radixSortPointer);
  std::cout << "\n";

  std::cout << "Итеративная сортировка слиянием---------------------------------------------------------------------------------\n";
  testSort(mergeIterativeSortPointer);

  std::cout << "\nТестирование временной сложности сортировок-------------------------------------------------------------------\n";
  testSortComplex();
}
