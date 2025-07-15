#include "include/token.hpp"
#include <cstdlib>

Token* init_token(int type, const char* value) {
    Token* token = new Token(static_cast<TokenType>(type), std::string(value));
    return token;
}
