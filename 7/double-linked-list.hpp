#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>
#include <string>

// Дважды связный список пар ключ(слово) - значение(частота встречаемости слова).
class DoubleLinkedList
{
public:
  DoubleLinkedList(); // Конструктор "по умолчанию" - создание пустого списка.

  virtual ~DoubleLinkedList(); // Деструктор списка.

  size_t count() const; // Количество элементов списка.
  void insertItem(const std::string& key); // Добавление узла с заданным ключом (или увеличение счетчика частотности).
  bool deleteItem(const std::string& key); // Удаление узла с заданным ключом.
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

  void insertNode(Node* x); // Вставить сформированный узел в список.
  void deleteNode(Node* x); // Удаление заданного узла.
  Node* searchNode(std::string key); // Поиск узла (адрес) с заданным значением ключа.
};

#endif
