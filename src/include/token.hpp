#pragma once
#include <string>

enum class TokenType {
    ID,
    EQUALS,
    SEMI,
    STRING,
    LPAREN,
    RPAREN
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value);
};
