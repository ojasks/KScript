#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "AST.hpp"

class Scope {
public:
    AST** function_definitions;
    size_t function_definitions_size;

    Scope();  // Constructor
    ~Scope(); // Destructor to free memory

    AST* addFunctionDefinition(AST* funcDef);
    AST* getFunctionDefinition(const std::string& fname);

};

#endif // SCOPE_HPP
