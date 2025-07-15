#include "include/AST.hpp"

AST::AST(ASTType type) {
    this->type = type;
    this->variable_definition_value = nullptr;
}
