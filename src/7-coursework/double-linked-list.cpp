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

bool DoubleLinkedList::insertItem(const std::string& key)
{
  Node* current = head_; // Указатель на текущий элемент
  while (current != nullptr) // Если в списке уже есть элемент с таким ключем - просто увеличим его value_.
  {
    if (current->key_ == key)
    {
      current->value_++;
      return false; // Добавления не было.
    }
    current = current->next_;
  }
  // Сейчас мы уверены в том, что в списке нет элемента с ключем key.
  // Поэтому просто добавим в список элемент с ключем key и значением 1.
  insertNode(new Node(key, 1));
  return true; // Добавление было.
}

size_t DoubleLinkedList::searchItem(const std::string& key) const
{
  Node* result = searchNode(key);
  if (result == nullptr)
  {
    return 0;
  }
  else
  {
    return result->value_;
  }
}

bool DoubleLinkedList::deleteItem(const std::string& key)
{
  Node* current = head_;
  while (current != nullptr)
  {
    if (current->key_ == key)
    {
      deleteNode(current);
      return true; // Удаление было.
    }
    current = current->next_;
  }
  return false; // Удаления не было (так как элемент с таким ключом отсутствовал в списке).
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

void DoubleLinkedList::print(std::ostream& out) const
{
  Node* current = head_;
  while (current != nullptr)
  {
    out << current->key_ <<": " << current->value_ << "\n"; // Выводим элемент.
    current = current->next_; // Переходим к следующему.
  }
}

void DoubleLinkedList::fillVector(std::vector < std::pair< std::string, size_t > > &vec) const
{
  Node* current = head_;
  while (current != nullptr) // Просто записываем все пары ключ - значение в вектор.
  {
    std::pair< std::string, size_t > pair;
    pair.first = current->key_;
    pair.second = current->value_;
    vec.push_back(pair);
    current = current->next_;
  }
}

void DoubleLinkedList::fillThreeMost(std::vector< std::pair< std::string, size_t > >& vec) const
{
  if (vec.size() != 3) // Вектор должен быть размером 3.
  {
    throw (std::invalid_argument("Некорректный размер подаваемого вектора!"));
  }

  Node* current = head_;
  while (current != nullptr) // Каждую пару ключ - значение ставим на свое место в векторе (если она должна там быть).
  {
    std::pair< std::string, size_t > pair;
    pair.first = current->key_;
    pair.second = current->value_;
    if (pair.second > vec[0].second) // Если пара должна оказаться на первом месте...
    {
      vec[2] = vec[1]; // ...смещаем уже стоявшие элементы.
      vec[1] = vec[0];
      vec[0] = pair; // И ставим пару на первое место.
    }
    else if (pair.second > vec[1].second)
    {
      vec[2] = vec[1];
      vec[1] = pair;
    }
    else if (pair.second > vec[2].second)
    {
      vec[2] = pair;
    }
    current = current->next_;
  }
}

size_t DoubleLinkedList::count() const
{
  return count_;
}

void DoubleLinkedList::insertNode(Node* x)
{
  // Так как на этом этапе мы уверены, что элемента с таким ключем в списке нет - просто добавим в начало списка.
  // Мы уверены в этом, потому что метод вызывается из insertItem() после проверки всего списка.
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

DoubleLinkedList::Node* DoubleLinkedList::searchNode(const std::string& key) const
{
  Node* current = head_;
  while ((current != nullptr) && (current->key_ != key)) // Пока не прошли весь список или не нашли нужный узел...
  {
    current = current->next_; // ...ищем дальше.
  }
  return current;
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
