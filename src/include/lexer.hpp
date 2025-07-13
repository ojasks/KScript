#pragma once
#include <string>
#include <vector>
#include "token.hpp"

class Lexer {
public:
    Lexer(const std::string& input);
    Token* getNextToken();

private:
    std::string input;
    char currentChar;
    size_t index;

    void advance();
    void skipWhitespace();
    Token* collectString();
    Token* collectId();
    std::string currentCharAsString();
};
