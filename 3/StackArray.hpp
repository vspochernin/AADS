#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include <iostream>

#include "Stack.hpp"
#include "StackExceptions.hpp"

template <class T>
class StackArray : public Stack<T>
{
public:
  StackArray(int size = 100);
  StackArray(const StackArray<T>& src); // Конструктор копирования.
  StackArray(StackArray<T>&& src); // Конструктор перемещения.
  StackArray& operator=(const StackArray<T>& src); // Конструктор копирующего присваивания.
  StackArray& operator=(StackArray<T>&& src); // Конструктор перемещающего присваивания.
  virtual ~StackArray();
  void push(const T& e);
  T pop();
  T top();
  bool isEmpty();
  size_t getSize();
private:
  T* array_; // Массив элементов стека (0-й элемент не используется, top_ от 1 до size_).
             // Если top_ равен 0, значит стек пустой.
  size_t top_; // Вершина стека, элемент, занесенный в стек последним.
  size_t size_; // Размер стека.
  void swap(StackArray<T>& src);
};

template <class T>
void StackArray<T>::swap(StackArray<T>& src)
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

template <class T>
StackArray<T>::StackArray(int size) :
  array_(nullptr),
  top_(0),
  size_(size)
{ // array_[0] не используется, top_ от 1 до size_.
  try
  {
    array_ = new T[size + 1]; // Пытаемся заказать память под элементы стека...
  }
  catch (...) // Если что-то случилось (выкинется bad_alloc и catch(...) его словит. 
  { //Catch (...) ловит всё.
    throw WrongStackSize(); // Выбрасываем наше исключение WrongStackSize.
  }
}

template <class T>
StackArray<T>::StackArray(const StackArray<T>& src):
  array_(nullptr),
  top_(src.top_),
  size_(src.size_)
{
  try // array_[0] не используется, top_ от 1 до size_.
  {
    array_ = new T[src.size_ + 1];
  }
  catch (...)
  {
    throw WrongStackSize();
  }
  // Копирование массива.
  // TODO: выяснить, < src.top_ или <= src.top_.
  for (int i = 1; i <= src.top_; i++)
  {
    array_[i] = src.array_[i];
  }
}

template <class T>
StackArray<T>::StackArray(StackArray<T>&& src):
  array_(src.array_),
  top_(src.top_),
  size_(src.size_)
{
  src.array_ = nullptr;
  src.size_ = 0;
  src.top_ = 0;
}

template <class T>
StackArray<T>& StackArray<T>::operator=(const StackArray& src)
{
  if (this == &src)
  {
    return *this;
  }

  size_ = src.size_;
  top_ = src.top_;
  delete[] array_;

  try
  {
    array_ = new T[src.size_ + 1];
  }
  catch (...)
  {
    throw WrongStackSize();
  }
  // TODO: выяснить < или <=.
  for (int i = 1; i <= src.top_; i++)
  {
    array_[i] = src.array_[i];
  }
}

template <class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src)
{
  if (this == &src)
  {
    return *this;
  }

  size_ = src.size_;
  top_ = src.top_;
  delete[] array_;
  array_ = src.array_;

  src.array_ = nullptr;
  src.top_ = 0;
  src.size_ = 0;
}

template <class T>
StackArray<T>::~StackArray()
{
  delete[] array_;
}

template <class T>
void StackArray<T>::push(const T& e)
{
  if (top_ == size_)
  {
    throw StackOverflow(); // Нет места для нового элемента.
  }
  array_[++top_] = e; // Увеличение счетчика и занесение нового элемента в стек.
}

template <class T>
T StackArray<T>::pop()
{
  if (top_ == 0)
  {
    throw StackUnderflow(); // Стек пуст.
  }
  return array_[top_--]; // Элемент физически останется в стеке, но больше не доступен.
}

template <class T>
T StackArray<T>::top()
{
  if (top_ == 0)
  {
    throw ("Stack is empty!");
  }
  return array_[top_];
}

template <class T>
bool StackArray<T>::isEmpty()
{
  if (top_ == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <class T>
size_t StackArray<T>::getSize()
{
  return top_;
}

#endif
