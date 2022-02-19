#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>

bool checkBalanceBrackets(const std::string& text, int maxDeep = 30);

bool getPostfixFromInfix(const std::string& infix, std::string& postrix, size_t stackSize = 30);

int evaluatePostfix(const std::string& infix, size_t stackSize = 30);

#endif
