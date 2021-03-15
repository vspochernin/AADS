#include <vector>
#include <iostream>

// Технические функции.
void fillVector(std::vector<int>& vec, size_t count, int min, int max);
void printVector(const std::vector<int>& vec, std::ostream& out);
int power10(int power);
int getTheLongestNumberLength(const std::vector<int>& vec); // Длинна самого длинного числа в векторе.

// Вспомогательные функции для сортировок.
bool isVectorSorted(const std::vector<int>& vec);
size_t binarySearchPlace(const std::vector<int>& vec, int element, size_t left, size_t right);
int getDigit(int number, int digit); // Взять разряд digit числа number.

// Сортировки.
void insertionBinarySort(std::vector<int>& vec); // Сортировка по методу вставок с двоичным поиском места вставки.
void radixSort(std::vector<int>& vec); // Поразрядная сортировка.
