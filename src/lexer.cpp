#include "include/lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& input) : input(input), index(0) {
    currentChar = input[index];
}

void Lexer::advance() {
    index++;
    currentChar = (index < input.size()) ? input[index] : '\0';
}

void Lexer::skipWhitespace() {
    while (currentChar == ' ' || currentChar == '\n') {
        advance();
    }
}

std::string Lexer::currentCharAsString() {
    return std::string(1, currentChar);
}

Token* Lexer::collectString() {
    advance(); // skip opening "
    std::string value;

    while (currentChar != '"' && currentChar != '\0') {
        value += currentChar;
        advance();
    }

    advance(); // skip closing "
    return new Token(TokenType::STRING, value);
}

Token* Lexer::collectId() {
    std::string value;

    while (isalnum(currentChar)) {
        value += currentChar;
        advance();
    }

    return new Token(TokenType::ID, value);
}

Token* Lexer::getNextToken() {
    while (currentChar != '\0') {
        if (currentChar == ' ' || currentChar == '\n') {
            skipWhitespace();
            continue;
        }

        if (currentChar == '"') return collectString();
        if (isalnum(currentChar)) return collectId();

        switch (currentChar) {
            case '=':
                advance();
                return new Token(TokenType::EQUALS, "=");
            case ';':
                advance();
                return new Token(TokenType::SEMI, ";");
            case '(':
                advance();
                return new Token(TokenType::LPAREN, "(");
            case ')':
                advance();
                return new Token(TokenType::RPAREN, ")");
        }

        advance(); // skip unknown character
    }

    return nullptr;
}
