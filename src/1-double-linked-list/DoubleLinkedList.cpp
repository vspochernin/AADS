#include "DoubleLinkedList.h"
//  DoubleLinkedList.cpp - Дважды связный список целых чисел - реализация методов класса  

 // Конструктор "копирования" – создание копии имеющегося списка
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src)
{
  count_ = 0; // Счетчик сам посчитается за счет insertTail.
  head_ = nullptr;
  tail_ = nullptr;
  if (src.head_ != nullptr) // Если копируемый список не пуст.
  {
    Node* current = src.head_; // Указатель на очередной элемент копируемого списка.
    while (current != nullptr) // Пока мы не пройдемся по всем элементам копируемого списка.
    {
      insertTail(new Node(current->item_)); // Скопировать элемент.
      current = current->next_;
    }
  }
}

// Конструктор копирования с перемещением.
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept
{
  count_ = src.count_;
  head_ = src.head_;
  tail_ = src.tail_;

  src.count_ = 0;
  src.head_ = nullptr;
  src.tail_ = nullptr;
}

// Вставить сформированный узел в хвост списка
void DoubleLinkedList::insertTail(Node* x)
{
  x->prev_ = tail_;
  if (tail_ != nullptr)
  {
    tail_->next_ = x;
  }
  else
  {
    head_ = x;
  }
  tail_ = x;
  count_++;
}

// Вставить сформированный узел в начало списка
void DoubleLinkedList::insertHead(Node* x)
{   // x->prev_ == nullptr,  x->next_ == nullptr  
  x->next_ = head_;
  if (head_ != nullptr)
  {
    // список был НЕ пуст – новый элемент будет и первым, и последним
    head_->prev_ = x;
  }
  else
  {
    // список был пуст – новый элемент будет и первым, и последним
    tail_ = x;
  }
  head_ = x;
  count_++;  // число элементов списка увеличилось
}

// Удаление заданного узла 
void DoubleLinkedList::deleteNode(Node* x)
{
  if (x == nullptr)
  {
    throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
  }

  if (x->prev_ != nullptr)
  {
    // удаляется НЕ голова списка
    (x->prev_)->next_ = x->next_;
  }
  else
  {
    // удаляется голова списка,  второй элемент становится первым
    head_ = x->next_;
  }

  if (x->next_ != nullptr)
  {
    // удаляется НЕ хвост
    (x->next_)->prev_ = x->prev_;
  }
  else
  {
    // удаляется хвост
    tail_ = x->prev_;
  }
  delete x;      // 
  count_--;     // число элементов списка уменьшилось
}

// Поиск узла (адрес) с заданным значением  
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
  Node* x = head_;
  while (x != nullptr && x->item_ != item)
  {
    x = x->next_;
  }
  return x;
}

// Замена информации узла на новое 
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
  x->item_ = item;
  return x;
}

// количество элементов списка
//  int DoubleLinkedList::сount()const{ return count_; }

// Доступ к информации головного узла списка
int DoubleLinkedList::headItem() const
{
  if (head_ != nullptr)
  {
    return head_->item_;
  }
  throw ("headItem - список пуст!");
}

int& DoubleLinkedList::headItem()
{
  if (head_ != nullptr)
  {
    return head_->item_;
  }
  throw ("headItem - список пуст!");
}

