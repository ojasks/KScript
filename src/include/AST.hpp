#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

enum ASTType {
    AST_STRING = 0,
    AST_VARIABLE,
    AST_VARIABLE_DEFINITION,
    AST_FUNCTION_CALL,
    AST_COMPOUND,
    AST_PRINT
};

struct AST {
    ASTType type;

    std::vector<AST*> compound_value;
    std::string function_call_name;
    std::vector<AST*> function_call_arguments;
    std::string variable_name;
    std::string string_value;
    std::string variable_definition_variable_name;
    AST* variable_defintion_value = nullptr;

    size_t compound_size = 0;

    AST() = default;
    AST(ASTType type) : type(type) {}

    void updateCompoundSize() {
        compound_size = compound_value.size();
    }
};

#endif
