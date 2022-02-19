#include <iostream>

#include "StackArray.hpp"
#include "Functions.hpp"

int main()
{
  std::cout << "---------------------TEST 1----------------------------------\n";
  const char* text00 = " ok ";
  std::cout << text00 << ": " << (checkBalanceBrackets(text00) ? "right" : "wrong") << std::endl;

  const char* text01 = "( ) ok ";
  std::cout << text01 << ": " << (checkBalanceBrackets(text01) ? "right" : "wrong") << std::endl;

  const char* text02 = "( ( [] ) ) ok ";
  std::cout << text02 << ": " << (checkBalanceBrackets(text02) ? "right" : "wrong") << std::endl;

  const char* text03 = "( ( [ { } [ ] ( [ ] ) ] ) ) OK";
  std::cout << text03 << ": " << (checkBalanceBrackets(text03) ? "right" : "wrong") << std::endl;

  const char* text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  std::cout << text04 << ": " << (checkBalanceBrackets(text04) ? "right" : "wrong") << std::endl;

  const char* text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  std::cout << text05 << ": " << (checkBalanceBrackets(text05) ? "right" : "wrong") << std::endl;

  const char* text06 = "( ( [{ ][ ]([ ])]) ) unpaired bracket ";
  std::cout << text06 << ": " << (checkBalanceBrackets(text06) ? "right" : "wrong") << std::endl;

  const char* text07 = ")))( ( [{ ][ ]([ ])]) ) close brackets at start ";
  std::cout << text07 << ": " << (checkBalanceBrackets(text07) ? "right" : "wrong") << std::endl;
  std::cout << "-------------------------------------------------------------\n";

  std::cout << "---------------------TEST 2----------------------------------\n";
  // Проверить достоверность можно на https://www.semestr.online/informatics/polish.php.
  std::string buffer08 = "";
  const char* text08 = "(A+B)*(C+D)-E";
  std::cout << text08 << ": " << (getPostfixFromInfix(text08, buffer08) ? buffer08 : "wrong") << std::endl;

  std::string buffer09 = "";
  const char* text09 = "A*(A+B)/(A+B)*D";
  std::cout << text09 << ": " << (getPostfixFromInfix(text09, buffer09) ? buffer09 : "wrong") << std::endl;

  std::string buffer10 = "";
  const char* text10 = "C*D+A+B*D/(A-E*D-(A*(B-D*C)))+E*A";
  std::cout << text10 << ": " << (getPostfixFromInfix(text10, buffer10) ? buffer10 : "wrong") << std::endl;

  std::string buffer11 = "";
  const char* text11 = "5+(3*4*(4+3*(4-3*5))-3)*1*2*(3-1)*2";
  std::cout << text11 << ": " << (getPostfixFromInfix(text11, buffer11) ? buffer11 : "wrong") << std::endl;

  std::string buffer12 = "";
  const char* text12 = "1+2+";
  std::cout << text12 << ": " << (getPostfixFromInfix(text12, buffer12) ? buffer12 : "wrong") << std::endl;

  std::cout << "-------------------------------------------------------------\n";

  std::cout << "---------------------TEST 3----------------------------------\n";
  // Проверить достоверность можно, вбив выражение в гугл поиск.
  const char* text13 = "2+2*2";
  std::cout << text13 << ": " << evaluatePostfix(text13) << std::endl;

  const char* text14 = "3*7*(5+8)-5*2";
  std::cout << text14 << ": " << evaluatePostfix(text14) << std::endl;

  const char* text15 = "1+2+3*4+5+(6*7)-8*9";
  std::cout << text15 << ": " << evaluatePostfix(text15) << std::endl;

  const char* text16 = "5+(3*4*(4+3*(4-3*5))-3)*1*2*(3-1)*2";
  std::cout << text16 << ": " << evaluatePostfix(text16) << std::endl;

  try
  {
    const char* text17 = "+1*(2+3)";
    std::cout << text17 << ": " << evaluatePostfix(text17) << std::endl;
  }
  catch (const char* error)
  {
    std::cout << error << std::endl;
  }
  std::cout << "-------------------------------------------------------------\n";

  return 0;
}
