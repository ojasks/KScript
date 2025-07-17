#include "include/visitor.hpp"
#include "include/scope.hpp"
#include "include/AST.hpp"
#include <iostream>
#include <string>

Visitor::Visitor() {
    // nothing to init manually
}

AST* Visitor::visit(AST* node) {
    switch (node->type) {
        case ASTType::VARIABLE_DEFINITION:
            return visitVariableDefinition(node);
        case ASTType::FUNCTION_DEFINITION:
            return visitFunctionDefinition(node);
        case ASTType::VARIABLE:
            return visitVariable(node);
        case ASTType::FUNCTION_CALL:
            return visitFunctionCall(node);
        case ASTType::STRING:
            return visitString(node);
        case ASTType::COMPOUND:
            return visitCompound(node);
        case ASTType::NOOP:
            return node;
        default:
            std::cerr << "Uncaught AST node type " << static_cast<int>(node->type) << "\n";
            return new AST(ASTType::NOOP);
    }
}

AST* Visitor::visitVariableDefinition(AST* node) {
    variable_definitions.push_back(node);
    return node;
}

AST* Visitor::visitFunctionDefinition(AST* node) {
    node->scope->addFunctionDefinition(node);  // ✅ Correct method call on Scope object
    

    std::cout << "We found the Function Definition: " << node->function_definition_name<<".kscript"<< "!" << std::endl;
    return node;
}



AST* Visitor::visitVariable(AST* node) {
    for (AST* def : variable_definitions) {
        if (def->variable_definition_variable_name == node->variable_name) {
            return visit(def->variable_definition_value);
        }
    }
    std::cerr << "Undefined variable '" << node->variable_name << "'\n";
    return node;
}

AST* Visitor::visitFunctionCall(AST* node) {
    if (node->function_call_name == "print") {
        return builtinFunctionPrint(node->function_call_arguments);
    }
     AST* fdef = node->scope->getFunctionDefinition(node->function_call_name);
    if (fdef != nullptr) {
        return this->visit(fdef->variable_function_body);
    }
    std::cerr << "Undefined method '" << node->function_call_name << "'\n";
    exit(1);
}

AST* Visitor::visitString(AST* node) {
    return node;
}

AST* Visitor::visitCompound(AST* node) {
    for (AST* stmt : node->compound_value) {
        visit(stmt);
    }
    return new AST(ASTType::NOOP);
}


// AST* Visitor::visitCompound(AST* node) {
//     for (AST* stmt : node->compound_value) {
//         std::cout << "Visiting compound statement of type: " << static_cast<int>(stmt->type) << std::endl;
//         visit(stmt);
//     }
//     return new AST(ASTType::NOOP);
// }

AST* Visitor::builtinFunctionPrint(const std::vector<AST*>& args) {
    for (AST* arg : args) {
        AST* result = visit(arg);
        if (result->type == ASTType::STRING) {
            std::cout << result->string_value << std::endl;
        } else {
            std::cout << "[Object@" << result << "]" << std::endl;
        }
    }
    return new AST(ASTType::NOOP);
}
