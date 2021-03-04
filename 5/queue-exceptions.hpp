#ifndef QUEUE_EXCEPTIONS_HPP
#define QUEUE_EXCEPTIONS_HPP

#include <exception>

// Классы QueueOverflow и QueueUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе с очередью.

class QueueOverflow: public std::exception
{
public:
  QueueOverflow():
    reason_("Queue Overflow")
  {}

  const char* what() const noexcept override
  {
    return reason_;
  }

private:
  const char* reason_;
};

class QueueUnderflow: public std::exception
{
public:
  QueueUnderflow():
    reason_("Queue Underflow")
  {}

  const char* what() const noexcept override
  {
    return reason_;
  }

private:
  const char* reason_;
};

// Исключительная ситуация WrongQueueSize может возникнуть,
// если в консутркторе очереди неправильно задан размер.

class WrongQueueSize: public std::exception
{
public:
  WrongQueueSize():
    reason_("Wrong Queue Size")
  {}

  const char* what() const noexcept override
  {
    return reason_;
  }

private:
  const char* reason_;
};

#endif
