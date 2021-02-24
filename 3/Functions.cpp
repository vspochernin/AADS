#include "Functions.hpp"

#include <memory> // Умные указатели.
                  // Они используются для того, чтобы перед каждым return не писать
                  // delete bracketsStack, а также, чтобы не терять память в исключениях.

#include "StackArray.hpp"

bool checkBalanceBrackets(const std::string& text, int maxDeep)
{
  std::shared_ptr<Stack<char>> bracketsStack(new StackArray<char>(maxDeep));
  //Stack<char>* bracketsStack = new StackArray<char>(maxDeep);
  for (size_t i = 0; i < text.size(); i++)
  {
    switch (text[i])
    {
    case '(':
      bracketsStack->push('(');
      break;
    case '[':
      bracketsStack->push('[');
      break;
    case '{':
      bracketsStack->push('{');
      break;
    case ')':
      if ((bracketsStack->isEmpty()) || (bracketsStack->pop() != '('))
      {
        return false;
      }
      break;
    case ']':
      if ((bracketsStack->isEmpty()) || (bracketsStack->pop() != '['))
      {
        return false;
      }
      break;
    case '}':
      if ((bracketsStack->isEmpty()) || (bracketsStack->pop() != '{'))
      {
        return false;
      }
      break;
    }
  }
  if (bracketsStack->isEmpty()) // Если все открывающие скобки нашли свою закрывающую.
  {
    return true;
  }
  else // Не все открывающие скобки нашли свою закрывающую.
  {
    return false;
  }
}

bool getPostfixFromInfix(const std::string& infix, std::string& postfix, size_t stackSize)
{
  if (!checkBalanceBrackets(infix, stackSize)) // Если скобки расставлены неправильно - выражение тем более.
  {
    return false;
  }
  int countOfOperands = 0;
  int countOfOperators = 0;
  std::shared_ptr<Stack<char>> stack(new StackArray<char>(stackSize));

  for (size_t i = 0; i < infix.size(); i++)
  {
    switch (infix[i])
    {
    case '(': // Если очередной символ из исходной строки - открывающая скобка, то он проталкивается в стек.
      stack->push(infix[i]);
      break;
    case ')': // Закрывающая скобка выталкивает все операции из стека до близжайшей открывающей скобки.
              // Сами скобки в выходную строку не переписываются, а уничтожают друг друга.
      while (stack->top() != '(')
      {
        postfix += stack->pop();
      }
      if (stack->top() == '(')
      {
        stack->pop();
      }
      break;
    case '+':
      countOfOperators++;
      // Если стек не пуст, операция выталкивает из стека все операции с большим или равным приоритетом в выходную строку.
      while ((!stack->isEmpty()) && ((stack->top() == '*') || (stack->top() == '/') || (stack->top() == '+') || (stack->top() == '-')))
      {
        postfix += stack->pop();
      }
      stack->push(infix[i]); // Если стек пуст (или мы вытолкнули элементы), то операция из входной строки заносится в стек.
      break;
    case '-':
      countOfOperators++;
      // Если стек не пуст, операция выталкивает из стека все операции с большим или равным приоритетом в выходную строку.
      while ((!stack->isEmpty()) && ((stack->top() == '*') || (stack->top() == '/') || (stack->top() == '+') || (stack->top() == '-')))
      {
        postfix += stack->pop();
      }
      stack->push(infix[i]); // Если стек пуст (или мы вытолкнули элементы), то операция из входной строки заносится в стек.
      break;
    case '*':
      countOfOperators++;
      // Если стек не пуст, операция выталкивает из стека все операции с большим или равным приоритетом в выходную строку.
      while ((!stack->isEmpty()) && ((stack->top() == '*') || (stack->top() == '/')))
      {
        postfix += stack->pop();
      }
      stack->push(infix[i]); // Если стек пуст (или мы вытолкнули элементы), то операция из входной строки заносится в стек.
      break;
    case '/':
      countOfOperators++;
      // Если стек не пуст, операция выталкивает из стека все операции с большим или равным приоритетом в выходную строку.
      while ((!stack->isEmpty()) && ((stack->top() == '*') || (stack->top() == '/')))
      {
        postfix += stack->pop();
      }
      stack->push(infix[i]); // Если стек пуст (или мы вытолкнули элементы), то операция из входной строки заносится в стек.
      break;
    default: // Операнды переписываем в выходную строку.
      postfix += infix[i];
      countOfOperands++;
      break;
    }
  }
  while (!stack->isEmpty()) // В завершении оставшиеся операции из стека переносятся в выходную строку.
  {
    postfix += stack->pop();
  }
  if ((countOfOperands - countOfOperators) != 1) // Если слишком много операндов (или слишком мало операций) - инфиксная форма задана неверно.
  {
    return false;
  }
  return true;
}

int evaluatePostfix(const std::string& infix, size_t stackSize)
{
  int a = 0;
  int b = 0;
  int result = 0;
  std::string postfix;
  if (!getPostfixFromInfix(infix, postfix, stackSize))
  {
    throw("Failed getting postfix form!");
  }
  std::shared_ptr<Stack<int>> stack(new StackArray<int>(stackSize));
  for (size_t i = 0; i < postfix.size(); i++)
  {
    if ((postfix[i] >= '0') && (postfix[i] <= '9')) // Операнд заносится на стек.
    {
      stack->push(static_cast<int>(postfix[i]) - static_cast<int>('0'));
    }
    else // Поступила операция.
    {
      if (stack->isEmpty())
      {
        throw ("Incorrect postix notation! Not enough operands.");
      }
      b = stack->pop();
      if (stack->isEmpty())
      {
        throw ("Incorrect postix notation! Not enough operands.");
      }
      a = stack->pop();
      switch (postfix[i])
      {
      case '+':
        stack->push(a + b);
        break;
      case '-':
        stack->push(a - b);
        break;
      case '*':
        stack->push(a * b);
        break;
      case '/':
        stack->push(a / b);
        break;
      default:
        throw("Unknown char in postfix string!");
        break;
      }
    }
  }
  if (stack->isEmpty()) // Если после прохождения по постфиксному выражению стек пустой - значит ответа там нет.
  {
    throw("Incorrect postfix notation! No answer.");
  }
  result = stack->pop();
  if (!stack->isEmpty()) // Если после выгрузки ответа из стека там есть еще элементы - что-то не так с постфиксным выражением.
  {
    throw("Incorrect postfix notation! Not enough operators.");
  }
  return result;
}