// #ifndef PARSER_HPP
// #define PARSER_HPP

// #include "lexer.hpp"
// #include "AST.hpp"
// #include "token.hpp"
// #include "scope.hpp"

// class Parser {
// public:
//     Lexer* lexer;
//     Token* current_token;
//     Token* prev_token;
//     Scope* scope;

//     // Constructor
//     Parser(Lexer* lexer);

//     // Methods
//     void eat(int token_type);

//     AST* parse();
//     AST* parseStatement();
//     AST* parseStatements();
//     AST* parseExpr();
//     AST* parseFactor();
//     AST* parseTerm();
//     AST* parseFunctionCall();
//     AST* parseVariable();
//     AST* parseVariableDefinition();
//     AST* parseFunctionDefinition();
//     AST* parseString();
//     AST* parseId();
//     AST* parsePrintStatement();
// };

// #endif


#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include "AST.hpp"
#include "scope.hpp"

class Parser {
public:
    Lexer* lexer;
    Token* current_token;
    Token* prev_token;
    Scope* scope;

    // Constructor
    Parser(Lexer* lexer);

    // Token handling
    void eat(int token_type);

    // Entry point
    AST* parse(Scope* scope);

    // Statement parsing
    AST* parseStatement(Scope* scope);
    AST* parseStatements(Scope* scope);

    // Expression parsing
    AST* parseExpr(Scope* scope);
    AST* parseFactor(Scope* scope);
    AST* parseTerm(Scope* scope);

    // Specific grammar rules
    AST* parseFunctionCall(Scope* scope);
    AST* parseVariable(Scope* scope);
    AST* parseVariableDefinition(Scope* scope);
    AST* parseFunctionDefinition(Scope* scope);
    AST* parseString(Scope* scope);
    AST* parseId(Scope* scope);
};

#endif
