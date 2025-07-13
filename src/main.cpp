#include <iostream>
#include "include/lexer.hpp"

int main() {
    Lexer lexer(
        "var name = \"ojas ks\";\n"
        "print(name);\n"
    );

    Token* token = nullptr;
    while ((token = lexer.getNextToken()) != nullptr) {
        std::cout << "TOKEN(" << static_cast<int>(token->type) << ", " << token->value << ")\n";
        delete token;
    }

    return 0;
}
