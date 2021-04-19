#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>
#include <string>

// Дважды связный список пар ключ(слово) - значение(частота встречаемости слова).
class DoubleLinkedList
{
public:
  DoubleLinkedList(); // TODO:перенести: count_(0), head_(nullptr), tail_(nullptr) {}   // Конструктор "по умолчанию" - создание пустого списка.

  virtual ~DoubleLinkedList(); // Деструктор списка

  //TODO:возможно удалитьfriend std::ostream& operator<< (std::ostream& out, const DoubleLinkedList& list); // Перегрузка оператора <<.

  size_t count()const; // TODO:Перенести{ return count_; }   // Количество элементов списка.
  //TODO:возможно удалитьint headItem() const; // Константный доступ к информации головного узла списка
  //TODO:возможно удалитьint& headItem(); // Доступ к информации головного узла списка
  //TODO:возможно удалитьint tailItem() const; // Константный доступ к информации хвостового узла списка
  //TODO:возможно удалитьint& tailItem(); // Доступ к информации хвостового узла списка
  void insertItem(const std::string& key); // Добавление узла с заданным ключом (или увеличение счетчика частотности).
  bool deleteItem(const std::string& key); // Удаление узла с заданным ключом.  //TODO: удалил bool all = false
  //TODO:возможно удалитьbool searchItem(const std::string& key); // Поиск записи с заданным ключом.
  //TODO:возможно удалитьvoid outAll(); // Вывод элементов списка в текстовом виде в стандартный выходной поток
  void clear();  // Очищение списка

private:
  // Тип Node используется для описания элемента цепочки, связанного со
  // следующим с помощью поля next_ и предшествующим с помощью поле prev_.
  struct Node
  {
    std::string key_; // Ключ (слово).
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

  //TODO:возможно удалитьNode* head() const; //TODO: перенести { return head_; } // Доступ к головному узлу списка.
  //TODO:возможно удалитьNode* tail() const; //TODO: перенести { return tail_; } // Доступ к хвостовому узлу списка.
  //TODO:возможно удалитьvoid insertTail(Node* x); // Всавить сформированный узел в хвост списка.
  //TODO:возможно удалитьvoid insertHead(Node* x); // Вставить сформированный узел в начало списка. //TODO: разобраться (int item);
  void insertNode(Node* x); // Вставить сформированный узел в список.
  void deleteNode(Node* x); // Удаление заданного узла.
  Node* searchNode(std::string key); // Поиск узла (адрес) с заданным значением ключа.
};

#endif
