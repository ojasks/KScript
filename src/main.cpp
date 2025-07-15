#include <iostream>
#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/visitor.hpp"

int main(int argc, char* argv[]) {
    Lexer* lexer = new Lexer(
        (char*)(
            "var name = \" ojas ks\";\n"
            "var othername = \" gurman\";\n"
            "print(name,othername);\n"
        )
    );

    Parser* parser = new Parser(lexer);
    AST* root = parser->parse();

    Visitor* visitor = new Visitor();
    visitor->visit(root);

    delete visitor;
    delete parser;
    delete lexer;

    return 0;
}
