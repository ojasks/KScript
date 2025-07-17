#include "include/scope.hpp"
#include <cstdlib> // for malloc, realloc, free
#include <stdlib.h>

Scope::Scope() {
    function_definitions = nullptr;
    function_definitions_size = 0;
}

Scope::~Scope() {
    if (function_definitions) {
        free(function_definitions);
    }
}

AST* Scope::addFunctionDefinition(AST* fdef) {
    function_definitions_size += 1;

    if (function_definitions == nullptr) {
        function_definitions = (AST**) std::calloc(1, sizeof(AST*));
    } else {
        function_definitions = (AST**) std::realloc(
            function_definitions,
            function_definitions_size * sizeof(AST*)
        );
    }

    function_definitions[function_definitions_size - 1] = fdef;
    return fdef;
}

AST* Scope::getFunctionDefinition(const std::string& fname) {
    for (size_t i = 0; i < function_definitions_size; ++i) {
        AST* fdef = function_definitions[i];
        if (fname == fdef->function_definition_name) {
            return fdef;
        }
    }
    return nullptr;
}
