#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum TokenType {
    TOKEN_ID,
    TOKEN_EQUALS,
    TOKEN_SEMI,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_LBRACE,
    TOKEN_RPAREN,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_EOF
};

class Token {
public:
    TokenType type;
    std::string value;

    Token(TokenType type, const std::string& value)
        : type(type), value(value) {}
};

Token* init_token(int type, const char* value);

#endif // TOKEN_HPP
