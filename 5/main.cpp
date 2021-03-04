#include <iostream>

#include <memory> // std::shared_ptr
#include "queue-array.hpp"
#include "binary-search-tree.hpp"

int main()
{
  setlocale(LC_ALL, "Russian");

  std::cout << "\nТест 1: создание кольцевой очереди и добавление элементов\n";
  std::cout << "--------------------------------------------------------------\n";
  std::shared_ptr<Queue<int>> queue1 = std::make_shared<QueueArray<int>>(5);
  queue1->enQueue(1);
  queue1->enQueue(2);
  queue1->enQueue(3);
  queue1->enQueue(4);
  queue1->enQueue(5);
  std::cout << "Мы добавили 5 элементов, заполнив всю очередь\n";
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 2: обработка переполнения очереди\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Попробуем добавить 6-й элемент:\n";
  try
  {
    queue1->enQueue(6);
  }
  catch (const QueueOverflow& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 3: исключение элементов\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Исключим из очереди все 5 элементов, выводя их:\n";
  for (size_t i = 0; i < 5; i++)
  {
    std::cout << queue1->deQueue() << " ";
  }
  std::cout << "\nЭлементы вывелись в том же порядке, в котором заносились в очередь\n";
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 4: обработка \"опустошения\"\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Очередь пуста? " << (queue1->isEmpty() ? "Да!" : "Нет!") << "\n";
  std::cout << "Попробуем достать элемент при пустой очереди:\n";
  try
  {
    queue1->deQueue();
  }
  catch (const QueueUnderflow& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 5: чередование добавления - исключения, переход через конец массива\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Будем добавлять и сразу же удалять числа:\n";
  for (size_t i = 1; i <= 30; i++)
  {
    queue1->enQueue(i);
    std::cout << queue1->deQueue() << " ";
    if ((i % 10) == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << "Очередь успела много раз перейти через 0 и она работает.\n";
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 6: тест переполнения при tail_ == size_ и head_ = 0\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Осталось проверить только этот случай.\n";
  std::cout << "Для этого искусственно создадим такую очередь:\n";
  std::shared_ptr<Queue<int>> queue2 = std::make_shared<QueueArray<int>>(3); // tail_ == head_ == 1.
  queue2->enQueue(1); // tail_ = 2;
  queue2->enQueue(1); // tail_ = 3;
  queue2->enQueue(1); // tail_ = 0;
  queue2->deQueue(); // head_ = 2;
  queue2->deQueue(); // head_ = 3;
  queue2->deQueue(); // head_ = 0;
  queue2->enQueue(1); // tail_ = 1;
  queue2->enQueue(1); // tail_ = 2;
  queue2->enQueue(1); // tail_ = 3;
  std::cout << "Итак, head_ == 0, tail_ == 3, size_ == 3. Попробуем записать еще одно число:\n";
  try
  {
    queue2->enQueue(1);
  }
  catch (const QueueOverflow& error)
  {
    std::cout << error.what() << "\n";
  }
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nПрелюдия к тестам деревьев.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Для тестов деревьев у нас будет несколько типов деревьев, которые мы будем использовать.\n";
  std::cout << "Я создам и заполню их здесь, я работать с ними буду уже в тестах\n";
  std::cout << "\n1-е дерево: как в презентации:\n";
  BinarySearchTree<int> tree1;
  tree1.insert(8);
  tree1.insert(3);
  tree1.insert(10);
  tree1.insert(6);
  tree1.insert(4);
  tree1.insert(7);
  tree1.insert(1);
  tree1.insert(14);
  tree1.print(std::cout);
  std::cout << "\n2-е дерево: как в презентации, но без элемента 14:\n";
  BinarySearchTree<int> tree2;
  tree2.insert(8);
  tree2.insert(3);
  tree2.insert(10);
  tree2.insert(6);
  tree2.insert(4);
  tree2.insert(7);
  tree2.insert(1);
  tree2.print(std::cout);
  std::cout << "\n3-е дерево: как в презентации, но без элемента 8:\n";
  BinarySearchTree<int> tree3;
  tree3.insert(3);
  tree3.insert(10);
  tree3.insert(6);
  tree3.insert(4);
  tree3.insert(7);
  tree3.insert(1);
  tree3.insert(14);
  tree3.print(std::cout);
  std::cout << "\n4-е дерево: как в презентации, но вырожденное:\n";
  BinarySearchTree<int> tree4;
  tree4.insert(1);
  tree4.insert(3);
  tree4.insert(4);
  tree4.insert(6);
  tree4.insert(7);
  tree4.insert(8);
  tree4.insert(10);
  tree4.insert(14);
  tree4.print(std::cout);
  std::cout << "\n5-е дерево: как в презентации, но вырожденное и без элемента 14:\n";
  BinarySearchTree<int> tree5;
  tree5.insert(1);
  tree5.insert(3);
  tree5.insert(4);
  tree5.insert(6);
  tree5.insert(7);
  tree5.insert(8);
  tree5.insert(10);
  tree5.print(std::cout);
  std::cout << "\n6-е дерево: как в презентации, но вырожденное и без элемента 8:\n";
  BinarySearchTree<int> tree6;
  tree6.insert(1);
  tree6.insert(3);
  tree6.insert(4);
  tree6.insert(6);
  tree6.insert(7);
  tree6.insert(10);
  tree6.insert(14);
  tree6.print(std::cout);
  std::cout << "\n7-е дерево: как в презентации, но вырожденное и без элемента 1:\n";
  BinarySearchTree<int> tree7;
  tree7.insert(3);
  tree7.insert(4);
  tree7.insert(6);
  tree7.insert(7);
  tree7.insert(8);
  tree7.insert(10);
  tree7.insert(14);
  tree7.print(std::cout);
  std::cout << "\n8-е дерево: пустое:\n";
  BinarySearchTree<int> tree8;
  tree8.print(std::cout);
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 7: итеративный метод обхода двоичного дерева в ширину.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "1-е дерево: ";
  tree1.breadthFirstWalk();
  std::cout << "2-е дерево: ";
  tree2.breadthFirstWalk();
  std::cout << "3-е дерево: ";
  tree3.breadthFirstWalk();
  std::cout << "4-е дерево: ";
  tree4.breadthFirstWalk();
  std::cout << "5-е дерево: ";
  tree5.breadthFirstWalk();
  std::cout << "6-е дерево: ";
  tree6.breadthFirstWalk();
  std::cout << "7-е дерево: ";
  tree7.breadthFirstWalk();
  std::cout << "8-е дерево: ";
  tree8.breadthFirstWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 8: итеративный метод обхода двоичного дерева (инфиксный). Дерево из презентации.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "1-е дерево: ";
  tree1.iterativeInorderWalk();
  std::cout << "2-е дерево: ";
  tree2.iterativeInorderWalk();
  std::cout << "3-е дерево: ";
  tree3.iterativeInorderWalk();
  std::cout << "4-е дерево: ";
  tree4.iterativeInorderWalk();
  std::cout << "5-е дерево: ";
  tree5.iterativeInorderWalk();
  std::cout << "6-е дерево: ";
  tree6.iterativeInorderWalk();
  std::cout << "7-е дерево: ";
  tree7.iterativeInorderWalk();
  std::cout << "8-е дерево: ";
  tree8.iterativeInorderWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 9: проверка похожести деревьев. Дерево из презентации.\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree1 == tree1) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "2-е дерево:";
  tree2.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree1 == tree2) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "3-е дерево:";
  tree3.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree1 == tree3) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "4-е дерево:";
  tree4.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree1 == tree4) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "3-е дерево:";
  tree3.print(std::cout);
  std::cout << "6-е дерево:";
  tree6.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree3 == tree6) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "1-е дерево:";
  tree1.print(std::cout);
  std::cout << "8-е дерево:";
  tree8.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree1 == tree8) ? "Да!" : "Нет!") << "\n\n";

  std::cout << "8-е дерево:";
  tree8.print(std::cout);
  std::cout << "8-е дерево:";
  tree8.print(std::cout);
  std::cout << "Похожи ли деревья? " << ((tree8 == tree8) ? "Да!" : "Нет!") << "\n";
  std::cout << "--------------------------------------------------------------\n";

  return 0;
}
