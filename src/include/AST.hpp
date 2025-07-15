#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>

enum class ASTType {
    NOOP,
    COMPOUND,
    FUNCTION_CALL,
    VARIABLE_DEFINITION,
    VARIABLE,
    STRING
};

class AST {
public:
    ASTType type;

    // COMPOUND
    std::vector<AST*> compound_value;

    // FUNCTION_CALL
    std::string function_call_name;
    std::vector<AST*> function_call_arguments;

    // VARIABLE_DEFINITION
    std::string variable_definition_variable_name;
    AST* variable_definition_value;

    // VARIABLE
    std::string variable_name;

    // STRING
    std::string string_value;

    AST(ASTType type);
};

#endif
