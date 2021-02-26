#include <iostream>

#include "BinarySearchTree.hpp"

int main()
{
  setlocale(LC_ALL, "Russian");

  std::cout << "\nТест 1: Функция поиска по ключу в бинарном дереве поиска\n";
  std::cout << "--------------------------------------------------------------\n";
  BinarySearchTree<int> tree1;
  tree1.insert(8);
  tree1.insert(3);
  tree1.insert(10);
  tree1.insert(6);
  tree1.insert(4);
  tree1.insert(7);
  tree1.insert(1);
  tree1.insert(14);
  tree1.insert(13);
  tree1.inorderWalk();
  std::cout << "Здесь есть 1? " << (tree1.iterativeSearch(1) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 2? " << (tree1.iterativeSearch(2) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 3? " << (tree1.iterativeSearch(3) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 4? " << (tree1.iterativeSearch(4) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 5? " << (tree1.iterativeSearch(5) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 6? " << (tree1.iterativeSearch(6) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 7? " << (tree1.iterativeSearch(7) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 8? " << (tree1.iterativeSearch(8) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 9? " << (tree1.iterativeSearch(9) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 10? " << (tree1.iterativeSearch(10) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 11? " << (tree1.iterativeSearch(11) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 12? " << (tree1.iterativeSearch(12) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 13? " << (tree1.iterativeSearch(13) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 14? " << (tree1.iterativeSearch(14) ? "Да." : "Нет.") << std::endl;
  std::cout << "Здесь есть 15? " << (tree1.iterativeSearch(15) ? "Да." : "Нет.") << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 2: Вставка нового элемента в дерево: true,если элемент добавлен; false, если элемент уже был.\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.inorderWalk();
  std::cout << "Пробуем добавить 1 2 3 4 5" << std::endl;
  std::cout << "Добавилась ли 1? " << (tree1.insert(1) ? "Да." : "Да.") << std::endl;
  std::cout << "Добавилась ли 2? " << (tree1.insert(2) ? "Да." : "Да.") << std::endl;
  std::cout << "Добавилась ли 3? " << (tree1.insert(3) ? "Да." : "Да.") << std::endl;
  std::cout << "Добавилась ли 4? " << (tree1.insert(4) ? "Да." : "Да.") << std::endl;
  std::cout << "Добавилась ли 5? " << (tree1.insert(5) ? "Да." : "Да.") << std::endl;
  tree1.inorderWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 3: Удаление элемента из дерева, не нарушающее порядка элементов.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Удаляем элементы от 0 до 15, в том числе несуществующие:\n";
  tree1.inorderWalk();

  for (int i = 0; i < 16; i++)
  {
    std::cout << "Удаляем " << i << ": ";
    tree1.deleteKey(i);
    tree1.inorderWalk();
  }
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 4: Печать строкового изображения дерева в выходной поток.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Сейчас дерево пустое: ";
  tree1.print(std::cout);
  std::cout << "Заполним его как в презентации: т.е. 8, 3, 10, 6, 4, 7, 1, 14, 13:\n";
  tree1.insert(8);
  tree1.insert(3);
  tree1.insert(10);
  tree1.insert(6);
  tree1.insert(4);
  tree1.insert(7);
  tree1.insert(1);
  tree1.insert(14);
  tree1.insert(13);
  std::cout << "Вывод заполненного дерева: ";
  tree1.print(std::cout);
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 5: Определение количества узлов дерева.\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.inorderWalk();
  std::cout << "Количество узлов: " << tree1.getCount() << std::endl;
  std::cout << "Создадим пустое дерево tree2\n";
  BinarySearchTree<int> tree2;
  std::cout << "Количество узлов: " << tree2.getCount() << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 6: Определение высоты дерева.\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.print(std::cout);
  std::cout << "Высота дерева: " << tree1.getHeight() << std::endl;
  std::cout << "Высота пустого дерева: " << tree2.getHeight() << std::endl;
  std::cout << "Создадим добавим в пустое дерево элемент 2\n";
  tree2.insert(2);
  tree2.print(std::cout);
  std::cout << "Высота дерева: " << tree2.getHeight() << std::endl;
  std::cout << "Создадим добавим в пустое дерево элементы 1 и 3\n";
  tree2.insert(1);
  tree2.insert(3);
  tree2.print(std::cout);
  std::cout << "Высота дерева: " << tree2.getHeight() << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 7: Инфиксный обход дерева (итеративный).\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.iterativeInorderWalk();
  tree2.iterativeInorderWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 8: Инфиксный обход дерева (рекурсивный).\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.inorderWalk();
  tree2.inorderWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 9: Сравнение деревьев: true, если все узлы деревьев одинаковые.\n";
  std::cout << "Вывод первого и второго деревьев: \n";
  tree1.inorderWalk();
  tree2.inorderWalk();
  std::cout << "Равны ли деревья: " << ((tree1 == tree2) ? "Да." : "Нет.") << std::endl;
  std::cout << "Добавим ко второму дереву элементы первого: \n";
  tree2.insert(1);
  tree2.insert(3);
  tree2.insert(4);
  tree2.insert(6);
  tree2.insert(7);
  tree2.insert(8);
  tree2.insert(10);
  tree2.insert(13);
  tree2.insert(14);
  std::cout << "Вывод первого и второго деревьев: \n";
  tree1.inorderWalk();
  tree2.inorderWalk();
  std::cout << "Равны ли деревья: " << ((tree1 == tree2) ? "Да." : "Нет.") << std::endl;
  std::cout << "Удалим из второго дерева лишнюю двойку: \n";
  tree2.deleteKey(2);
  std::cout << "Вывод первого и второго деревьев: \n";
  tree1.inorderWalk();
  tree2.inorderWalk();
  std::cout << "Равны ли деревья: " << ((tree1 == tree2) ? "Да." : "Нет.") << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  return 0;
}