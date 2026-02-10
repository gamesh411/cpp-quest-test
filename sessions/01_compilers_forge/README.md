# Session 1: The Compiler's Forge ⚒️

## Quest Narrative

*"Welcome to the Academy of Modern Magic, apprentice. Before you can wield the powerful spells of C++, you must first learn to forge your tools. The compiler is your forge, and understanding its flames is the first step on your journey to mastery."*

---

## Learning Objectives

By completing this quest, you will:
- Set up a C++ development environment
- Understand the compilation process (preprocessing, compilation, linking)
- Use compiler flags effectively
- Write a basic C++ program with proper structure
- Debug compilation errors

---

## Core Quest (100 XP)

### Requirements

Create a **Character Stats Display System** that:

1. **Displays character information** with proper formatting:
   - Character name
   - Class (Warrior, Mage, Rogue, etc.)
   - Level
   - Health (current/max)
   - Mana (current/max)

2. **Uses proper C++ features**:
   - `iostream` for output
   - `iomanip` for formatting
   - `string` for text
   - Proper variable types

3. **Compiles cleanly**:
   - Zero warnings with `-Wall -Wextra -Werror`
   - Uses C++20 standard
   - Proper includes

### Example Output

```
================================
     CHARACTER SHEET
================================
Name:   Aldric the Brave
Class:  Warrior
Level:  5
--------------------------------
Health: 120 / 150  [████████░░]
Mana:   30  / 50   [██████░░░░]
================================
```

### Starter Code

See `starter/main.cpp` - fill in the implementation!

### Testing

```bash
cd build
cmake ..
make
./sessions/01_compilers_forge/starter/character_display

# Run automated tests
ctest -R session01
```

---

## Side Quests (50 XP each)

### Side Quest 1: Color Magic ✨
Add ANSI color codes to make output colorful:
- Health bar in red/green
- Mana bar in blue
- Character name in bold

**Hint:** ANSI codes like `\033[1;31m` for red, `\033[0m` to reset

### Side Quest 2: The CMake Scroll 📜
Create a proper `CMakeLists.txt` for this session:
- Set C++20 standard
- Enable all warnings
- Create executable target
- Add to parent build system

### Side Quest 3: Input Validation 🛡️
Extend the program to accept user input:
- Prompt for character details
- Validate input (level 1-100, health/mana > 0)
- Handle invalid input gracefully
- Use `std::numeric_limits` for range checking

### Side Quest 4: Type Size Explorer 🔍
Create a program that displays type sizes and limits:
- Show `sizeof()` for all basic types (char, int, long, float, double)
- Display min/max values using `std::numeric_limits<T>`
- Create a formatted table of results
- Compare results on different systems (32-bit vs 64-bit)

---

## Code Quality Bonus (+20 XP)

Earn bonus XP by:
- ✅ Zero compiler warnings
- ✅ Consistent code style (indentation, naming)
- ✅ Meaningful variable names
- ✅ Comments explaining non-obvious code
- ✅ No magic numbers (use constants)

---

## Compilation Flags Explained

```bash
g++ -std=c++20 -Wall -Wextra -Werror -O2 main.cpp -o character_display
```

- `-std=c++20`: Use C++20 standard features
- `-Wall`: Enable common warnings
- `-Wextra`: Enable extra warnings
- `-Werror`: Treat warnings as errors (forces clean code!)
- `-O2`: Optimization level 2 (faster code)
- `-o character_display`: Output executable name

---

## Common Pitfalls

### ❌ Missing includes
```cpp
// Error: 'cout' was not declared
std::cout << "Hello";  // Forgot #include <iostream>
```

### ❌ Forgetting std:: namespace
```cpp
// Error: 'cout' was not declared
cout << "Hello";  // Should be std::cout
```

### ❌ Not using setw/setprecision
```cpp
// Ugly output
std::cout << 3.14159;  // Prints: 3.14159

// Better
std::cout << std::fixed << std::setprecision(2) << 3.14159;  // Prints: 3.14
```

