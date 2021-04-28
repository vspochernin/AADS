#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <iostream>
#include <string>
#include <vector>

// Дважды связный список пар ключ(слово) - значение(частота встречаемости слова).
class DoubleLinkedList
{
public:
  DoubleLinkedList(); // Конструктор "по умолчанию" - создание пустого списка.

  virtual ~DoubleLinkedList(); // Деструктор списка.

  bool insertItem(const std::string& key); // Добавление узла с заданным ключом (или увеличение счетчика частотности).
  size_t searchItem(const std::string& key) const; // Поиска частоты вхождения слова key.
  bool deleteItem(const std::string& key); // Удаление узла с заданным ключом.
  void clear();  // Очищение списка.
  size_t count() const; // Получить количество элементов списка.
  void print(std::ostream& out) const; // Вывести содержимое списка в out.
  void fillVector(std::vector< std::pair< std::string, size_t > >& vec) const; // Добавить к поступаемому на вход вектору пары из списка.
  void fillThreeMost(std::vector< std::pair< std::string, size_t > >& vec) const; // Заполнить вектор трех чаще всего встречающихся слов.

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
      key_(std::move(key)),
      value_(value),
      next_(next),
      prev_(prev)
    {}
  };

  size_t count_;      // Cчетчик числа элементов списка.
  Node* head_;        // Указатель на первый элемент списка.
  Node* tail_;        // Указатель на последний элемент списка.

  void insertNode(Node* x); // Вставить сформированный узел в список.
  Node* searchNode(const std::string& key) const; // Поиск узла (адрес) с заданным значением ключа.
  void deleteNode(Node* x); // Удаление заданного узла.
};

#endif
