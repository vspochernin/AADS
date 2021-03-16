#include <iostream>
#include <vector>

#include "algorithms.hpp"

// Определения типа указателя на сортирующую функцию.
typedef void (*SortFunctionPointer) (std::vector<int>&);

// Функция тестирования сортировки вектора, указатель на функцию подается в качестве параметра.
void testSort(SortFunctionPointer sortFunction, bool isPrint = false);

int main()
{
  SortFunctionPointer insertionBinarySortPointer = &insertionBinarySort;
  SortFunctionPointer radixSortPointer = &radixSort;
  SortFunctionPointer mergeIterativeSortPointer = &mergeIterativeSort;

  std::cout << "Сортировка вставками с двоичным поиском-------------------------------------------------------------\n";
  testSort(insertionBinarySortPointer);
  std::cout << "\n";

  std::cout << "Поразрядная сортировка------------------------------------------------------------------------------\n";
  testSort(radixSortPointer);
  std::cout << "\n";

  std::cout << "Итеративная сортировка слиянием---------------------------------------------------------------------------------\n";
  testSort(mergeIterativeSortPointer);
}

void testSort(SortFunctionPointer sortFunction, bool isPrint)
{
  bool check = true; // Переменная, которая покажет, нормально ли прошли тесты.
  std::vector<int> testVec1; // Пустой вектор.
  std::vector<int> testVec2; // Случайный вектор с переменным размером.
  std::vector<int> testVec3; // Случайный вектор большого размера.
  std::vector<int> testVec4; // Лучший случай.
  std::vector<int> testVec5; // Худший случай.

  // Тест 1: пустой вектор.
  testVec1.clear();
  if(isPrint)
  {
    std::cout << "Тест 1: пустой вектор-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec1, std::cout);
  }
  sortFunction(testVec1);
  if (!isVectorSorted(testVec1))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec1, std::cout);
  }

  // Тест 2: случайный вектор с переменным размером.
  if(isPrint)
  {
    std::cout << "Тест 2: случайный вектор с переменным размером------------------------------------\n";
  }
  for (size_t count = 1; count <= 100; count++)
  {
    fillVector(testVec2, count, -100, 100);
    if (isPrint)
    {
      std::cout << "Размер " << count << ", до сортировки:\n";
      printVector(testVec2, std::cout);
    }
    sortFunction(testVec2);
    if (!isVectorSorted(testVec2))
    {
      check = false;
      if (isPrint)
      {
        std::cout << "!!!ОШИБКА!!!\n";
      }
    }
    if (isPrint)
    {
      std::cout << "После сортировки:\n";
      printVector(testVec2, std::cout);
    }
  }

  // Тест 3: случайный вектор большого размера.
  fillVector(testVec3, 10000, -1000, 1000);
  if(isPrint)
  {
    std::cout << "Тест 3: случайный вектор большого размера-----------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec3, std::cout);
  }
  sortFunction(testVec3);
  if (!isVectorSorted(testVec3))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec3, std::cout);
  }

  // Тест 4: лучший случай.
  for (int i = -100; i <= 100; i++)
  {
    testVec4.push_back(i);
  }
  if(isPrint)
  {
    std::cout << "Тест 4: лучший случай-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec4, std::cout);
  }
  sortFunction(testVec4);
  if (!isVectorSorted(testVec4))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec4, std::cout);
  }

  // Тест 5: худший случай.
  for (int i = 100; i >= -100; i--)
  {
    testVec5.push_back(i);
  }
  if(isPrint)
  {
    std::cout << "Тест 4: худший случай-------------------------------------------------------------\n";
    std::cout << "До сортировки:\n";
    printVector(testVec5, std::cout);
  }
  sortFunction(testVec5);
  if (!isVectorSorted(testVec5))
  {
    check = false;
    if (isPrint)
    {
      std::cout << "!!!ОШИБКА!!!\n";
    }
  }
  if (isPrint)
  {
    std::cout << "После сортировки:\n";
    printVector(testVec5, std::cout);
  }

  if (check)
  {
    std::cout << "Тестирование прошло кореектно, все векторы были успешно отсортированы.\n";
  }
  else
  {
    std::cout << "Тестирование прошло !!!НЕ!!! корректно, где-то была !!!ОШИБКА!!!.\n";
  }
}
