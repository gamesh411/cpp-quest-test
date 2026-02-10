# C++ Quest Style Guide

## Automated Formatting Available! ✨

**This repository includes a `.clang-format` configuration file.** You can automatically format your code to match this style guide!

```bash
# Format your code before committing
clang-format -i sessions/01_compilers_forge/starter/main.cpp
```

See the [Tools](#tools) section below for IDE integration.

---

## General Principles

- **Clarity over cleverness**: Write code that others can understand
- **Consistency**: Follow the same style throughout your code
- **Modern C++**: Use C++11/14/17/20 features appropriately

---

## Naming Conventions

### Variables and Functions
```cpp
// Use camelCase for variables and functions
int playerHealth = 100;
std::string characterName = "Aldric";

void calculateDamage(int baseDamage) {
    // ...
}
```

### Constants
```cpp
// Use UPPER_CASE for constants
const int MAX_LEVEL = 100;
const double PI = 3.14159;
```

### Classes and Structs
```cpp
// Use PascalCase for class names
class Character {
    // ...
};

struct ItemData {
    // ...
};
```

### Private Members
```cpp
class Character {
private:
    int health_;      // Trailing underscore for private members
    std::string name_;
    
public:
    int getHealth() const { return health_; }
};
```

---

## Formatting

### Indentation
- Use **4 spaces** (not tabs)
- Consistent indentation for readability

```cpp
int main() {
    if (condition) {
        doSomething();
        if (anotherCondition) {
            doMore();
        }
    }
    return 0;
}
```

### Braces
- Opening brace on same line (K&R style)
- Always use braces, even for single-line blocks

```cpp
// Good
if (condition) {
    doSomething();
}

// Avoid (even though valid)
if (condition)
    doSomething();
```

### Line Length
- Keep lines under 100 characters
- Break long lines logically

```cpp
// Good
std::cout << "This is a very long message that should be "
          << "split across multiple lines for readability\n";
```

---

## Comments

### When to Comment
- Explain **why**, not **what**
- Document non-obvious logic
- Add TODO for incomplete work

```cpp
// Good: Explains why
// Use binary search because inventory is sorted
int findItem(const std::string& name) {
    // ...
}

// Bad: States the obvious
// Increment i by 1
i++;
```

### Comment Style
```cpp
// Single-line comments for brief explanations

/*
 * Multi-line comments for longer explanations
 * or documentation blocks
 */

/**
 * Function documentation (Doxygen style)
 * @param damage Amount of damage to apply
 * @return true if character survived, false otherwise
 */
bool takeDamage(int damage);
```

---

## Modern C++ Features

### Use auto Appropriately
```cpp
// Good: Type is obvious from right side
auto name = std::string("Aldric");
auto it = myVector.begin();

// Bad: Type is not obvious
auto x = calculate();  // What type is x?
```

### Range-Based For Loops
```cpp
// Prefer range-based for when possible
std::vector<int> numbers = {1, 2, 3, 4, 5};

// Good
for (const auto& num : numbers) {
    std::cout << num << " ";
}

// Avoid (unless you need index)
for (size_t i = 0; i < numbers.size(); i++) {
    std::cout << numbers[i] << " ";
}
```

### Use nullptr
```cpp
// Good
int* ptr = nullptr;

// Avoid
int* ptr = NULL;  // Old C style
int* ptr = 0;     // Ambiguous
```

### Prefer {} Initialization
```cpp
// Good: Uniform initialization
int x{42};
std::string name{"Aldric"};
std::vector<int> numbers{1, 2, 3};

// Also acceptable
int x = 42;
```

---

## Memory Management

### Prefer Stack to Heap
```cpp
// Good: Stack allocation
std::string name = "Aldric";
std::vector<int> inventory;

// Avoid unless necessary
std::string* name = new std::string("Aldric");  // Why heap?
```

### Use Smart Pointers
```cpp
// Good: Smart pointers manage memory
std::unique_ptr<Character> player = std::make_unique<Character>();
std::shared_ptr<Item> item = std::make_shared<Item>();

// Avoid: Raw pointers with new/delete
Character* player = new Character();
delete player;  // Easy to forget!
```

---

## Error Handling

### Check for Errors
```cpp
// Good: Check file operations
std::ifstream file("data.txt");
if (!file.is_open()) {
    std::cerr << "Error: Could not open file\n";
    return 1;
}
```

### Use Const Correctness
```cpp
class Character {
    int health_;
public:
    // Const for methods that don't modify
    int getHealth() const { return health_; }
    
    // Non-const for methods that modify
    void setHealth(int h) { health_ = h; }
};
```

---

## Organization

### Header Guards
```cpp
// character.h
#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
    // ...
};

#endif  // CHARACTER_H

// Or use #pragma once (modern compilers)
#pragma once

class Character {
    // ...
};
```

### Include Order
```cpp
// 1. Related header (if in .cpp file)
#include "character.h"

// 2. C++ standard library
#include <iostream>
#include <string>
#include <vector>

// 3. Third-party libraries
#include <catch2/catch.hpp>

// 4. Project headers
#include "inventory.h"
#include "spell.h"
```

---

## Common Patterns

### Constructor Initialization Lists
```cpp
// Good: Use initializer lists
class Character {
    std::string name_;
    int health_;
public:
    Character(const std::string& name, int health)
        : name_(name), health_(health) {
        // Constructor body
    }
};

// Avoid: Assignment in constructor body
Character(const std::string& name, int health) {
    name_ = name;      // Less efficient
    health_ = health;
}
```

### Return Value Optimization
```cpp
// Good: Return by value (RVO applies)
std::vector<int> createNumbers() {
    std::vector<int> result = {1, 2, 3};
    return result;  // No copy, RVO optimizes
}

// Don't do this
std::vector<int>* createNumbers() {
    return new std::vector<int>{1, 2, 3};  // Memory leak risk!
}
```

---

## Things to Avoid

### ❌ Using namespace std
```cpp
// Bad: Pollutes global namespace
using namespace std;

// Good: Use std:: prefix
std::cout << "Hello\n";

// Acceptable: In limited scope
void someFunction() {
    using std::cout;
    cout << "Hello\n";
}
```

### ❌ Magic Numbers
```cpp
// Bad
if (level > 100) { ... }

// Good
const int MAX_LEVEL = 100;
if (level > MAX_LEVEL) { ... }
```

### ❌ C-Style Casts
```cpp
// Bad
int x = (int)3.14;

// Good
int x = static_cast<int>(3.14);
```

---

## Quick Checklist

Before submitting code:

- [ ] Consistent naming (camelCase, PascalCase, UPPER_CASE)
- [ ] Proper indentation (4 spaces)
- [ ] Meaningful variable names
- [ ] Comments explain why, not what
- [ ] No compiler warnings
- [ ] Use modern C++ features (auto, range-for, nullptr)
- [ ] Smart pointers instead of raw new/delete
- [ ] Const correctness
- [ ] Error checking
- [ ] No magic numbers

---

## Tools

### Automatic Formatting

**This repository includes a `.clang-format` file that enforces the style guide automatically!**

```bash
# Format a single file
clang-format -i main.cpp

# Format all C++ files in current directory
clang-format -i *.cpp *.h

# Check formatting without modifying (useful for CI)
clang-format --dry-run --Werror main.cpp
```

**IDE Integration:**

**VS Code:**
1. Install "C/C++" extension
2. Add to `.vscode/settings.json`:
   ```json
   {
       "editor.formatOnSave": true,
       "C_Cpp.clang_format_style": "file"
   }
   ```

**CLion:**
- Settings → Editor → Code Style → C/C++
- Scheme: "Project" (automatically uses `.clang-format`)
- Enable "Reformat code" on save

**Vim/Neovim:**
```vim
" Format on save
autocmd BufWritePre *.cpp,*.h :silent! !clang-format -i %
```

### Static Analysis
```bash
# cppcheck
cppcheck --enable=all main.cpp

# clang-tidy
clang-tidy main.cpp -- -std=c++20
```

---

**Remember:** Good style makes code easier to read, maintain, and debug. Your future self (and your teammates) will thank you! ✨
