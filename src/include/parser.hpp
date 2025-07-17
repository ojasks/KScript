#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "AST.hpp"
#include "token.hpp"

class Parser {
public:
    Lexer* lexer;
    Token* current_token;
    Token* prev_token;

    // Constructor
    Parser(Lexer* lexer);

    // Methods
    void eat(int token_type);

    AST* parse();
    AST* parseStatement();
    AST* parseStatements();
    AST* parseExpr();
    AST* parseFactor();
    AST* parseTerm();
    AST* parseFunctionCall();
    AST* parseVariable();
    AST* parseVariableDefinition();
    AST* parseFunctionDefinition();
    AST* parseString();
    AST* parseId();
    AST* parsePrintStatement();
};

#endif
