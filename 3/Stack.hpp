#ifndef STACK_HPP
#define STACK_HPP

#include <stddef.h> // Для size_t.

template <class T>
class Stack
{
public:
  virtual ~Stack() {}
  virtual void push(const T& e) = 0; // Добавление элемента в стек.
  virtual T pop() = 0; // Удаление и возвращение верхнего элемента.
                       //Если элементов нет, может возникнуть StackUnderflow
  virtual T top() = 0; // Показать верхний элемент.
  virtual bool isEmpty() = 0; // Проверка стека на пустоту.
  virtual size_t getSize() = 0;
};

#endif
