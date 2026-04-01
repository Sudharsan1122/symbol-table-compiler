# Interactive Symbol Table Compiler ⚙️

![Tech Stack](https://img.shields.io/badge/C++-17-blue) ![HTML5](https://img.shields.io/badge/HTML5-CSS/JS-orange)

A powerful and interactive **Symbol Table Generator** and **Interactive C++ Tokenizer**. This project consists of two versions:
1. A **C++ console application** (`finall.cpp`) that reads C++ code and validates variable declarations while updating a symbol table.
2. A **Web-based GUI** (`symbol_compiler.html`) that simulates a C++ compiler in the browser, showing a live token stream, compiling errors, and an interactive, sortable symbol table.

## 🌟 Features

- **Robust Tokenization**: Processes C++ keywords, primitives, identifiers, and literals.
- **Syntax Validation**: Ensures strings are wrapped in `""`, characters in `''`, and numeric variables actually contain numbers.
- **Dynamic Symbol Table**: Generates a symbol table tracking `Variable Name`, `Type`, `Value`, `Scope`, and `Line Number`.
- **Live Interactive GUI**: A premium web-based interface built with glassmorphism, dynamic updates, and micro-animations for an exceptional developer experience.

---

## 🚀 Getting Started

### 1. Web Version (Interactive Compiler GUI)

The fastest way to experience the compiler is through the web interface. No installation or backend required!

**How to run:**
1. Open the `symbol_compiler.html` file in any modern web browser (Chrome, Edge, Firefox, Safari).
2. Type C++ declarations into the **Source Editor** panel.
3. Click the **▶ Compile** button or press `Ctrl + Enter`.
4. View the live **Token Stream**, **Compiler Output** (for success/errors), and the compiled **Symbol Table**.

*Pro tip: Use the "Load Demo" button or the quick test cases (TC 1 - 5) at the bottom of the editor to see it in action instantly.*

### 2. C++ Console Version

If you prefer the command line, you can compile and run the backend validation engine written in C++.

**Prerequisites:**
- A C++ compiler (like `g++`)

**How to run:**
1. Open your terminal and navigate to the project directory.
2. Compile the source code:
   ```bash
   g++ -o symbol_compiler finall.cpp
   ```
3. Run the executable:
   ```bash
   ./symbol_compiler
   ```
4. Enter your code line-by-line. When finished, type `compile` and press Enter to generate the final Symbol Table.

---

## 🛠️ Tech Stack

- **Core Engine**: C++
- **GUI Engine**: JavaScript (Vanilla)
- **Structure**: HTML5
- **Styling**: CSS3 (Modern Glassmorphism & Variables)

---

## 📸 Web GUI Highlights

- **Dark Glassmorphism Theme**: A premium look and feel emphasizing productivity and readability.
- **Intelligent Scope Analysis**: Detects `public`, `private`, `static`, and local function structures in C++ code.
- **Error Badges & Output Logs**: Highlights syntax errors instantly with line numbers and descriptive logs.
- **Token Highlights**: Color-coded tokens in the token stream visually differentiate keywords, types, assignments, and literals. 

## 🤝 Contributing

Contributions, issues, and feature requests are welcome! Feel free to fork the repository and open a pull request.
