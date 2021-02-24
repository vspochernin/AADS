#ifndef SINGLY_LINKED_ORDERED_LIST_HPP
#define SINGLY_LINKED_ORDERED_LIST_HPP

#include <iostream>

template <typename T>
struct Node
{
  T item_;
  Node* next_;

  Node(T item, Node* next = nullptr) :
    item_(item),
    next_(next)
  {
  }
};

template <typename T>
class SinglyLinkedOrderedList
{
public:
  SinglyLinkedOrderedList(); 
  SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>&& src);

  ~SinglyLinkedOrderedList();

  void outAll();
  bool insert(T item);
  void clear();
  bool searchItem(T item);
  bool deleteItem(T item);
  void unionOfSets(SinglyLinkedOrderedList& otherList);
  void smartUnionOfSets(SinglyLinkedOrderedList& otherList);
  void substractionOfSets(SinglyLinkedOrderedList& otherList);

  template <typename V>
  friend SinglyLinkedOrderedList<V> intersectionOfSets(SinglyLinkedOrderedList<V>& list1, SinglyLinkedOrderedList<V>& list2);

private:

  Node<T>* head_;

  bool insert(Node<T>* x);
  bool searchNode(T item);
  void deleteNode(Node<T>* x, Node<T>* prev);
};

template <typename T>
SinglyLinkedOrderedList<T>::SinglyLinkedOrderedList() :
  head_(nullptr)
{
}

template <typename T>
void SinglyLinkedOrderedList<T>::outAll()
{
  Node<T>* current = head_;
  while (current != nullptr)
  {
    std::cout << current->item_ << ' ';
    current = current->next_;
  }
  std::cout << "\n";
}

template <typename T>
bool SinglyLinkedOrderedList<T>::insert(Node<T>* x)
{
  Node<T>* current = head_;

  if (current == nullptr) // Если у нас пустой словарь - просто делаем элемент головой.
  {
    x->next_ = nullptr;
    head_ = x;
    return true;
  }

  Node<T>* preCurrent = nullptr; // Предыдущий элемент. Изначально == nullptr.
  while (current != nullptr)
  {
    if (current->item_ < x->item_) // Если очередной элемент меньше - просто смотрим дальше.
    {
      preCurrent = current;
      current = current->next_;
    }
    else if (current->item_ == x->item_) // Если нашли такой элемент в списке - добавить второй раз нельзя.
    {
      return false;
    }
    else if (current->item_ > x->item_) // Если очередной элемент больше вставляемого, значит надо вставить.
    {
      if (preCurrent == nullptr) // Если самый первый элемент словаря - уже больше вставляемого, надо вставить в начало.
      {
        x->next_ = current;
        head_ = x;
        return true;
      }
      else // Иначе - вставляем в середину.
      {
        x->next_ = preCurrent->next_;
        preCurrent->next_ = x;
        return true;
      }
    }
  }

  // Сейчас current стал nullptr, preCurrent указывает на последний элемент. Значит вставляем в конец.
  x->next_ = nullptr;
  preCurrent->next_ = x;
  return true;
}

template<typename T>
bool SinglyLinkedOrderedList<T>::insert(T item)
{
  Node<T>* temp = new Node<T>(item);
  if (insert(temp))
  {
    return true;
  }
  else
  {
    delete temp;
    return false;
  }
}

template<typename T>
void SinglyLinkedOrderedList<T>::clear()
{
  Node<T>* current = nullptr;   // указатель на элемент, подлежащий удалению
  Node<T>* next = head_;        // указатель на следующий элемент
  while (next != nullptr)
  {  // пока есть еще элементы в списке
    current = next;
    next = next->next_;    // переход к следующему элементу
    delete current;        // освобождение памяти удаляемого элемента.
  }
  head_ = nullptr;
}

template<typename T>
SinglyLinkedOrderedList<T>::~SinglyLinkedOrderedList()
{
  clear();
}

