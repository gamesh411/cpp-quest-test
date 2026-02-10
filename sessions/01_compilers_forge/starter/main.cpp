#include <iomanip>
#include <iostream>
#include <limits>  // For Side Quest 4
#include <string>

// TODO: Implement your character display system here!
//
// Core Requirements (demonstrated in session):
// 1. Display character name, class, level
// 2. Display health with visual progress bar
// 3. Use proper formatting with iomanip (setw, setprecision)
// 4. Compile with zero warnings
//
// Homework Extensions (you implement):
// 5. Add MANA bar (same technique as health)
// 6. Display character ID in decimal, hex, and octal
// 7. Use std::setfill() for advanced formatting
// 8. Side Quest 4: Create type size explorer (sizeof, numeric_limits)

int main() {
    // TODO: Define character attributes
    // Hint: Use std::string for name/class, int for numbers

    // TODO: Display formatted character sheet
    // Hint: Use std::setw() for alignment

    // TODO: Create health progress bar (in-session demo)
    // Hint: Calculate filled = (current * barWidth) / max

    // TODO HOMEWORK: Create mana progress bar (same technique)

    // TODO HOMEWORK: Display character ID in different bases
    // Example:
    // int characterId = 42;
    // std::cout << "ID (dec): " << std::dec << characterId << "\n";
    // std::cout << "ID (hex): " << std::hex << characterId << "\n";
    // std::cout << "ID (oct): " << std::oct << characterId << "\n";

    // TODO HOMEWORK (Side Quest 4): Type size exploration
    // Example:
    // std::cout << "sizeof(int): " << sizeof(int) << " bytes\n";
    // std::cout << "int max: " << std::numeric_limits<int>::max() << "\n";
    // Do this for: char, short, int, long, float, double, bool

    std::cout << "Character display not yet implemented!\n";
    std::cout << "Open starter/main.cpp and complete the quest.\n";

    return 0;
}