### ❌ Magic numbers
```cpp
// Bad
if (level > 100) { ... }

// Good
const int MAX_LEVEL = 100;
if (level > MAX_LEVEL) { ... }
```

---

## Hints

### Formatting Output

```cpp
#include <iostream>
#include <iomanip>

// Set width for alignment
std::cout << std::setw(10) << "Name:" << "Aldric\n";

// Set precision for numbers
std::cout << std::fixed << std::setprecision(2) << 3.14159;  // 3.14

// Fill character
std::cout << std::setfill('0') << std::setw(5) << 42;  // 00042

// Hex and octal output
std::cout << std::hex << 255;        // ff
std::cout << std::oct << 64;         // 100
std::cout << std::dec << 42;         // 42 (back to decimal)
```

### Creating Progress Bars

```cpp
int current = 120;
int max = 150;
int barWidth = 10;
int filled = (current * barWidth) / max;

std::cout << "[";
for (int i = 0; i < barWidth; i++) {
    if (i < filled) std::cout << "█";
    else std::cout << "░";
}
std::cout << "]";
```

### Memory Layout Exploration

```cpp
#include <iostream>
#include <limits>

// Explore type sizes on your system
std::cout << "sizeof(char):   " << sizeof(char) << " bytes\n";
std::cout << "sizeof(int):    " << sizeof(int) << " bytes\n";
std::cout << "sizeof(double): " << sizeof(double) << " bytes\n";
std::cout << "sizeof(bool):   " << sizeof(bool) << " bytes\n";

// Numeric limits
std::cout << "int max: " << std::numeric_limits<int>::max() << "\n";
std::cout << "int min: " << std::numeric_limits<int>::min() << "\n";
```

---

## Resources

- [C++ iostream reference](https://en.cppreference.com/w/cpp/io)
- [iomanip reference](https://en.cppreference.com/w/cpp/io/manip)
- [Compiler flags guide](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html)
- [std::numeric_limits reference](https://en.cppreference.com/w/cpp/types/numeric_limits)

---

## Homework Expectations

### In-Session Demo (What we'll build together)
- ✅ Basic character display with name, class, level
- ✅ Simple health bar visualization
- ✅ Using `std::cout` and basic `std::setw()`

### Your Homework (What you'll implement)
- 📝 Complete character stats system with health AND mana bars
- 📝 Advanced formatting with `std::setfill()`, `std::setprecision()`
- 📝 Hex/octal number display for character ID
- 📝 Input validation with error handling
- 📝 Type size exploration (Side Quest 4)
- 📝 Optional: Color codes, custom CMakeLists.txt

**Expected time:** 2-3 hours for core quest + 1-2 hours per side quest

---

## Submission Checklist

Before creating your pull request:

- [ ] Code compiles without warnings
- [ ] All tests pass (`ctest -R session01`)
- [ ] **Code is properly formatted** (`clang-format -i starter/main.cpp`)
- [ ] Code is properly formatted and commented
- [ ] Committed to `session-01` branch
- [ ] Pushed to your repository

**Note:** GitHub Actions will automatically check formatting, warnings, and tests. If any check fails, your PR will be rejected with instructions on how to fix it.

---

## Grading Rubric

| Criterion | Points | Description |
|-----------|--------|-------------|
| Correctness | 40 | All tests pass, requirements met |
| Code Quality | 30 | Clean code, no warnings, good style |
| Design | 20 | Proper use of C++ features |
| Creativity | 10 | Side quests, extra features |

---

## Next Quest Preview

In **Session 2: Memory Realms**, you'll learn to navigate the dangerous territories of pointers and references as you build a dynamic inventory system. Prepare yourself for the mysteries of memory! 🧭

---

**Ready to forge your first spell?** Open `starter/main.cpp` and begin!

May your code compile on the first try! ⚒️✨
