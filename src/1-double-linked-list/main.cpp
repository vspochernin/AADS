//
// Тестовая функция:   проверка методов работы со списком 
//
#include "DoubleLinkedList.h"
#include <iostream>

int main()
{
  DoubleLinkedList list1;

  std::cout << "Test 1: " << std::endl;
  list1.insertTail(123);
  list1.insertTail(1234);
  list1.insertTail(1235);
  list1.outAll();
  DoubleLinkedList list2 = list1;
  list2.outAll();
  list1.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 2: " << std::endl;
  list2.insertHead(333);
  list2.insertTail(444);
  list2.outAll();
  list1.outAll();
  list1 = list2;
  list2.outAll();
  list1.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 3: " << std::endl;
  DoubleLinkedList list3 = list1 + list2;
  list3.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 4: " << std::endl;
  DoubleLinkedList list4;
  list4.insertHead(432432);
  list4.insertHead(23);
  list4.outAll();
  list3.outAll();
  list1.outAll();
  list4 = list3 + list1;
  list4.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 5: " << std::endl;
  list1.outAll();
  list1.insertTail(1);
  list1.insertTail(2);
  list1.insertTail(3);
  list1.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 6, 9: " << std::endl;
  list4.outAll();
  list4.replaceItem(1234, 1111, true);
  list4.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 7: " << std::endl;
  list1.outAll();
  list1.deleteTail();
  list1.outAll();
  list1.deleteTail();
  list1.deleteTail();
  list1.deleteTail();
  list1.deleteTail();
  list1.deleteTail();
  list1.deleteTail();
  list1.outAll();
  list1.deleteTail();
  list1.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 8: " << std::endl;
  list4.outAll();
  list4.deleteItem(1111, true);
  list4.outAll();
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 10: " << std::endl;
  list4.outAll();
  std::cout << list4 << std::endl;
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 11: " << std::endl;
  list4.outAll();
  list3.outAll();
  std::cout << (list4 == list3) << std::endl;
  list4 = list3;
  list4.outAll();
  list3.outAll();
  std::cout << (list4 == list3) << std::endl;
  std::cout << "----------------------" << std::endl;

  std::cout << "Test 12: " << std::endl;
  list1.insertHead(1);
  list1.insertHead(2);
  list1.insertHead(3);
  list1.outAll();
  list2.outAll();
  list1.addArgument(list2);
  list1.outAll();
  list2.outAll();
  std::cout << "----------------------" << std::endl;


  return 0;
}