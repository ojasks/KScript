#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "include/lexer.hpp"
#include "include/parser.hpp"
#include "include/visitor.hpp"

void print_help() {
    std::cout << "Usage:\n  kscript.out <filename>\n";
    std::exit(1);
}

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file) {
        std::cerr << "Error reading file: " << filepath << "\n";
        std::exit(2);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        print_help();

    std::string source_code = read_file(argv[1]);

    Lexer* lexer = new Lexer((char*)source_code.c_str());
    Parser* parser = new Parser(lexer);
    AST* root = parser->parse(parser->scope);

    Visitor* visitor = new Visitor();
    visitor->visit(root);

    delete visitor;
    delete parser;
    delete lexer;

    return 0;
}
