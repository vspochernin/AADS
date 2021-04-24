#include <iostream>
#include <fstream>
#include <vector>

#include "frequency-dictionary.hpp"

int main()
{
  FrequencyDictionary test;
  test.readFile("input.txt");
  std::ofstream fout("output.txt");
  test.printSorted(fout);

  return 0;
}
