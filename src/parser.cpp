#include "include/parser.hpp"
#include <iostream>
#include <cstdlib>

Parser::Parser(Lexer* lexer) {
    this->lexer = lexer;
    this->current_token = this->lexer->getNextToken();
    this->prev_token = this->current_token;
}

void Parser::eat(int token_type) {
    if (this->current_token->type == token_type) {
        this->prev_token = this->current_token;
        this->current_token = this->lexer->getNextToken();
    } else {
        std::cerr << "Unexpected token: value='" 
                  << (this->current_token->value.empty() ? "(null)" : this->current_token->value)
                  << "', type=" << this->current_token->type << "\n";
        exit(1);
    }
}

AST* Parser::parse() {
    return this->parseStatements();
}

AST* Parser::parseStatement() {
    switch (this->current_token->type) {
        case TOKEN_ID: return this->parseId();
        case TOKEN_EOF: return nullptr;
        default:
            std::cerr << "Unexpected token in statement: type=" << this->current_token->type
                      << ", value='" << this->current_token->value << "'\n";
            exit(1);
    }
}

AST* Parser::parseStatements() {
   AST* compound = new AST(AST_COMPOUND);

    AST* stmt = this->parseStatement();
    if (stmt) compound->compound_value.push_back(stmt);

    while (this->current_token->type == TOKEN_SEMI) {
        this->eat(TOKEN_SEMI);
        AST* next_statement = this->parseStatement();
        if (!next_statement) break;
        compound->compound_value.push_back(next_statement);
    }
    compound->updateCompoundSize();  // ✅ this line
    return compound;
}


AST* Parser::parseExpr() {
    switch (this->current_token->type) {
        case TOKEN_ID: return this->parseId();
        case TOKEN_STRING: return this->parseString();
        default:
            std::cerr << "Unexpected token in expression: " << this->current_token->value << "\n";
            exit(1);
    }
}

AST* Parser::parseFunctionCall() {
    AST* function_call = new AST(AST_FUNCTION_CALL);
    this->eat(TOKEN_LPAREN);
    function_call->function_call_name = this->prev_token->value;

    AST* first_arg = this->parseExpr();
    if (first_arg)
        function_call->function_call_arguments.push_back(first_arg);

    while (this->current_token->type == TOKEN_COMMA) {
        this->eat(TOKEN_COMMA);
        function_call->function_call_arguments.push_back(this->parseExpr());
    }

    this->eat(TOKEN_RPAREN);
    return function_call;
}

AST* Parser::parseVariableDefinition() {
    this->eat(TOKEN_ID); // var
    std::string var_name = this->current_token->value;
    this->eat(TOKEN_ID); // variable name
    this->eat(TOKEN_EQUALS);

    AST* value = this->parseExpr();

    AST* def = new AST(AST_VARIABLE_DEFINITION);
    def->variable_definition_variable_name = var_name;
    def->variable_defintion_value = value;

    return def;
}

AST* Parser::parseVariable() {
    std::string name = this->current_token->value;
    this->eat(TOKEN_ID);

    if (this->current_token->type == TOKEN_LPAREN)
        return this->parseFunctionCall();

    AST* var = new AST(AST_VARIABLE);
    var->variable_name = name;
    return var;
}

AST* Parser::parseString() {
    AST* str_node = new AST(AST_STRING);
    str_node->string_value = this->current_token->value;
    this->eat(TOKEN_STRING);
    return str_node;
}

AST* Parser::parseId() {
    if (this->current_token->value == "var") {
        return this->parseVariableDefinition();
    } else {
        return this->parseVariable();
    }
}