// Доступ к информации хвостового узла списка
int DoubleLinkedList::tailItem() const
{
  if (tail_ != nullptr)
  {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}
int& DoubleLinkedList::tailItem()
{
  if (tail_ != nullptr)
  {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

// Вставить элемент в голову списка
void DoubleLinkedList::insertHead(int item)
{   // создаем новый элемент списка и добавляем в голову 
  insertHead(new Node(item));
}


// Вставить элемент в хвост списка
void DoubleLinkedList::insertTail(int item)
{   // создаем новый элемент списка и добавляем в хвост 
  insertTail(new Node(item));
}

// Удалить элемент с головы списка
bool DoubleLinkedList::deleteHead()
{
  if (head_ == nullptr)
  {
    return 0;  // список пуст, удалений нет
  }
  deleteNode(head_);
  return 1;      // список был НЕ пуст, удаление головы
}

// Удалить элемент из хвоста списка
bool DoubleLinkedList::deleteTail()
{
  if (tail_ == nullptr)
  {
    return 0;
  }
  deleteNode(tail_);
  return 1;
}

// Удаление узла с заданным значением  
bool DoubleLinkedList::deleteItem(const int item, bool all)
{
  bool check = false; // Удалился ли хоть один элемент?
  bool isDelete = false; // Было ли удаление в итерации?
  Node* current = head_;
  if (all)
  {
    while (current != nullptr)
    {
      if (current->item_ == item)
      {
        Node* temp = current;
        current = current->next_;
        deleteNode(temp);
        isDelete = true;
        check = true;
      }
      if (isDelete)
      {
        isDelete = false;
      }
      else
      {
        current = current->next_;
      }
    }
  }
  else
  {
    while (current != nullptr)
    {
      if (current->item_ == item)
      {
        deleteNode(current);
        return true;
      }
      current = current->next_;
    }
  }
  return check;
}

// Поиск записи с заданным значением  
bool DoubleLinkedList::searchItem(int item)
{   // возвращаем TRUE, если узел найден 
  return (searchNode(item) != nullptr);
}


// Замена информации узла на новое 
bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
  bool check = false; // Изменился ли хоть один элемент?
  Node* current = head_;
  if (all)
  {
    while (current != nullptr)
    {
      if (current->item_ == itemOld)
      {
        replaceNode(current, itemNew);
        check = true;
      }
      current = current->next_;
    }
  }
  else // Код повторяется в целях оптимизации.
  {
    while (current != nullptr)
    {
      if (current->item_ == itemOld)
      {
        replaceNode(current, itemNew);
        return true;
      }
      current = current->next_;
    }
  }
  return check;
}

// Вывод элементов списка в текстовом виде в стандартный выходной поток 
void DoubleLinkedList::outAll()
{
  Node* current = head_;       // Указатель на элемент
  while (current != nullptr)
  {
    std::cout << current->item_ << ' ';
    current = current->next_;  // Переход к следующему элементу
  }
  std::cout << std::endl;
}

// Очищение списка
void DoubleLinkedList::clear()
{
  Node* current = nullptr;   // указатель на элемент, подлежащий удалению
  Node* next = head_;        // указатель на следующий элемент
  while (next != nullptr)
  {  // пока есть еще элементы в списке
    current = next;
    next = next->next_;    // переход к следующему элементу
    delete current;        // освобождение памяти
  }
  head_ = nullptr;
  tail_ = nullptr;
  count_ = 0;
}

// Деструктор списка	
DoubleLinkedList::~DoubleLinkedList()
{
  clear();
}

// Перемещение списка аргумента в конец вызывающего.
void DoubleLinkedList::addArgument(DoubleLinkedList& otherList)
{
  tail_->next_ = otherList.head_;
  otherList.head_->prev_ = tail_;
  tail_ = otherList.tail_;
  count_ += otherList.count_;

  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;
  otherList.count_ = 0;
}

// Поменять местами два списка.
void DoubleLinkedList::swap(DoubleLinkedList& otherList) noexcept
{
  int countTemp = count_;
  Node* headTemp = head_;
  Node* tailTemp = tail_;

  count_ = otherList.count_;
  head_ = otherList.head_;
  tail_ = otherList.tail_;

  otherList.count_ = countTemp;
  otherList.head_ = headTemp;
  otherList.tail_ = tailTemp;
}

// Перегрузка оператора =.
DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& otherList)
{
  if (this == &otherList)
  {
    return *this;
  }
  DoubleLinkedList tmp(otherList);
  swap(tmp);
  return *this;
}

// Перегрузка оператора = c перемещением.
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& otherList) noexcept
{
  if (this == &otherList)
  {
    return *this;
  }

  clear();

  count_ = otherList.count_;
  head_ = otherList.head_;
  tail_ = otherList.tail_;

  otherList.count_ = 0;
  otherList.head_ = nullptr;
  otherList.tail_ = nullptr;

  return *this;
}

// Перегрузка оператора +.
DoubleLinkedList DoubleLinkedList::operator+(const DoubleLinkedList& otherList) const
{
  DoubleLinkedList result;
  
  Node* current = head_;
  while (current != nullptr)
  {
    result.insertTail(current->item_);
    current = current->next_;
  }
  current = otherList.head_;
  while (current != nullptr)
  {
    result.insertTail(current->item_);
    current = current->next_;
  }

  return result;
}

// Перегрузка опретора ==.
bool DoubleLinkedList::operator==(const DoubleLinkedList& otherList) const
{
  Node* currentThis = head_;
  Node* currentOther = otherList.head_;

  if (count_ != otherList.count_)
  {
    return false;
  }
  while ((currentThis != nullptr) && (currentOther != nullptr))
  {
    if (currentThis->item_ != currentOther->item_)
    {
      return false;
    }
    currentThis = currentThis->next_;
    currentOther = currentOther->next_;
  }
  return true;
}

// Перегрузка оператора <<. 
std::ostream& operator<< (std::ostream& out, const DoubleLinkedList& list)
{
  DoubleLinkedList::Node* current = list.head_;
  while (current != nullptr)
  {
    out << current->item_;
    if (current->next_ != nullptr)
    {
      out << " | ";
    }
    current = current->next_;  // Переход к следующему элементу
  }
  return out;
}