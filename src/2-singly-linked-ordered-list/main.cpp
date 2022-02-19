#include <iostream>

#include "SinglyLinkedOrderedList.hpp"

int main()
{
  std::cout << "Test 1: default constructor." << std::endl;
  SinglyLinkedOrderedList<int> list1;
  list1.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 2: insert and outAll." << std::endl;
  list1.insert(3);
  list1.insert(2);
  list1.insert(1);
  list1.insert(4);
  list1.insert(3);
  list1.insert(32);
  list1.insert(0); // В начало.
  list1.insert(100); // В конец.
  list1.insert(5); // В середину.
  list1.insert(5); // Такой же.
  list1.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 3: searchItem." << std::endl;
  std::cout << "Is 0 here? " << (list1.searchItem(0) ? "YES" : "NO") << std::endl;
  std::cout << "Is 4 here? " << (list1.searchItem(4) ? "YES" : "NO") << std::endl;
  std::cout << "Is 100 here? " << (list1.searchItem(100) ? "YES" : "NO") << std::endl;
  std::cout << "Is 200 here? " << (list1.searchItem(200) ? "YES" : "NO") << std::endl;
  std::cout << "Is -100 here? " << (list1.searchItem(-100) ? "YES" : "NO") << std::endl;
  std::cout << "Is 6 here? " << (list1.searchItem(6) ? "YES" : "NO") << std::endl;
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 4: deleteItem." << std::endl;
  list1.outAll();
  list1.deleteItem(0);
  list1.outAll();
  list1.deleteItem(100);
  list1.outAll();
  list1.deleteItem(4);
  list1.outAll();
  list1.deleteItem(-100);
  list1.deleteItem(4);
  list1.deleteItem(200);
  list1.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 5: unionOfSets." << std::endl;
  list1.deleteItem(2);
  list1.deleteItem(3);
  list1.insert(-3);
  list1.insert(100);
  list1.insert(4);
  list1.insert(34);
  SinglyLinkedOrderedList<int> list2;
  list2.insert(-2);
  list2.insert(-1);
  list2.insert(0);
  list2.insert(2);
  list2.insert(3);
  list2.insert(4);
  list2.insert(6);
  list2.insert(7);
  list2.insert(8);
  list2.insert(9);
  list2.insert(10);
  list2.insert(33);
  list2.insert(34);
  list1.outAll();
  list2.outAll();
  list1.unionOfSets(list2);
  list1.outAll();
  list2.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 5.5 smartUnionOfSets." << std::endl;
  list2.insert(-2);
  list2.insert(-1);
  list2.insert(0);
  list2.insert(2);
  list2.insert(3);
  list2.insert(4);
  list2.insert(6);
  list2.insert(7);
  list2.insert(8);
  list2.insert(9);
  list2.insert(10);
  list2.insert(33);
  list2.insert(34);
  list1.clear();
  list1.insert(-3);
  list1.insert(1);
  list1.insert(4);
  list1.insert(5);
  list1.insert(32);
  list1.insert(34);
  list1.insert(100);
  list1.outAll();
  list2.outAll();
  list1.smartUnionOfSets(list2);
  list1.outAll();
  list2.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 6: substractionOfSets." << std::endl;
  list2.insert(3);
  list2.insert(4);
  list2.insert(5);
  list2.insert(6);
  list2.insert(-2);
  list2.insert(-1);
  list2.insert(33);
  list2.insert(34);
  list2.insert(35);
  list2.insert(-20);
  list2.insert(11);
  list1.outAll();
  list2.outAll();
  list1.substractionOfSets(list2);
  list1.outAll();
  list2.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 7: intersectionOfSets." << std::endl;
  list1.clear();
  list1.insert(1);
  list1.insert(2);
  list1.insert(3);
  list1.insert(4);
  list1.insert(-20);
  list1.insert(34);
  list1.insert(35);
  list1.outAll();
  list2.outAll();
  SinglyLinkedOrderedList<int> list3 = intersectionOfSets(list1, list2);
  list3.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 8 smartUnionOfSets again." << std::endl;
  SinglyLinkedOrderedList<int> list4;
  SinglyLinkedOrderedList<int> list5;
  list4.insert(1);
  list4.insert(3);
  list4.insert(5);
  list4.insert(7);
  list4.insert(9);
  list4.insert(11);
  list5.insert(2);
  list5.insert(4);
  list5.insert(6);
  list5.insert(8);
  list5.insert(10);
  list5.insert(12);
  list4.outAll();
  list5.outAll();
  list4.smartUnionOfSets(list5);
  list4.outAll();
  list5.outAll();
  std::cout << "----------------------------------" << std::endl;

  std::cout << "Test 9 smartUnionOfSets again." << std::endl;
  SinglyLinkedOrderedList<int> list6;
  SinglyLinkedOrderedList<int> list7;
  list6.insert(1);
  list6.insert(2);
  list6.insert(3);
  list6.insert(4);
  list6.insert(11);
  list6.insert(12);
  list6.insert(13);
  list6.insert(14);
  list7.insert(5);
  list7.insert(6);
  list7.insert(7);
  list7.insert(8);
  list7.insert(111);
  list7.insert(222);
  list7.insert(333);
  list7.insert(444);
  list6.outAll();
  list7.outAll();
  list6.smartUnionOfSets(list7);
  list6.outAll();
  list7.outAll();
  std::cout << "----------------------------------" << std::endl;

  return 0;
}