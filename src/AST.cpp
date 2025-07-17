// #include "include/AST.hpp"

// AST::AST(ASTType type) {
//     this->type = type;
//     this->variable_definition_value = nullptr;
//     this->variable_function_body = nullptr;
// }


#include "include/AST.hpp"

AST::AST(ASTType type)
    : type(type),
      scope(nullptr),
      variable_definition_value(nullptr),
      variable_function_body(nullptr) {}
