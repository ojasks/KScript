# 🧠 KScript – A Minimalist Statically Typed Programming Language
<img width="1400" height="880" alt="Kscipt" src="https://github.com/user-attachments/assets/a78b9b98-c26d-4769-b0fd-4cbcac156bd7" />

![KScript Banner](A_digital_image_emulating_a_retro_computer_termina.png)

KScript is a custom-built, statically typed programming language with a C-like syntax. Designed and implemented from scratch in C++, KScript features support for:

- Variable declarations and types  
- Arithmetic and logical operations  
- Conditional statements and loops  
- User-defined functions  
- Custom bytecode execution via a lightweight interpreter

KScript was engineered with compiler principles in mind, following a structured architecture from lexical analysis to bytecode execution.

---

## 🛠️ Project Highlights

### ✅ Language Features

- **C-like Syntax** – Familiar and concise.
- **Static Typing** – Compile-time type checking.
- **Control Flow** – `if`, `while`, `for`, and logical branching.
- **Functions** – Custom functions with scoped variables.
- **Modular Architecture** – Clean separation of compiler components.

### 📚 Compiler Design

- **Lexer** – Tokenizes the source input into lexical units.
- **Parser** – Converts tokens into an Abstract Syntax Tree (AST).
- **BNF Grammar** – Formal grammar specification of the language.
- **Interpreter** – Custom stack-based bytecode interpreter for runtime execution.

---

## 🧩 Project Structure

```bash
KScript/
├── include/              # Header files for each compiler component
│   ├── AST.h
│   ├── parser.h
│   ├── lexer.h
│   └── visitor.h
├── src/                  # Implementation files
│   ├── AST.cpp
│   ├── parser.cpp
│   ├── lexer.cpp
│   └── main.cpp
├── examples/             # Sample .ks scripts
│   └── factorial.ks
├── Makefile              # Build script
└── README.md             # This file
