#include "include/parser.hpp"
#include "include/AST.hpp"
#include "include/token.hpp"
#include "include/lexer.hpp"

#include <iostream>
#include <cstring>

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->current_token = lexer->getNextToken();
    this->prev_token = this->current_token;
}

void Parser::eat(int token_type) {
    if (this->current_token->type == token_type) {
        this->prev_token = this->current_token;
        this->current_token = this->lexer->getNextToken();
    } else {
        std::cerr << "Unexpected token '" << this->current_token->value
                  << "' of type " << this->current_token->type << std::endl;
        exit(1);
    }
}

AST* Parser::parse() {
    return this->parseStatements();
}

AST* Parser::parseStatements() {
    AST* compound = new AST(ASTType::COMPOUND);

    AST* stmt = this->parseStatement();
    if (stmt) {
        compound->compound_value.push_back(stmt);
    }

    while (this->current_token->type == TOKEN_SEMI) {
        this->eat(TOKEN_SEMI);
        AST* next_stmt = this->parseStatement();
        if (!next_stmt) break;
        compound->compound_value.push_back(next_stmt);
    }

    return compound;
}

AST* Parser::parseStatement() {
    switch (this->current_token->type) {
        case TOKEN_ID: return this->parseId();
        case TOKEN_EOF: return nullptr;
         default:
        return new AST(ASTType::NOOP);
    }
    return new AST(ASTType::NOOP);
}

AST* Parser::parseExpr() {
    switch (this->current_token->type) {
        case TOKEN_ID: return this->parseId();
        case TOKEN_STRING: return this->parseString();
         default:
        return new AST(ASTType::NOOP);
    }
    return new AST(ASTType::NOOP);
}

AST* Parser::parseFunctionCall() {
    AST* function_call = new AST(ASTType::FUNCTION_CALL);
    function_call->function_call_name = this->prev_token->value;

    this->eat(TOKEN_LPAREN);

    AST* arg = this->parseExpr();
    if (arg) function_call->function_call_arguments.push_back(arg);

    while (this->current_token->type == TOKEN_COMMA) {
        this->eat(TOKEN_COMMA);
        AST* arg = this->parseExpr();
        if (arg) function_call->function_call_arguments.push_back(arg);
    }

    this->eat(TOKEN_RPAREN);
    return function_call;
}

AST* Parser::parseVariableDefinition() {
    this->eat(TOKEN_ID); // 'var'
    std::string var_name = this->current_token->value;
    this->eat(TOKEN_ID);
    this->eat(TOKEN_EQUALS);

    AST* value = this->parseExpr();

    AST* var_def = new AST(ASTType::VARIABLE_DEFINITION);
    var_def->variable_definition_variable_name = var_name;
    var_def->variable_definition_value = value;

    return var_def;
}

AST* Parser::parseVariable() {
    std::string token_value = this->current_token->value;
    this->eat(TOKEN_ID);

    if (this->current_token->type == TOKEN_LPAREN) {
        return this->parseFunctionCall();
    }

    AST* variable = new AST(ASTType::VARIABLE);
    variable->variable_name = token_value;
    return variable;
}

AST* Parser::parseString() {
    AST* str = new AST(ASTType::STRING);
    str->string_value = this->current_token->value;
    this->eat(TOKEN_STRING);
    return str;
}

AST* Parser::parseId() {
    if (this->current_token->value == "var") {
        return this->parseVariableDefinition();
    } else {
        return this->parseVariable();
    }
}
