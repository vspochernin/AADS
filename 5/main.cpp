#include <iostream>

#include <memory> // std::shared_ptr
#include "queue-array.hpp"

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

  return 0;
}
