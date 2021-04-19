#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>
#include <string>

// Дважды связный список пар ключ(слово) - значение(частота встречаемости слова).
class DoubleLinkedList
{
public:
  DoubleLinkedList(); // TODO:перенести: count_(0), head_(nullptr), tail_(nullptr) {}   // Конструктор "по умолчанию" - создание пустого списка.

  //TODO:ВРЕМЕННОудалитьDoubleLinkedList(const DoubleLinkedList& src); // TODO: Возможно вообще удалить  // Конструктор "копирования" – создание копии имеющегося списка.
  //TODO:ВРЕМЕННОудалитьDoubleLinkedList(DoubleLinkedList&& src) noexcept; // Конструктор копирования с перемещением.

  virtual ~DoubleLinkedList(); // Деструктор списка

  //TODO::ВРЕМЕННОудалитьDoubleLinkedList& operator=(const DoubleLinkedList& otherList); // Перегрузка оператора =.
  //TODO::ВРЕМЕННОудалитьDoubleLinkedList& operator=(DoubleLinkedList&& otherList) noexcept; // Перегрузка оператора = c перемещением.
  //TODO:ВРЕМЕННОудалитьDoubleLinkedList operator+(const DoubleLinkedList& otherList) const; // Перегрузка оператора +.
  //TODO:ВРЕМЕННОудалитьbool operator==(const DoubleLinkedList& otherList) const; // Перегрузка опретора ==.
  friend std::ostream& operator<< (std::ostream& out, const DoubleLinkedList& list); // Перегрузка оператора <<.

  int count()const; // TODO:Перенести{ return count_; }   // Количество элементов списка.
  int headItem() const; // Константный доступ к информации головного узла списка
  int& headItem(); // Доступ к информации головного узла списка
  int tailItem() const; // Константный доступ к информации хвостового узла списка
  int& tailItem(); // Доступ к информации хвостового узла списка
  //TODO:ЗАМЕНИТЬ на один методvoid insertHead(std::string key); // Вставить элемент в голову списка.
  //TODO:ЗАМЕНИТЬ на один методvoid insertTail(std::string key); // Вставить элемент в хвост списка
  //TODO:удалитьbool deleteHead(); // Удалить элемент с головы списка.
  //TODO:удалитьbool deleteTail(); // Удалить элемент из хвоста списка.
  bool deleteItem(const std::string& key); // Удаление узла с заданным ключом.  //TODO: удалил bool all = false
  bool searchItem(std::string key); // Поиск записи с заданным ключом.
  // TODO:удалитьbool replaceItem(size_t valueOld, size_t valueNew, bool all = false); // Замена информации узла на новое.
  void outAll(); // Вывод элементов списка в текстовом виде в стандартный выходной поток
  void clear();  // Очищение списка
  //TODO:ВРЕМЕННОудалитьvoid addArgument(DoubleLinkedList& otherList); // Перемещение списка аргумента в конец вызывающего.
  //TODO:ВРЕМЕННОудалитьvoid swap(DoubleLinkedList& otherList) noexcept; // Поменять местами два списка.

private:
  // Тип Node используется для описания элемента цепочки, связанного со
  // следующим с помощью поля next_ и предшествующим с помощью поле prev_.
  struct Node
  {
    std::string key_  // Ключ (слово).
    size_t value_;    // Значение (частота встречаемости слова).
    Node* next_;      // Указатель на следующий элемент списка.
    Node* prev_;      // Указатель на предшествующий элемент списка.

    // Конструктор для создания нового элемента списка.
    Node(std::string key, size_t value, Node* next = nullptr, Node* prev = nullptr):
      key_(key),
      value_(value),
      next_(next),
      prev_(prev)
    {}
  };

  size_t count_;      // Cчетчик числа элементов списка.
  Node* head_;        // Указатель на первый элемент списка.
  Node* tail_;        // Указатель на последний элемент списка.

  Node* head() const; //TODO: перенести { return head_; } // Доступ к головному узлу списка.
  Node* tail() const; //TODO: перенести { return tail_; } // Доступ к хвостовому узлу списка.
  void insertTail(Node* x); // Всавить сформированный узел в хвост списка.
  void insertHead(Node* x); // Вставить сформированный узел в начало списка. //TODO: разобраться (int item);
  void deleteNode(Node* x); // Удаление заданного узла.
  Node* searchNode(std::string key); // Поиск узла (адрес) с заданным значением ключа.
  // TODO:удалитьNode* replaceNode(Node* x, size_t value_); // Замена информации узла на новое //TODO: Возможно, вообще удалить.
};

#endif

