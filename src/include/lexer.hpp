#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

class Lexer {
public:
    char c;
    unsigned int i;
    char* contents;

    Lexer(char* contents);

    void advance();

    void skipWhitespace();

    Token* getNextToken();

    Token* collectString();

    Token* collectId();

    Token* advanceWithToken(Token* token);

    char* getCurrentCharAsString();
};

#endif
