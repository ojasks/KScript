#include "include/parser.hpp"
#include "include/scope.hpp"
#include "include/AST.hpp"
#include <iostream>
#include <cstring>


Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->current_token = this->lexer->getNextToken();
    this->prev_token = this->current_token;
    this->scope = new Scope();
}

void Parser::eat(int token_type) {
    if (this->current_token->type == token_type) {
        this->prev_token = this->current_token;
        this->current_token = this->lexer->getNextToken();
    } else {
        std::cerr << "Unexpected Token '" << this->current_token->value
                  << "' with type '" << this->current_token->type << "'\n";
        exit(1);
    }
}

AST* Parser::parse(Scope* scope) {
    return this->parseStatements(scope);
}

AST* Parser::parseStatement(Scope* scope) {
    switch (this->current_token->type) {
        case TOKEN_ID:
            return this->parseId(scope);
        case TOKEN_EOF:
            return nullptr;
        default:
            return new AST(ASTType::NOOP);
    }
}

AST* Parser::parseStatements(Scope* scope) {
    AST* compound = new AST(ASTType::COMPOUND);
    compound->compound_value.push_back(this->parseStatement(scope));
    compound->scope = scope;

   while (this->current_token->type != TOKEN_EOF &&
           this->current_token->type != TOKEN_RBRACE) {
        AST* stmt = this->parseStatement(scope);
        stmt->scope = scope;
        compound->compound_value.push_back(stmt);

        // Eat optional semicolon after each statement
        if (this->current_token->type == TOKEN_SEMI) {
            this->eat(TOKEN_SEMI);
        }
    }


    return compound;
}

AST* Parser::parseExpr(Scope* scope) {
    switch (this->current_token->type) {
        case TOKEN_ID:
            return this->parseId(scope);
        case TOKEN_STRING:
            return this->parseString(scope);
        default:
            return new AST(ASTType::NOOP);
    }
}

AST* Parser::parseFunctionCall(Scope* scope) {
    AST* function_call = new AST(ASTType::FUNCTION_CALL);
    function_call->function_call_name = this->prev_token->value;

    this->eat(TOKEN_LPAREN);

    function_call->function_call_arguments.push_back(this->parseExpr(scope));

    while (this->current_token->type == TOKEN_COMMA) {
        this->eat(TOKEN_COMMA);
        function_call->function_call_arguments.push_back(this->parseExpr(scope));
    }

    this->eat(TOKEN_RPAREN);
    function_call ->scope= scope;
    return function_call;
}

AST* Parser::parseVariableDefinition(Scope* scope) {
    this->eat(TOKEN_ID); // var
    std::string var_name = this->current_token->value;
    this->eat(TOKEN_ID);
    this->eat(TOKEN_EQUALS);
    AST* value = this->parseExpr(scope);

    AST* var_def = new AST(ASTType::VARIABLE_DEFINITION);
    var_def->variable_definition_variable_name = var_name;
    var_def->variable_definition_value = value;

    var_def->scope = scope;
    return var_def;
}

AST* Parser::parseFunctionDefinition(Scope* scope) {
    AST* func_def = new AST(ASTType::FUNCTION_DEFINITION);
    this->eat(TOKEN_ID); // function
    std::string name = this->current_token->value;
    func_def->function_definition_name = name;
    this->eat(TOKEN_ID);
    this->eat(TOKEN_LPAREN);
    this->eat(TOKEN_RPAREN);
    this->eat(TOKEN_LBRACE);
    func_def-> variable_function_body = this->parseStatements(scope);
    this->eat(TOKEN_RBRACE);
    func_def->scope = scope;
    return func_def;
}

AST* Parser::parseVariable(Scope* scope) {
    std::string token_value = this->current_token->value;
    this->eat(TOKEN_ID);

    if (this->current_token->type == TOKEN_LPAREN) {
        return this->parseFunctionCall(scope);
    }

    AST* variable = new AST(ASTType::VARIABLE);
    variable->variable_name = token_value;
    variable->scope = scope;
    return variable;
}

AST* Parser::parseString(Scope* scope) {
    AST* string_node = new AST(ASTType::STRING);
    string_node->string_value = this->current_token->value;
    this->eat(TOKEN_STRING);
    string_node->scope = scope;
    return string_node;
}

AST* Parser::parseId(Scope* scope) {
    if (this->current_token->value == "var") {
        return this->parseVariableDefinition(scope);
    } else if (this->current_token->value == "function") {
        return this->parseFunctionDefinition(scope);
    } else {
        return this->parseVariable(scope);
    }
}
