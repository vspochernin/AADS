#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack> // Для итеративного обхода дерева.
#include <vector> // Для перегрузки оператора ==.

//
// Определение шаблона класса BinarySearchTree.
//
template <class T>
class BinarySearchTree
{
public:
	// Конструкторы 
	// Конструктор "по умолчанию" создает пустое дерево.
	BinarySearchTree();
	// Неиспользуемый консутрктор копирования.
	BinarySearchTree(const BinarySearchTree<T> & src) = delete;
	// Конструктор перемещения.
	BinarySearchTree(BinarySearchTree<T>&& src);

	// Перегрузка оператора =.
	BinarySearchTree<T>& operator= (const BinarySearchTree<T>& src) = delete;
	BinarySearchTree<T>& operator= (BinarySearchTree<T>&& src);

	// Деструктор освобождает память, занятую узлами дерева.
	virtual ~BinarySearchTree();
		
	// 1.1 Функция поиска по ключу в бинарном дереве поиска.
	bool iterativeSearch(const T& key) const;

	// 2.1 Вставка нового элемента в дерево:
  // true,если элемент добавлен; false, если элемент уже был.
	bool insert(const T& key);
	
	// Удаление элемента из дерева, не нарушающее порядка элементов
	// true,если элемент удален; false, если элемента не было.
	bool deleteKey(const T& key);
	
	// 4.1 Печать строкового изображения дерева в выходной поток out.
	void print(std::ostream& out) const;
	
	// 5.1 Определение количества узлов дерева.
	int getCount() const;
	
	// 6.1 Определение высоты дерева.
	int getHeight() const;

	// 7 Инфиксный обход дерева (итеративный).
	void iterativeInorderWalk () const;

	// 8.1 Инфиксный обход дерева (рекурсивный).
	void inorderWalk() const;

	// 9 Сравнение деревьев: true, если все узлы деревьев одинаковые.
	bool operator== (const BinarySearchTree<T>& src);

private:
	// Описание структуры узла со ссылками на детей и родителя.
	template <class V>
	struct Node {
		V  key_;         // Значение ключа, содержащееся в узле.
		Node<V>* left_;     // Указатель на левое поддерево.
		Node<V>* right_;    // Указатель на правое поддерево.
		Node<V>* p_;        // Указатель на  родителя.

		// Конструктор узла.
		Node(V key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr):
			key_(key),
			left_(left),
			right_(right),
			p_(p)
		{}
	};

	// Дерево реализовано в виде указателя на корневой узел.
	Node<T>* root_;

