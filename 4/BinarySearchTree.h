#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>

//
// Определение шаблона класса BinarySearchTree
//
template <class T>
class BinarySearchTree
{
public:

	// Конструкторы 
	// "по умолчанию" создает пустое дерево
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T> & scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr);

	//
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src);

	// Деструктор освобождает память, занятую узлами дерева
	virtual ~BinarySearchTree();
		
	// 1.1 Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const;
	
	// 2 Вставка нового элемента в дерево:
    // true,если элемент добавлен; false, если элемент уже был
	bool insert(const T& key);
	
	// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
	// true,если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);
	
	// 4.1 Печать строкового изображения дерева в выходной поток out
	void print(std::ostream& out) const;
	
	// 5.1 Определение количества узлов дерева
	int getCount() const;
	
	// 6.1 Определение высоты дерева
	int getHeight() const;
	
	// 7 Инфиксный обход дерева (итеративный) 
	void iterativeInorderWalk () const;

	// 8.1 Инфиксный обход дерева (рекурсивный) 
	void inorderWalk() const;

	// 9 Сравнение деревьев: true, если все узлы деревьев одинаковые
	bool operator== (const BinarySearchTree <T>& src);	

private:

	// Описание структуры узла со ссылками на детей и родителя
	template <class T>
	struct Node {
		T  key_;         // значение ключа, содержащееся в узле
		Node<T>* left_;     // указатель на левое поддерево
		Node<T>* right_;    // указатель на правое поддерево
		Node<T>* p_;        // указатель на  родителя 
						 
		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{  }
	};

	// Дерево реализовано в виде указателя на корневой узел.
	Node<T>* root_;

	void swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right);

	// Рекурсивная функция для освобождения памяти
	void deleteSubtree(Node<T>* node);

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node<T>* iterativeSearchNode(const T& key) const;
	
	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(std::ostream& out, Node<T>* root) const;
	
	// 5.2 Рекурсивная функция определения количества узлов дерева
	int getCountSubTree(const Node<T>* node) const;

	// 6.2 Рекурсивная функция определения высоты дерева
	int getHeightSubTree(Node<T>* node) const;
	
	// 8.2 Рекурсивная функция для организации обхода узлов дерева.
	void inorderWalk(Node<T>* node) const;

}; // конец шаблона класса TreeBinarySearchTree



    // Конструктор "по умолчанию" создает пустое дерево
	template <class T>
	BinarySearchTree<T>::BinarySearchTree(): root_(nullptr)
	{}
	template <class T>
	BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr)
	{
		// ???
	}

	// .........................................................................
	template <class T>
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src)
	{
		// ???
	}

	// .........................................................................
	// Деструктор освобождает память, занятую узлами дерева

	template <class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		deleteSubtree(root_);
	}

	// Рекурсивная функция для освобождения памяти
	template <class T>
	void BinarySearchTree<T>::deleteSubtree(Node<T>* node)
	{
		// ??? 
	}

	// ......................................................................... 
	template <class T>
	void BinarySearchTree<T>::swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right)
	{
		// ??? использовать swap
	}
	// .........................................................................

	// 1.1 Функция поиска по ключу в бинарном дереве поиска
	template <class T>
	bool BinarySearchTree<T>::iterativeSearch(const T& key)  const
	{
		return (iterativeSearchNode(key) != nullptr);
	}
	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	template <class T>
	BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
	{
		// ???
		return nullptr; // ??? заменить при реализации
	}
	// .........................................................................
	
	// 2. Вставка нового элемента в дерево:
	// true,если элемент добавлен; false, если элемент уже был

	template <class T>
	bool BinarySearchTree<T>::insert(const T& key)
	{
		// ???
		return true; // ??? заменить при реализации
	}
	// .........................................................................

	// 3. Удаление элемента из дерева, не нарушающее порядка элементов
	template <class T>
	bool BinarySearchTree<T>::deleteKey(const T& key)
	{
		// . . . 
	}
	// .........................................................................

	// 4.1 Печать строкового изображения дерева в выходной поток out
	template <class T>
	void BinarySearchTree<T>::print(std::ostream& out) const
	{
		printNode(out, root_);
		out << std::endl;
	}
	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	template <class T>
	void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
	{
		// Изображение дерева заключается в круглые скобки.
		out << '(';
		if (root != nullptr) {
			// Для узлов дерева должна быть определена (или переопределена)
			// операция вывода в выходной поток <<
			out << root->key_;
			printNode(out, root->left_);
			printNode(out, root->right_);
		}
		out << ')';
	}
	// .........................................................................

	//5.1 Определение количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCount() const
	{
		return getCountSubTree(this->root_);
	}
	// 5.2 Рекурсивная функция определения количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCountSubTree(const Node<T>* node) const
	{
		if (node == nullptr)
			return 0;
		return (1 + getCountSubTree(node->left_) +
			getCountSubTree(node->right_));
	}
	// .........................................................................
	
	// 6.1 Определение высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeight() const
	{
		return getHeightSubTree(this->root_);
	}
	// 6.2 Рекурсивная функция определения высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeightSubTree(Node<T>* node) const
	{
		// ??? 
		return 0; // ??? заменить при реализации
	}
	
	// .........................................................................

	// 7. Инфиксный обход дерева (итеративный) 
	template <class T>
	void BinarySearchTree<T>::iterativeInorderWalk() const
	{
		// ??? 
	}
	// .........................................................................
	
	// 8.1 Инфиксный обход дерева (рекурсивный) 
	template <class T>
	void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
	{
		return inorderWalk(this->root_);
	}
	// 8.2 Рекурсивная функция для организации обхода узлов дерева.
	template <class T>
	void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
	{
		// ??? 
	}
	// .........................................................................
	// 9. Сравнение деревьев: true, если все узлы деревьев одинаковые
	template <class T>
	bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
	{
		// ???
	}

#endif
