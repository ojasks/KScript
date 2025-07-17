#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <vector>
#include "AST.hpp"

class Visitor {
public:
    std::vector<AST*> variable_definitions;

    Visitor();

    AST* visit(AST* node);
    AST* visitVariableDefinition(AST* node);
    AST* visitFunctionDefinition(AST* node);
    AST* visitVariable(AST* node);
    AST* visitFunctionCall(AST* node);
    AST* visitString(AST* node);
    AST* visitCompound(AST* node);

private:
    AST* builtinFunctionPrint(const std::vector<AST*>& args);
};

#endif
