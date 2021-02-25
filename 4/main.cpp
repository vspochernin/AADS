#include <iostream>

#include "BinarySearchTree.hpp"

int main()
{
  setlocale(LC_ALL, "Russian");

  std::cout << "\nТест 1\n";
  std::cout << "--------------------------------------------------------------\n";
  BinarySearchTree<int> tree1;
  tree1.insert(8);
  tree1.insert(3);
  tree1.insert(10);
  tree1.insert(6);
  tree1.insert(4);
  tree1.insert(7);
  tree1.insert(1);
  tree1.insert(14);
  tree1.insert(13);
  std::cout << "There are " << tree1.getCount() << " elemets in tree.\n";
  std::cout << "\nHeight of this tree is " << tree1.getHeight() << std::endl;
  std::cout << "Smart output of tree:\n";
  tree1.print(std::cout);
  tree1.inorderWalk();
  std::cout << "IterativeInorderWalk:\n";
  tree1.iterativeInorderWalk();

  tree1.deleteKey(1);
  tree1.inorderWalk();
  tree1.insert(1);

  tree1.deleteKey(3);
  tree1.inorderWalk();
  tree1.insert(3);

  tree1.deleteKey(4);
  tree1.inorderWalk();
  tree1.insert(4);

  tree1.deleteKey(6);
  tree1.inorderWalk();
  tree1.insert(6);

  tree1.deleteKey(7);
  tree1.inorderWalk();
  tree1.insert(7);

  tree1.deleteKey(8);
  tree1.inorderWalk();
  tree1.insert(8);

  tree1.deleteKey(10);
  tree1.inorderWalk();
  tree1.insert(10);

  tree1.deleteKey(13);
  tree1.inorderWalk();
  tree1.insert(13);

  tree1.deleteKey(14);
  tree1.inorderWalk();
  tree1.insert(14);

  std::cout << "\nHeight of this tree is " << tree1.getHeight() << std::endl;
  tree1.inorderWalk();

  std::cout << "One more time\n";
  tree1.deleteKey(8);
  tree1.deleteKey(3);
  tree1.deleteKey(10);
  tree1.deleteKey(6);
  tree1.deleteKey(4);
  tree1.deleteKey(7);
  tree1.deleteKey(1);
  tree1.deleteKey(14);
  tree1.deleteKey(13);
  tree1.insert(8);
  tree1.insert(3);
  tree1.insert(10);
  tree1.insert(6);
  tree1.insert(4);
  tree1.insert(7);
  tree1.insert(1);
  tree1.insert(14);
  tree1.insert(13);
  tree1.inorderWalk();

  tree1.deleteKey(1);
  tree1.inorderWalk();
  tree1.insert(1);

  tree1.deleteKey(4);
  tree1.inorderWalk();
  tree1.insert(4);

  tree1.deleteKey(7);
  tree1.inorderWalk();
  tree1.insert(7);

  tree1.deleteKey(13);
  tree1.inorderWalk();
  tree1.insert(13);

  tree1.deleteKey(6);
  tree1.inorderWalk();
  tree1.insert(6);

  tree1.deleteKey(14);
  tree1.inorderWalk();
  tree1.insert(14);

  tree1.deleteKey(3);
  tree1.inorderWalk();
  tree1.insert(3);

  tree1.deleteKey(10);
  tree1.inorderWalk();
  tree1.insert(10);

  tree1.deleteKey(8);
  tree1.inorderWalk();
  tree1.insert(8);

  std::cout << "\nHeight of this tree is " << tree1.getHeight() << std::endl;
  tree1.inorderWalk();
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 2\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Is 1 there? " << (tree1.iterativeSearch(1) ? "YES!" : "NO!") << std::endl;
  std::cout << "Is 2 there? " << (tree1.iterativeSearch(2) ? "YES!" : "NO!") << std::endl;
  std::cout << "Is 3 there? " << (tree1.iterativeSearch(3) ? "YES!" : "NO!") << std::endl;
  std::cout << "Is 4 there? " << (tree1.iterativeSearch(4) ? "YES!" : "NO!") << std::endl;
  std::cout << "Is 5 there? " << (tree1.iterativeSearch(5) ? "YES!" : "NO!") << std::endl;
  std::cout << "Is 6 there? " << (tree1.iterativeSearch(6) ? "YES!" : "NO!") << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 3\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "There are " << tree1.getCount() << " elemets in tree.\n";
  std::cout << "Height of this tree is " << tree1.getHeight() << std::endl;
  BinarySearchTree<int> tree2;
  tree2.iterativeInorderWalk();
  std::cout << "There are " << tree2.getCount() << " elemets in tree.\n";
  std::cout << "Height of this tree is " << tree2.getHeight() << std::endl;
  std::cout << "IterativeInorderWalk:\n";
  tree2.insert(1);
  tree2.iterativeInorderWalk();
  tree2.inorderWalk();
  std::cout << "There are " << tree2.getCount() << " elemets in tree.\n";
  std::cout << "Height of this tree is " << tree2.getHeight() << std::endl;
  std::cout << "IterativeInorderWalk:\n";
  tree2.insert(0);
  tree2.insert(3);
  tree2.iterativeInorderWalk();
  tree2.inorderWalk();
  std::cout << "There are " << tree2.getCount() << " elemets in tree.\n";
  std::cout << "Height of this tree is " << tree2.getHeight() << std::endl;
  std::cout << "IterativeInorderWalk:\n";
  std::cout << "--------------------------------------------------------------\n";

  std::cout << "\nТест 3\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "Smart output of tree:\n";
  tree2.print(std::cout);
  std::cout << "--------------------------------------------------------------\n";


  std::cout << "\nТест 4\n";
  std::cout << "--------------------------------------------------------------\n";
  tree1.iterativeInorderWalk();
  tree2.iterativeInorderWalk();
  std::cout << "Is trees equal? " << ((tree1 == tree2) ? "YES!" : "NO!") << std::endl;
  tree2.deleteKey(0);
  tree2.insert(4);
  tree2.insert(6);
  tree2.insert(7);
  tree2.insert(8);
  tree2.insert(10);
  tree2.insert(13);
  tree2.insert(14);
  tree1.iterativeInorderWalk();
  tree2.iterativeInorderWalk();
  std::cout << "Is trees equal? " << ((tree1 == tree2) ? "YES!" : "NO!") << std::endl;
  std::cout << "--------------------------------------------------------------\n";

  return 0;
}
