#include <iostream>
#include <fstream>
#include <vector>

#include "frequency-dictionary.hpp"

int main()
{
  std::cout << "------------------------------------------------------\n"
            << "Вы в главном меню программы, выберите действие:\n"
            << "\"1\" - начать работу с программой\n"
            << "\"2\" - прогнать программу по тестам\n"
            << "\"exit\" - выйти из программы\n"
            << "------------------------------------------------------\n";
  std::string input = "";
  while (true)
  {
    std::cin >> input;
    if (input == "1")
    {
      startProgram();
      break;
    }
    else if (input == "2")
    {
      testProgram();
      break;
    }
    else if (input == "exit")
    {
      break;
    }
    else
    {
      std::cout << "Некорректная команда, попробуйте еще раз.\n";
    }
  }

  return 0;
}
