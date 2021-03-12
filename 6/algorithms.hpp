#include <vector>
#include <iostream>

void fillVector(std::vector<int>& vec, size_t count);
void printVector(const std::vector<int>& vec, std::ostream& out);

bool isVectorSorted(const std::vector<int>& vec);

size_t binarySearchPlace(const std::vector<int>& vec, int element, size_t left, size_t right);
