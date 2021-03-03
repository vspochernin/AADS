#ifndef QUEUE_EXCEPTIONS_HPP
#define QUEUE_EXCEPTIONS_HPP

#include <exception>

// Классы QueueOverflow и QueueUnderflow представляют две основные
// исключительные ситуации, которые могут возникнуть при работе с очередью.

class QueueOverflow: public std::exception
{
public:
  QueueOverflow():
    std::exception("Queue Overflow")
  {}
};

class QueueUnderflow: public std::exception
{
public:
  QueueUnderflow():
    std::exception("Queue Underflow")
  {}
};

// Исключительная ситуация WrongQueueSize может возникнуть,
// если в консутркторе очереди неправильно задан размер.

class WrongQueueSize: public std::exception
{
public:
  WrongQueueSize():
    std::exception("Wrong Queue Size")
  {}
};

#endif
