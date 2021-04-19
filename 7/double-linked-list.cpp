#include "double-linked-list.hpp"

DoubleLinkedList::DoubleLinkedList():
  count_(0),
  head_(nullptr),
  tail_(nullptr)
{}

DoubleLinkedList::~DoubleLinkedList()
{
  clear();
}

void DoubleLinkedList::insertItem(const std::string& key)
{
  Node* current = head_; // Указатель на текущий элемент
  while (current != nullptr) // Если в списке уже есть элемент с таким ключем - просто увеличим его value_.
  {
    if (current->key_ == key)
    {
      current->value_++;
      return;
    }
    current = current->next_;
  }
  // Сейчас мы уверены в том, что в списке нет элемента с ключем key.
  // Поэтому просто добавим в список элемент с ключем key и значением 1.
  insertNode(new Node(key, 1));
}

bool DoubleLinkedList::deleteItem(const std::string& key)
{
  bool check = false; // Удалился ли элемент?
  Node* current = head_;
  while (current != nullptr)
  {
    if (current->key_ == key)
    {
      deleteNode(current);
      return true;
    }
    current = current->next_;
  }
  return check;
}

void DoubleLinkedList::clear()
{
  Node* current = nullptr; // Указатель на элемент, подлежащий удалению.
  Node* next = head_; // Указатель на следующий элемент.
  while (next != nullptr) // Пока в списке есть элементы.
  {
    current = next;
    next = next->next_; // Переход к следующему элементу.
    delete current; // Освобождение памяти.
  }
  count_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}

size_t DoubleLinkedList::count() const
{
  return count_;
}

void DoubleLinkedList::insertNode(Node* x)
{
  // Так как на этом этапе мы уверены, что элемента с таким ключем в списке нет - просто добавим в начало списка.
  x->next_ = head_;
  if (head_ != nullptr)
  {
    // Список был НЕ пуст - предыдущий первый элемент должен указывать на вставляемый.
    head_->prev_ = x;
  }
  else
  {
    // Список был пуст - новый элемент будет и первым, и последним.
    tail_ = x;
  }
  head_ = x; // Теперь x - первый элемент списка.
  count_++; // Число элементов списка увеличилось.
}

void DoubleLinkedList::deleteNode(Node* x)
{
  if (x == nullptr)
  {
    throw std::invalid_argument("DoubleLinkedList::deleteNode - неверно задан адрес удаляемого узла");
  }

  if (x->prev_ != nullptr)
  {
    // Удаляется НЕ голова списка.
    // Значит с предыдущего элемента переносим указатель на следующий за удаляемым элемент.
    (x->prev_)->next_ = x->next_;
  }
  else
  {
    // Удаляется голова списка.
    // Значит следующий за удаляемым элемент становится первым.
    head_ = x->next_;
  }

  if (x->next_ != nullptr)
  {
    // Удаляется НЕ хвост списка.
    // Значит со следующего элемента переносим указатель на предыдущий перед удаляемым элемент.
    (x->next_)->prev_ = x->prev_;
  }
  else
  {
    // Удаляется хвост.
    // Значит предыдущий перед удаляемым элемент становится последним.
    tail_ = x->prev_;
  }
  delete x; // Чистим память.
  count_--; // Число элементов списка уменьшилось на 1.
}
