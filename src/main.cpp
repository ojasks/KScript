#include <iostream>
#include "include/lexer.hpp"
#include "include/parser.hpp"

int main(int argc, char* argv[])
{
   Lexer* lexer = new Lexer(
    (char*)"var name = \"ojas ks\"; print(name);"
);
    // Uncomment this block to print tokens if needed
    // Token* token = nullptr;
    // while ((token = lexer->getNextToken()) != nullptr) {
    //     std::cout << "TOKEN(" << token->type << ", " << token->value << ")\n";
    // }

    Parser* parser = new Parser(lexer);
    AST* root = parser->parse();

    std::cout << root->type << std::endl;
    std::cout << root->compound_size << std::endl;

    // Clean up memory
    delete root;
    delete parser;
    delete lexer;

    return 0;
}
