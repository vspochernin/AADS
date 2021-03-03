#ifndef QUEUE_ARRAY_HPP
#define QUEUE_ARRAY_HPP

#include "queue.hpp"

#include "queue-exceptions.hpp"

template <typename T>
class QueueArray final: public Queue<T> // Модификатор final запрещает наследование от класса.
{
public:
  QueueArray(const QueueArray<T>& src) = delete;
  QueueArray(QueueArray<T>&& src);

  QueueArray(size_t size);

  virtual ~QueueArray() override;

  QueueArray<T>& operator=(const QueueArray<T>& src) = delete;
  QueueArray<T>& operator=(QueueArray<T> && src); // Оператор перемещающего присваивания.

  void enQueue(const T& e) override;
  T deQueue() override;
  bool isEmpty() const override;

private:
  T* array_; // Массив элементов очереди.
  size_t head_ = 1; // Очередь пуста, если head[Q] = tail[Q].
  size_t tail_ = 1; // Первоначально: head[Q] = tail[Q] = 1;
  size_t size_; // Размер очереди.

  void swap(QueueArray<T>& right);
};

template <typename T>
QueueArray<T>::QueueArray<T>(QueueArray<T>&& src):
  array_(src.array_),
  head_(src.head_),
  tail_(src.tail_),
  size_(src.size_)
{
    src.array_ = nullptr;
    src.head_ = 1;
    src.tail_ = 1;
    src.size_ = 0;
}

template <typename T>
QueueArray<T>::QueueArray<T>(size_t size):
  array_(nullptr),
  head_(1),
  tail_(1),
  size_(size)
{
  try
  {
    array_ = new T[size + 1]; // Пытаемся заказать память под элементы очереди...
  }
  catch (...) // Если что-то случилось (например, размер слишком большой или ...)
  {
    throw WrongQueueSize(); // - возникает bad_alloc.
  }
}

template <typename T>
QueueArray<T>::~QueueArray<T>()
{
  delete array_;
}

template <typename T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T> && src)
{
  array_ = src.array_;
  head_ = src.head_;
  tail_ = src.tail_;
  size_ = src.size_;

  src.array_ = nullptr;
  src.head_ = 1;
  src.tail_ = 1;
  src.size_ = 0;
}

template <typename T>
void QueueArray<T>::enQueue(const T& e)
{
  if ((head_ == tail_ + 1) || ((head_ == 0) && (tail_ = size_))) // Если следующий за tail_ - head_, то мы не можем записать
  {                                                              // т.к. станет выполняться условие пустоты.
    throw QueueOverflow(); // Нет места для новго элемента.
  }

  array_[tail_] = e;
  if (tail_ == size_)
  {
    tail_ = 0;
  }
  else
  {
    tail_++;
  }
}

template <typename T>
T QueueArray<T>::deQueue()
{
  if (head_ == tail_)
  {
    throw QueueUnderflow(); // Очередь пуста.
  }

  T result = array_[head_];
  if (head_ == size_)
  {
    head_ = 0;
  }
  else
  {
    head_++;
  }
  return result;
}

template <typename T>
bool QueueArray<T>::isEmpty() const
{
  return head_ == tail;
}

template <typename T>
void QueueArray<T>::swap(QueueArray<T>& right)
{
  std::swap(array_, right.array_);
  std::swap(head_, right.head_);
  std::swap(tail_, right.tail_);
  std::swap(size_, right.size_);
}

#endif