	// Метод свап.
	void swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right);

	// Рекурсивная функция для освобождения памяти.
	void deleteSubtree(Node<T>* node);

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска.
	Node<T>* iterativeSearchNode(const T& key) const;

	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток.
	void printNode(std::ostream& out, Node<T>* root) const;
	
	// 5.2 Рекурсивная функция определения количества узлов дерева.
	int getCountSubTree(const Node<T>* node) const;

	// 6.2 Рекурсивная функция определения высоты дерева.
	int getHeightSubTree(Node<T>* node) const;
	
	// 8.2 Рекурсивная функция для организации обхода узлов дерева.
	void inorderWalk(Node<T>* node) const;

}; // Конец определения шаблона класса TreeBinarySearchTree.



  // Конструктор "по умолчанию" создает пустое дерево.
	template <class T>
	BinarySearchTree<T>::BinarySearchTree():
		root_(nullptr)
	{}

	// Конструктор перемещения.
	template <class T>
	BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src)
	{
		root_ = src.root_;
		src.root_ = nullptr;
	}

	// .........................................................................

	// Оператор перемещающего присваивания.
	template <class T>
	BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src)
	{
		deleteSubtree(root_);
		root_ = src.root_;
		src.root_ = nullptr;
	}

	// .........................................................................

	// Деструктор освобождает память, занятую узлами дерева.
	template <class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		deleteSubtree(root_);
	}

	// Рекурсивная функция для освобождения памяти.
	template <class T>
	void BinarySearchTree<T>::deleteSubtree(Node<T>* node)
	{
		if (node !=nullptr){ // Если не пытаемся очистить уже пустое дерево...
			if (node->left_ != nullptr) // Очищаем левое поддерево.
			{
				deleteSubtree(node->left_);
			}
			if (node->right_ != nullptr) // Очищаем правое поддерево.
			{
				deleteSubtree(node->right_);
			}

			// На этом этапе мы уверены, что у node удалены левые и правые поддеревья. Т.е. node - лист.
			if (node->p_ == nullptr) // Если node - корень - удаляем его как корень.
			{
				root_ = nullptr;
				delete node;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если node слева от своего родителя...
				{
					node->p_->left_ = nullptr;
					delete node;
				}
				else if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если node справа от своего родителя...
				{
					node->p_->right_ = nullptr;
					delete node;
				}
			}
		}
	}

	// .........................................................................

	// Метод свап.
	template <class T>
	void BinarySearchTree<T>::swap(BinarySearchTree<T>& left, BinarySearchTree<T>& right)
	{
		std::swap(left.root_, right.root_); // Просто меняем указатели на корень.
	}
	// .........................................................................

	// 1.1 Функция поиска по ключу в бинарном дереве поиска.
	template <class T>
	bool BinarySearchTree<T>::iterativeSearch(const T& key)  const
	{
		return (iterativeSearchNode(key) != nullptr);
	}

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	template <class T>
	BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
	{
		Node<T>* x = root_;

		while ((x != nullptr) && (x->key_ != key)) // Пока может происходить поиск...
		{
			if (key < x->key_)
			{
				x = x->left_;
			}
			else
			{
				x = x->right_;
			}
		}

		return x;
	}
	// .........................................................................
	
	// 2. Вставка нового элемента в дерево:
	// true,если элемент добавлен; false, если элемент уже был.
	template <class T>
	bool BinarySearchTree<T>::insert(const T& key)
	{
		Node<T>* x = root_; // Проверяемый узел.
		Node<T>* y = nullptr; // Хранитель родителя (изначально nullptr).

		if (root_ == nullptr) // Если дерево изначально пустое - вставляемый элемент станет корнем.
		{
			Node<T>* newRoot = new Node<T>(key, nullptr, nullptr, nullptr);
			root_ = newRoot;
			return true;
		}

		while (x != nullptr) // Пока не нашли нужную пустую ячейку...
		{
			if (x->key_ == key) // Не добавляем элемент с ключем, который есть в дереве.
			{
				return false;
			}
			y = x; // Родителем становится проверяемый элемент, так как он пойдет глубже.
			if (key < x->key_)
			{
				x = x->left_;
			}
			else
			{
				x = x->right_;
			}
		}

		if (key < y->key_) // Смотрим, в какую сторону от родителя вставлять элемент.
		{
			y->left_ = new Node<T>(key, nullptr, nullptr, y);
			return true;
		}
		else
		{
			y->right_ = new Node<T>(key, nullptr, nullptr, y);
			return true;
		}
	}
	// .........................................................................

	// 3. Удаление элемента из дерева, не нарушающее порядка элементов.
	template <class T>
	bool BinarySearchTree<T>::deleteKey(const T& key)
	{
		Node<T>* node = iterativeSearchNode(key); // Ищем узел, который собираемся удалить.
		if (node == nullptr)
		{
			return false;
		}

		if ((node->left_ == nullptr) && (node->right_ == nullptr))
		{ // Удаляем лист.
			if (node->p_ == nullptr) // Если этот лист - корень...
			{
				root_ = nullptr;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот лист слева от родителя...
				{
					node->p_->left_ = nullptr;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот лист справа от родителя...
				{
					node->p_->right_ = nullptr;
					delete node;
					return true;
				}
			}
		}
		else if (((node->left_ != nullptr) && (node->right_ == nullptr)))
		{ // Удаляем узел только с левым ребенком.
			if (node->p_ == nullptr) // Если этот узел - корень...
			{
				node->left_->p_ = nullptr;
				root_ = node->left_;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
				{
					node->left_->p_ = node->p_;
					node->p_->left_ = node->left_;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
				{
				node->left_->p_ = node->p_;
				node->p_->right_ = node->left_;
				delete node;
				return true;
				}
			}
		}
		else if (((node->left_ == nullptr) && (node->right_ != nullptr)))
		{ // Удаляем узел только с правым ребенком.
			if (node->p_ == nullptr) // Если этот узел - корень...
			{
				node->right_->p_ = nullptr;
				root_ = node->right_;
				delete node;
				return true;
			}
			else
			{
				if ((node->p_->left_ != nullptr) && (node->p_->left_->key_ == node->key_)) // Если этот узел слева от родителя...
				{
					node->right_->p_ = node->p_;
					node->p_->left_ = node->right_;
					delete node;
					return true;
				}
				if ((node->p_->right_ != nullptr) && (node->p_->right_->key_ == node->key_)) // Если этот узел справа от родителя...
				{
					node->right_->p_ = node->p_;
					node->p_->right_ = node->right_;
					delete node;
					return true;
				}
			}
		}
		else if (((node->left_ != nullptr) && (node->right_ != nullptr)))
		{ // Удаляем узел с обоими детьми. Будем искать минимальный элемент из правого поддерева.
			Node<T>* x  = node->right_; // Смотрим правое поддерево.
			while (x->left_ != nullptr) // Пока есть левые дети - будем идти по ним.
			{
				x = x->left_;
			} // Теперь x - минимальный элемент из правого поддерева.
			if ((x->p_->left_ != nullptr) && (x->p_->left_->key_ == x->key_)) // Если x - слева от своего родителя.
			{
				x->p_->left_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
				if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
				{
					x->right_->p_ = x->p_;
				}
			}
			if ((x->p_->right_ != nullptr) && (x->p_->right_->key_ == x->key_)) // Если x - справа от своего родителя.
			{
				x->p_->right_ = x->right_; // Добавляем к родителю возможную правую ветку x (левой точно нет).
				if (x->right_ != nullptr) // Устанавливаем родителя возможной правой ветки x как родителя самого x.
				{
					x->right_->p_ = x->p_;
				}
			}
			// У нас "в буфере" появился элемент x, которым мы должны заменить удаляемый элемент.
			// Вроде бы нужно поработать с указателями...
			// Но мы можем сделать проще - в удаляемом элементе поставить значение элемента x, а элемент x удалить.
			node->key_ = x->key_;
			delete x;
			return true;
		}

		// Чтобы компилятор не ругался (предупреждением) - ему нужна определенность, что функция точно что-то вернет.
		// Исходя из того, что после каждого возможного случая удаления (оператора delete) стоит return true...
		// Если мы дошли до этой строчки кода - что-то пошло не так.
		// Значит вернем false.
		return false;
	}
	// .........................................................................

	// 4.1 Печать строкового изображения дерева в выходной поток out.
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
			// операция вывода в выходной поток <<.
			// Прим. автора: скорее не для узлов, а для ключей, хранящихся в узлах.
			out << root->key_; // Сначала выведем ключ...
			printNode(out, root->left_); // затем аналогично в скобочках выведем левое...
			printNode(out, root->right_); // и правое деревья.
			// Таким образом, будет наглядно представлена структура дерева.
		}
		out << ')';
	}
	// .........................................................................

	// 5.1 Определение количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCount() const
	{
		return getCountSubTree(root_);
	}

	// 5.2 Рекурсивная функция определения количества узлов дерева
	template <class T>
	int BinarySearchTree<T>::getCountSubTree(const Node<T>* node) const
	{
		// Если узел пустой - возвращаем 0.
		if (node == nullptr){
			return 0;
		}

		// Если узел не пустой - возвращаем 1 + количество узлов снизу.
		return (1 + getCountSubTree(node->left_) + getCountSubTree(node->right_));
	}
	// .........................................................................
	
	// 6.1 Определение высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeight() const
	{
		// Здесь приутствует -1, так как getHeightSubTree считает высоту вместе с корнем
		// А мы считаем высотой - расстояние от корня до самого глубокого узла.
		// В случае, если в дереве только корень - высота будет = 0.
		// В случае, если дерево пустое - высота будет = -1.
		return getHeightSubTree(root_) - 1;
	}

	// 6.2 Рекурсивная функция определения высоты дерева
	template <class T>
	int BinarySearchTree<T>::getHeightSubTree(Node<T>* node) const
	{
		// Если узел пустой - возвращаем 0.
		if (node == nullptr)
		{
			return 0;
		}

		// Если узел непустой - возвращаем 1 + высота самого высокого ребенка.
		return std::max(1 + getHeightSubTree(node->left_), 1 + getHeightSubTree(node->right_));
	}
	// .........................................................................

	// 7. Инфиксный обход дерева (итеративный)
	template <class T>
	void BinarySearchTree<T>::iterativeInorderWalk() const
	{
		std::stack<Node<T>*> nodeStack; // Стек, хранящий указатели на узлы.
		Node<T>* node = root_; // Узел, которому смотрим.
		while ((nodeStack.size() != 0) || (node != nullptr)) // Пока есть узлы на стеке в просмотр или узел, который смотрим ненулевой.
		{
			if (node != nullptr) // Если просматриваемый узел ненулевой...
			{
				nodeStack.push(node); // Заносим его в очередь на просмотр.
				node = node->left_; // А сами смотрим левого ребенка.
			}
			else // Если просматриваемый элемент нулевой (например, по левым детям просматриваемого узла дошли до nullptr)...
			{
				node = nodeStack.top(); // Достаем следующий элемент со стека на просмотр.
				nodeStack.pop();
				std::cout << node->key_; // Смотрим его значение.
				std::cout << ", ";
				node = node->right_; // Переходим к правому ребенку.
			}
		}
		std::cout << "\n";
	}
	// .........................................................................
	
	// 8.1 Инфиксный обход дерева (рекурсивный)
	template <class T>
	void BinarySearchTree<T>::inorderWalk() const
	{
		inorderWalk(root_);
		std::cout << "\n";
	}
	// 8.2 Рекурсивная функция для организации обхода узлов дерева.
	template <class T>
	void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
	{
		if (node != nullptr) // Если узел ненулевой..
		{
			inorderWalk(node->left_); // Обходим его левых детей.
			std::cout << node->key_; // Затем смотрим его значение.
			std::cout << ", ";
			inorderWalk(node->right_); // Наконец, обходим его правых детей.
		}
	}
	// .........................................................................

	// 9 Сравнение деревьев: true, если все узлы деревьев одинаковые.
	template <class T>
	bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
	{
		// Вектора, которые будут хранить последовательность элементов дерева после инфиксного обхода.
		std::vector<T> vec1;
		std::vector<T> vec2;
		// Указатели, которые ходят по дереву.
		Node<T>* node1 = root_;
		Node<T>* node2 = src.root_;
		// Стеки указателей для итеративных обходов деревьев.
		std::stack<Node<T>*> nodeStack1;
		std::stack<Node<T>*> nodeStack2;

		// Итеративно обходим оба дерева и заносим их в вектор.
		while ((nodeStack1.size() != 0) || (node1 != nullptr))
		{
			if (node1 != nullptr)
			{
				nodeStack1.push(node1);
				node1 = node1->left_;
			}
			else
			{
				node1 = nodeStack1.top();
				nodeStack1.pop();
				vec1.push_back(node1->key_);
				node1 = node1->right_;
			}
		}
		while ((nodeStack2.size() != 0) || (node2 != nullptr))
		{
			if (node2 != nullptr)
			{
				nodeStack2.push(node2);
				node2 = node2->left_;
			}
			else
			{
				node2 = nodeStack2.top();
				nodeStack2.pop();
				vec2.push_back(node2->key_);
				node2 = node2->right_;
			}
		}

		// Если два вектора равны - значит равны и два дерева, породившие эти вектора.
		return vec1 == vec2;
	}

#endif