template<typename T>
bool SinglyLinkedOrderedList<T>::searchNode(T item)
{
  Node<T>* x = head_;
  while (x != nullptr && x->item_ < item) // Выходим из цикла либо, если прошли все элементы, либо очередной элемент стал больше или равен искомому.
  {
    x = x->next_;
  }
  if (x == nullptr)
  {
    return false;
  }
  if (x->item_ == item)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
bool SinglyLinkedOrderedList<T>::searchItem(T item)
{
  return (searchNode(item));
}

template<typename T>
void SinglyLinkedOrderedList<T>::deleteNode(Node<T>* x, Node<T>* prev)
{
  if (x == nullptr)
  {
    throw ("SinglyLinkedOrderedList::deleteNode  - неверно задан адрес удаляемого узла");
  }

  if (prev == nullptr) // Либо элемент единственный, либо первый.
  {
    head_ = x->next_;
    delete x;
  }
  else // Элемент либо в конце, либо в середине.
  {
    prev->next_ = x->next_;
    delete x;
  }

}

template<typename T>
bool SinglyLinkedOrderedList<T>::deleteItem(T item)
{
  Node<T>* current = head_;
  Node<T>* prev = nullptr;
  while (current != nullptr)
  {
    if (current->item_ == item)
    {
      deleteNode(current, prev);
      return true;
    }
    prev = current;
    current = current->next_;
  }
  return false;
}

// Объединение множеств.
template<typename T>
void SinglyLinkedOrderedList<T>::unionOfSets(SinglyLinkedOrderedList& otherList)
{
  Node<T>* current = otherList.head_;
  while (current != nullptr)
  {
    Node<T>* temp = new Node<T>(current->item_);
    if (!insert(temp))
    {
      delete temp;
    }
    current = current->next_;
  }
  otherList.clear();
}

template<typename T>
void SinglyLinkedOrderedList<T>::smartUnionOfSets(SinglyLinkedOrderedList& otherList)
{
  otherList.substractionOfSets(*this); // Вычитаем из добавляемого списка изменяемый.
  // Теперь мы уверены, что в добавляемом списке нет элементов, которые есть в изменяемом.

  Node<T>* currentNow = head_; // Указатель на текущий элемент в изменяемом списке.
  Node<T>* currentPrev = nullptr; // Указатель на предыдущий элемент в изменяемом списке (изначально nullptr).

  if (otherList.head_ == nullptr) // Если добавляемый список пустой, значит его не надо добавлять.
  {
    return;
  } // После этого  if мы уверены, что добавляемый список не пустой.

  if (currentNow == nullptr) // Если в изменяемом списке нет элементов, то мы просто перемещаем туда добавляемый.
  {
    head_ = otherList.head_;
    otherList.head_ = nullptr;
    return;
  } // После этого if мы уверены, что в обоих списках есть элементы.

  while (otherList.head_ != nullptr) // Пробегаемся по второму списку (из которого добавляем элементы). Т.е. пока не исчерпаем добавляемый список...
  {
    // Пока мы не дошли до момента, когда очередной элемент в изменяемом списке больше элемента во вставляемом списке
    // или пока не кончится изменяемый список...
    while ((currentNow != nullptr) && (currentNow->item_ < otherList.head_->item_))
    {
      // Проходим дальше по изменяемому списку.
      currentPrev = currentNow;
      currentNow = currentNow->next_;
    }
    if (currentNow == nullptr) // Если мы прошли весь изменяемый список, то просто должны перенести оставшийся вставляемый в конец изменяемого.
    {
      // При этом currentPrev будет указывать на предпоследний элемент списка.
      currentPrev->next_ = otherList.head_;
      otherList.head_ = nullptr;
      return;
    }
    else // Иначе, мы вставляем элемент из вставляемого списка в начало или середину.
    {
      if (currentPrev == nullptr) // Вставляем в начало (если currentPrev == nullptr, значит, мы не изменяли его, следовательно, мы на первом элементе).
      {
        Node<T>* temp = otherList.head_->next_;
        otherList.head_->next_ = head_;
        head_ = otherList.head_;
        currentNow = head_;
        currentPrev = nullptr;
        otherList.head_ = temp;
      }
      else // Вставляем в середину (это именно середина, а не конец. Если бы это был конец, мы бы словили его как currentNow == nullptr).
      {
        Node<T>* temp = otherList.head_->next_;
        otherList.head_->next_ = currentNow;
        currentPrev->next_ = otherList.head_;
        currentNow = otherList.head_;
        otherList.head_ = temp;
      }
    }
  }
}


// Вычитание множеств.
template<typename T>
void SinglyLinkedOrderedList<T>::substractionOfSets(SinglyLinkedOrderedList& otherList)
{
  Node<T>* current = otherList.head_;
  while (current != nullptr)
  {
    deleteItem(current->item_);
    current = current->next_;
  }
}

// Пересечение множеств.
template<typename V>
SinglyLinkedOrderedList<V> intersectionOfSets(SinglyLinkedOrderedList<V>& list1, SinglyLinkedOrderedList<V>& list2)
{
  SinglyLinkedOrderedList<V> newList;
  Node<V>* current = list1.head_;
  while (current != nullptr)
  {
    if (list2.searchItem(current->item_))
    {
      newList.insert(current->item_);
    }
    current = current->next_;
  }
  return newList;


}

template<typename T>
SinglyLinkedOrderedList<T>::SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>&& src)
{
  head_ = src.head_;
  src.head_ = nullptr;
}

#endif