#include "include/lexer.hpp"
#include <cstdlib>
#include <cstring>
#include <cctype>

Lexer::Lexer(char* contents) {
    this->contents = contents;
    this->i = 0;
    this->c = contents[this->i];
}

void Lexer::advance() {
    if (this->c != '\0' && this->i < strlen(this->contents)) {
        this->i += 1;
        this->c = this->contents[this->i];
    }
}

void Lexer::skipWhitespace() {
    while (this->c == ' ' || this->c == 10) {
        this->advance();
    }
}

Token* Lexer::getNextToken() {
    while (this->c != '\0' && this->i < strlen(this->contents)) {
        this->skipWhitespace();

        if (this->c == '"') {
            return this->collectString();
        }

        if (isalnum(this->c)) {
            return this->collectId();
        }

        switch (this->c) {
            case '=':
                return this->advanceWithToken(new Token(TOKEN_EQUALS, this->getCurrentCharAsString()));
            case ';':
                return this->advanceWithToken(new Token(TOKEN_SEMI, this->getCurrentCharAsString()));
            case '(':
                return this->advanceWithToken(new Token(TOKEN_LPAREN, this->getCurrentCharAsString()));
            case ')':
                return this->advanceWithToken(new Token(TOKEN_RPAREN, this->getCurrentCharAsString()));
            case ',':
                return this->advanceWithToken(new Token(TOKEN_COMMA, this->getCurrentCharAsString()));
        }
    }

    return new Token(TOKEN_EOF, strdup("\0"));
}

Token* Lexer::collectString() {
    this->advance();
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while (this->c != '"') {
        char* s = this->getCurrentCharAsString();
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        free(s);
        this->advance();
    }

    this->advance();
    return new Token(TOKEN_STRING, value);
}

Token* Lexer::collectId() {
    char* value = (char*)calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(this->c)) {
        char* s = this->getCurrentCharAsString();
        value = (char*)realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);
        free(s);
        this->advance();
    }

    return new Token(TOKEN_ID, value);
}

Token* Lexer::advanceWithToken(Token* token) {
    this->advance();
    return token;
}

char* Lexer::getCurrentCharAsString() {
    char* str = (char*)calloc(2, sizeof(char));
    str[0] = this->c;
    str[1] = '\0';
    return str;
}
