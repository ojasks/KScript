#include "include/AST.hpp"

AST* init_ast(ASTType type) {
    AST* ast = new AST(type);
    ast->variable_defintion_value = nullptr;  // already handled by default, but fine to be explicit
    ast->compound_size = 0;                   // we want this manually tracked
    return ast;
}
