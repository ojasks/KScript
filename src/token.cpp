#include "include/token.hpp"

Token::Token(TokenType type, const std::string& value)
    : type(type), value(value) {}
