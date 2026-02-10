#pragma once
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// ============================================================================
// REQUIRED FUNCTIONS FOR TESTS
// ============================================================================
// Implement these functions to pass the automated tests.

/**
 * Display a progress bar
 * Requirements for tests:
 * - Print exactly: [filled_chars][empty_chars] with NO newline
 * - Use '█' (U+2588) for filled, '░' (U+2591) for empty
 * - Calculate filled = (current * barWidth) / max
 * - Handle edge cases: if max==0, avoid division by zero
 * - If current > max, clamp to show full bar
 * 
 * Example: displayBar(7, 10, 10) prints: [███████░░░]
 */
void displayBar(int current, int max, int barWidth = 10);

/**
 * Display character information
 * Requirements for tests:
 * - Must include: name, class, level, and health values
 * - Must call displayBar() to show health visually
 * - Use std::setw() for alignment (see solution for format)
 * - Tests check for presence of all values and progress bar characters
 * 
 * Hint: Look at main.cpp to see expected output format
 */
void displayCharacter(const std::string& name, const std::string& charClass, int level, int health,
                      int maxHealth);

/**
 * Display a number in different bases
 * Requirements for tests:
 * - Must output the value in decimal, hexadecimal, and octal
 * - Tests check for presence of all three representations
 * - Hex can be uppercase or lowercase
 * - Remember to reset stream to decimal after using hex/oct manipulators
 * 
 * Example: displayInBases(42) should show 42, 2a (or 2A), and 52
 */
void displayInBases(int value);

/**
 * Display size and limits of a type
 * NOTE: This template is already implemented for you!
 * Just read and understand how it works - you'll write
 * your own templates in Session 10.
 * 
 * Shows: type name, size in bytes, min value, max value
 */
template <typename T>
void displayTypeInfo(const std::string& typeName) {
    std::cout << "Type: " << typeName << "\n";
    std::cout << "  Size: " << sizeof(T) << " bytes\n";
    std::cout << "  Min:  " << std::numeric_limits<T>::min() << "\n";
    std::cout << "  Max:  " << std::numeric_limits<T>::max() << "\n";
}
