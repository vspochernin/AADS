#ifndef QUEUE_HPP
#define QUEUE_HPP

// Шаблон класса Queue представляет понятие абстрактной очереди.

template <class T>
class Queue
{
public:
  virtual ~Queue() = default;

  virtual void enQueue(const T& e) = 0; // Добавление элемента в стек.
  virtual T deQueue() = 0; // Удаление и возвращение верхнего элемента.
  virtual bool isEmpty() const = 0; // Проверка на пустоту.
};

#endif
